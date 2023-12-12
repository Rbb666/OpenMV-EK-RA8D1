#include <rtthread.h>
#include "hal_data.h"
#include "cam_hal.h"

#define DRV_DEBUG
#define LOG_TAG             "sensor"
#include <drv_log.h>

#define CAM_TASK_STACK (2 * 1024)

static cam_obj_t *cam_obj = NULL;
extern struct rt_memheap system_heap;

//void g_ceu_callback(capture_callback_args_t *p_args)
//{
//    rt_interrupt_enter();

//    if (CEU_EVENT_FRAME_END == p_args->event)
//    {
//        rt_completion_done(&cam_obj->ceu_completion);
//    }

//    rt_interrupt_leave();
//}

static void cam_task(void *arg)
{
    fsp_err_t err = R_CEU_Open(cam_obj->ceu_instance->p_ctrl, cam_obj->ceu_instance->p_cfg);
    if (err != FSP_SUCCESS)
    {
        LOG_E("R_CEU_Open API FAILED:%d", err);
        return;
    }

    while (1)
    {
        fsp_err_t err = R_CEU_CaptureStart(cam_obj->ceu_instance->p_ctrl, cam_obj->frames->fb.buf);
        if (err != FSP_SUCCESS)
        {
            LOG_E("R_CEU_CaptureStart API FAILED:%d", err);
        }

        rt_completion_wait(&cam_obj->ceu_completion, RT_WAITING_FOREVER);

        rt_mq_send(cam_obj->frame_buffer_queue, &cam_obj->frames->fb, sizeof(camera_fb_t *));
    }
}

camera_fb_t *cam_take(rt_tick_t timeout)
{
    camera_fb_t *buffer = NULL;
    //rt_tick_t start = rt_tick_get();

    if (rt_mq_recv(cam_obj->frame_buffer_queue, (void *)&buffer, sizeof(camera_fb_t *), timeout) > 0)
    {
        rt_kprintf("%#x\n", (void *)&buffer);
        return buffer;
    }
    return NULL;
}

#define FB_GET_TIMEOUT (4000 / RT_TICK_PER_SECOND)

camera_fb_t *camera_fb_get(void)
{
    camera_fb_t *fb = cam_take(FB_GET_TIMEOUT);
    //set the frame properties
    if (fb)
    {
        fb->width = 320;
        fb->height = 240;
        fb->len = 320 * 240;
    }
    return fb;
}

static rt_err_t cam_config(void)
{
    cam_obj->ceu_instance = (capture_instance_t *)&g_ceu_qvga;
    cam_obj->frames->fb.width = 320;
    cam_obj->frames->fb.height = 240;

    cam_obj->frames->fb.buf = (uint8_t *)rt_memheap_alloc(&system_heap, cam_obj->frames->fb.width * cam_obj->frames->fb.height);
    rt_kprintf("%#x\n", cam_obj->frames->fb.buf);

    return RT_EOK;
}

rt_err_t camera_init(void)
{
    size_t frame_buffer_queue_len = 2;
    cam_obj->frame_cnt = frame_buffer_queue_len;

    cam_obj = (cam_obj_t *)rt_malloc(sizeof(cam_obj_t));
    cam_obj->frames = (cam_frame_t *)rt_malloc(cam_obj->frame_cnt * sizeof(cam_frame_t));

    cam_obj->frame_buffer_queue = rt_mq_create("cam_mq", sizeof(camera_fb_t *),
                                  frame_buffer_queue_len, RT_IPC_FLAG_PRIO);
    RT_ASSERT(cam_obj->frame_buffer_queue != RT_NULL);

    cam_config();

    rt_completion_init(&cam_obj->ceu_completion);

    rt_thread_t tid = rt_thread_create("cam", cam_task, RT_NULL,
                                       CAM_TASK_STACK, 10, 20);
    RT_ASSERT(tid != RT_NULL);
    rt_thread_startup(tid);

    return RT_EOK;
}

rt_err_t cam_deinit(void)
{
    if (!cam_obj)
    {
        return -RT_ERROR;
    }

    if (cam_obj->frame_buffer_queue)
        rt_mq_delete(cam_obj->frame_buffer_queue);

    return RT_EOK;
}
////////////////////////////////////////////////////////