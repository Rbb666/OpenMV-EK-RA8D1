/*
 * This file is part of the OpenMV project.
 *
 * Copyright (c) 2013-2021 Ibrahim Abdelkader <iabdalkader@openmv.io>
 * Copyright (c) 2013-2021 Kwabena W. Agyeman <kwagyeman@openmv.io>
 *
 * This work is licensed under the MIT license, see the file LICENSE for details.
 *
 * Sensor abstraction layer.
 */
#include <string.h>
#include <stdint.h>

#include "sensor.h"
#include "py/mphal.h"
#include "framebuffer.h"
#include "omv_boardconfig.h"
#include "unaligned_memcpy.h"

#include "hal_data.h"

#define DRV_DEBUG
#define LOG_TAG             "sensor"
#include <drv_log.h>

sensor_t sensor = {0};
capture_instance_t *gp_ceu_instance = NULL;

static struct rt_completion ceu_completion;

static int ceu_device_open(void);
static int ceu_device_close(void);

int sensor_init(void)
{
    int init_ret = 0;

    /* Reset the sesnor state */
    memset(&sensor, 0, sizeof(sensor_t));

    // Set default snapshot function.
    sensor.snapshot = sensor_snapshot;

    // Detect and initialize the image sensor.
    if ((init_ret = sensor_probe_init(ISC_I2C_ID, ISC_I2C_SPEED)) != 0)
    {
        LOG_E("not found any sensors !!");
        // Sensor probe/init failed.
        return init_ret;
    }

    // Set default color palette.
    sensor.color_palette = rainbow_table;
    sensor.pwdn_pol = ACTIVE_HIGH;

    // Disable VSYNC IRQ and callback
    sensor_set_vsync_callback(NULL);

    // All good!
    sensor.detected = true;

    //ceu_device_close();

    rt_completion_init(&ceu_completion);

    return 0;
}

int sensor_set_xclk_frequency(uint32_t frequency)
{

    return 0;
}

uint32_t sensor_get_xclk_frequency(void)
{
    return 0;
}

int sensor_set_vsync_callback(vsync_cb_t vsync_cb)
{
    return 0;
}

int sensor_dcmi_config(uint32_t pixformat)
{

    return 0;
}

int sensor_abort(void)
{
    // ceu_device_close();
    framebuffer_reset_buffers();
    return 0;
}

int sensor_set_framesize(framesize_t framesize)
{
    if (sensor.framesize == framesize)
    {
        return 0;
    }

    switch (framesize)
    {
    case FRAMESIZE_SVGA://800x600
        gp_ceu_instance = (capture_instance_t *)&g_ceu_svga;
        break;
    case FRAMESIZE_VGA://640x480
        gp_ceu_instance = (capture_instance_t *)&g_ceu_vga;
        break;
    case FRAMESIZE_QVGA://320x240
        gp_ceu_instance = (capture_instance_t *)&g_ceu_qvga;
        break;
    case FRAMESIZE_QQVGA://160x120
        gp_ceu_instance = (capture_instance_t *)&g_ceu_qqvga;
        break;
    case FRAMESIZE_QQQVGA://80x60
        gp_ceu_instance = (capture_instance_t *)&g_ceu_qqqvga;
        break;
    case FRAMESIZE_HVGA://480x320
        gp_ceu_instance = (capture_instance_t *)&g_ceu_hvga;
        break;
    case FRAMESIZE_HQVGA://240x160
        gp_ceu_instance = (capture_instance_t *)&g_ceu_hqvga;
        break;
    case FRAMESIZE_HQQVGA://120x80
        gp_ceu_instance = (capture_instance_t *)&g_ceu_hqqvga;
        break;
    case FRAMESIZE_64X32://64X32
        gp_ceu_instance = (capture_instance_t *)&g_ceu_64X32;
        break;
    case FRAMESIZE_64X64://64X64
        gp_ceu_instance = (capture_instance_t *)&g_ceu_64X64;
        break;
    case FRAMESIZE_128X64://128X64
        gp_ceu_instance = (capture_instance_t *)&g_ceu_128X64;
        break;
    case FRAMESIZE_128X128://128X128
        gp_ceu_instance = (capture_instance_t *)&g_ceu_128X128;
        break;
    case FRAMESIZE_320X320://320X320
        gp_ceu_instance = (capture_instance_t *)&g_ceu_320X320;
        break;
    default:
        break;
    }
    LOG_I("set framesize:%dX%d", gp_ceu_instance->p_cfg->x_capture_pixels, gp_ceu_instance->p_cfg->y_capture_pixels);

    ceu_device_open();

    // Disable any ongoing frame capture.
    sensor_abort();

    // Flush previous frame.
    framebuffer_update_jpeg_buffer();

    // Call the sensor specific function
    if (sensor.set_framesize == NULL)
    {
        return SENSOR_ERROR_CTL_UNSUPPORTED;
    }

    if (sensor.set_framesize(&sensor, framesize) != 0)
    {
        return SENSOR_ERROR_CTL_FAILED;
    }

    mp_hal_delay_ms(100); // wait for the camera to settle

    // Set framebuffer size
    sensor.framesize = framesize;

    // Skip the first frame.
    MAIN_FB()->pixfmt = PIXFORMAT_INVALID;

    // Set MAIN FB x offset, y offset, width, height, backup width, and backup height.
    MAIN_FB()->x = 0;
    MAIN_FB()->y = 0;
    MAIN_FB()->w = MAIN_FB()->u = resolution[framesize][0];
    MAIN_FB()->h = MAIN_FB()->v = resolution[framesize][1];

    // Pickout a good buffer count for the user.
    framebuffer_auto_adjust_buffers();

    return 0;
}

void g_ceu_callback(capture_callback_args_t *p_args)
{
    rt_interrupt_enter();

    if (CEU_EVENT_HD == p_args->event)
    {
        /* Capture has started. Process V-Sync event. */
    }
    if (CEU_EVENT_FRAME_END == p_args->event)
    {
        if (sensor.frame_callback)
        {
            sensor.frame_callback();
        }
        rt_completion_done(&ceu_completion);
    }

    rt_interrupt_leave();
}

static int ceu_device_close(void)
{
    capture_status_t ceu_state;
    R_CEU_StatusGet(gp_ceu_instance->p_ctrl, (capture_status_t *)&ceu_state);
    if (ceu_state.state == CAPTURE_STATE_BUSY)
    {
        fsp_err_t err = R_CEU_Close(gp_ceu_instance->p_ctrl);
        if (err != FSP_SUCCESS)
        {
            LOG_E("R_CEU_CaptureStart API FAILED !!");
            return -1;
        }
    }
    LOG_I("Close CEU device");
    return 0;
}

static int ceu_device_open(void)
{
    capture_status_t ceu_state;
    R_CEU_StatusGet(gp_ceu_instance->p_ctrl, (capture_status_t *)&ceu_state);
    if (ceu_state.state == CAPTURE_STATE_IDLE)
    {
        fsp_err_t err = R_CEU_Open(gp_ceu_instance->p_ctrl, gp_ceu_instance->p_cfg);
        if (err != FSP_SUCCESS)
        {
            LOG_E("R_CEU_Open API FAILED:%d", err);
            return -1;
        }
    }

    framebuffer_reset_buffers();

    LOG_I("Open CEU device");
    return 0;
}

static int ceu_device_snapshot(void *buffer)
{
    vbuffer_t *v_buf = buffer;
    /* Start capture image and store it in the buffer specified by image buffer pointer */
    fsp_err_t err = R_CEU_CaptureStart(gp_ceu_instance->p_ctrl, (uint8_t *)v_buf->data);
    if (err != FSP_SUCCESS)
    {
        LOG_E("R_CEU_CaptureStart API FAILED:%d", err);
        return -1;
    }
    return 0;
}

int write_raw_yuyv_to_gray(uint8_t *data, uint8_t *grey, int len)
{
    int j = 0;
    for (int i = 0; i < len; i += 2)
    {
        grey[j] = data[i];
        j++;
    }
    return 0;
}

// This is the default snapshot function, which can be replaced in sensor_init functions. This function
// uses the DCMI and DMA to capture frames and each line is processed in the DCMI_DMAConvCpltUser function.
int sensor_snapshot(sensor_t *sensor, image_t *image, uint32_t flags)
{
    uint32_t w = MAIN_FB()->u;
    uint32_t h = MAIN_FB()->v;

    if (sensor->pixformat == PIXFORMAT_INVALID)
    {
        return SENSOR_ERROR_INVALID_PIXFORMAT;
    }

    if (sensor->framesize == FRAMESIZE_INVALID)
    {
        return SENSOR_ERROR_INVALID_FRAMESIZE;
    }

    if (sensor_check_framebuffer_size() != 0)
    {
        return SENSOR_ERROR_FRAMEBUFFER_OVERFLOW;
    }

    if (MAIN_FB()->n_buffers != 1)
    {
        framebuffer_set_buffers(1);
    }

    // Compress the framebuffer for the IDE preview.
    framebuffer_update_jpeg_buffer();

    // Free the current FB head.
    framebuffer_free_current_buffer();

    vbuffer_t *buffer = framebuffer_get_tail(FB_NO_FLAGS);
    if (!buffer)
    {
        return SENSOR_ERROR_FRAMEBUFFER_ERROR;
    }

    ceu_device_snapshot((vbuffer_t *)buffer);

    rt_completion_wait(&ceu_completion, RT_WAITING_FOREVER);

    // Wait for the DMA to finish the transfer.
    for (mp_uint_t ticks = mp_hal_ticks_ms(); buffer == NULL;)
    {
        buffer = framebuffer_get_head(FB_NO_FLAGS);
        if ((mp_hal_ticks_ms() - ticks) > 3000)
        {
            sensor_abort();
            return SENSOR_ERROR_CAPTURE_TIMEOUT;
        }
    }

    if (!sensor->transpose)
    {
        MAIN_FB()->w = w;
        MAIN_FB()->h = h;
    }
    else
    {
        MAIN_FB()->w = h;
        MAIN_FB()->h = w;
    }

    // Fix the BPP.
    switch (sensor->pixformat)
    {
    case PIXFORMAT_GRAYSCALE:
        MAIN_FB()->pixfmt = PIXFORMAT_GRAYSCALE;
        write_raw_yuyv_to_gray(buffer->data, buffer->data, w * h * 2);
        break;
    case PIXFORMAT_RGB565:
        MAIN_FB()->pixfmt = PIXFORMAT_RGB565;
        break;
    case PIXFORMAT_BAYER:
        MAIN_FB()->pixfmt = PIXFORMAT_BAYER;
        MAIN_FB()->subfmt_id = sensor->hw_flags.bayer;
        break;
    case PIXFORMAT_YUV422:
    {
        bool yuv_order = sensor->hw_flags.yuv_order == SENSOR_HW_FLAGS_YUV422;
        int even = yuv_order ? PIXFORMAT_YUV422 : PIXFORMAT_YVU422;
        int odd = yuv_order ? PIXFORMAT_YVU422 : PIXFORMAT_YUV422;
        MAIN_FB()->pixfmt = (MAIN_FB()->x % 2) ? odd : even;
        break;
    }
    case PIXFORMAT_JPEG:
    {
        int32_t size = 0;
        if (sensor->chip_id == OV5640_ID)
        {
            // Offset contains the sum of all the bytes transferred from the offset buffers
            // while in DCMI_DMAConvCpltUser().
            size = buffer->offset;
        }
        // Clean trailing data after 0xFFD9 at the end of the jpeg byte stream.
        MAIN_FB()->pixfmt = PIXFORMAT_JPEG;
        MAIN_FB()->size = jpeg_clean_trailing_bytes(size, buffer->data);
        break;
    }
    default:
        break;
    }

    // Swap bytes if set.
    if ((MAIN_FB()->pixfmt == PIXFORMAT_RGB565 && sensor->hw_flags.rgb_swap) ||     \
            (MAIN_FB()->pixfmt == PIXFORMAT_YUV422 && sensor->hw_flags.yuv_swap))   \
    {
        unaligned_memcpy_rev16(buffer->data, buffer->data, w * h);
    }

    // Set the user image.
    framebuffer_init_image(image);
    return 0;
}
