/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2023-12-10     Rbb666        first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "ra/board/ra8d1_ek/board_sdram.h"
#ifdef RT_USING_DFS
    #include <unistd.h>
    #include <fcntl.h>
#endif
#ifdef BSP_USING_OPENMV
    #include <py/compile.h>
    #include <py/runtime.h>
    #include <py/repl.h>
    #include <py/gc.h>
    #include <py/mperrno.h>
    #include <py/stackctrl.h>
    #include <py/frozenmod.h>
    #include <lib/utils/pyexec.h>
    #include <lib/mp-readline/readline.h>
    #include "framebuffer.h"
    #include "fb_alloc.h"
    #include "ff_wrapper.h"
    #include "usbdbg.h"
    #include "sensor.h"
    #include "tinyusb_debug.h"
    #include "tusb.h"
    #include "led.h"
#endif /* BSP_USING_OPENMV */
#ifdef RT_USING_FAL
    #include "fal.h"
#endif /* RT_USING_FAL */

#define DRV_DEBUG
#define LOG_TAG             "main"
#include <drv_log.h>

/* Onboard LED pins */
#define LED_PIN    BSP_IO_PORT_06_PIN_00
/* MicroPython runs as a task under RT-Thread */
#define MP_TASK_STACK_SIZE      (16 * 1024)

#ifdef RT_USING_MEMHEAP_AS_HEAP
    struct rt_memheap system_heap;
#endif

#ifdef BSP_USING_OPENMV
static void *stack_top = RT_NULL;
static char OMV_ATTR_SECTION(OMV_ATTR_ALIGNED(gc_heap[OMV_HEAP_SIZE], 4), ".data");

extern int mount_init(void);
extern void fmath_init(void);
static void exec_boot_script(const char *path, bool interruptible);

void *__signgam_addr(void)
{
    return NULL;
}

static void omv_entry(void *parameter)
{
    (void) parameter;
    int stack_dummy;
    stack_top = (void *)&stack_dummy;

    bool first_soft_reset = true;

#ifdef RT_USING_FAL
    fal_init();
#endif
#ifdef PKG_TINYUSB_DEVICE_MSC
    mount_init();
#endif
    fmath_init();

    framebuffer_init0();
    fb_alloc_init0();

#if MICROPY_PY_THREAD
    mp_thread_init(rt_thread_self()->stack_addr, MP_TASK_STACK_SIZE / sizeof(uintptr_t));
#endif

#ifdef SENSOR_USING_CAM_XCLK
    /* Initialize GPT module */
    R_GPT_Open(&g_timer3_ctrl, &g_timer3_cfg);
    /* Start GPT module to provide the 24MHz clock frequency output for the camera clock source */
    R_GPT_Start(&g_timer3_ctrl);
#endif

OMV_RESTART:
    /* Stack limit should be less than real stack size, so we have a */
    /* chance to recover from limit hit. (Limit is measured in bytes) */
    mp_stack_set_top(stack_top);
    mp_stack_set_limit(MP_TASK_STACK_SIZE - 1024);

    /* GC init */
    gc_init(&gc_heap[0], &gc_heap[MP_ARRAY_SIZE(gc_heap)]);

    /* MicroPython initialization */
    mp_init();

    readline_init0();
    imlib_init_all();

    usb_cdc_init();
    usbdbg_init();
    file_buffer_init0();
    sensor_init0();
    led_init();

#if MICROPY_PY_SENSOR
    if (sensor_init() != 0 && first_soft_reset)
    {
        LOG_E("sensor init failed!");
    }
#endif

    /* run boot.py and main.py if they exist */
    exec_boot_script("boot.py", false);

    if (first_soft_reset)
    {
        exec_boot_script("main.py", true);
    }

    /* If there's no script ready, just re-exec REPL */
    while (!usbdbg_script_ready())
    {
        nlr_buf_t nlr;
        if (nlr_push(&nlr) == 0)
        {
            /* enable IDE interrupt */
            usbdbg_set_irq_enabled(true);
            /* run REPL */
            if (pyexec_mode_kind == PYEXEC_MODE_RAW_REPL)
            {
                if (pyexec_raw_repl() != 0)
                {
                    break;
                }
            }
            else
            {
                if (pyexec_friendly_repl() != 0)
                {
                    break;
                }
            }
            nlr_pop();
        }
    }

    LOG_I("Exit from repy!");

    if (usbdbg_script_ready())
    {
        nlr_buf_t nlr;
        if (nlr_push(&nlr) == 0)
        {
            // Enable IDE interrupt
            usbdbg_set_irq_enabled(true);
            // Execute the script.
            pyexec_str(usbdbg_get_script());
            // Disable IDE interrupts
            usbdbg_set_irq_enabled(false);
            nlr_pop();
        }
        else
        {
            mp_obj_print_exception(&mp_plat_print, (mp_obj_t) nlr.ret_val);
        }

        if (usbdbg_is_busy() && nlr_push(&nlr) == 0)
        {
            // Enable IDE interrupt
            usbdbg_set_irq_enabled(true);
            // Wait for the current command to finish.
            usbdbg_wait_for_command(1000);
            // Disable IDE interrupts
            usbdbg_set_irq_enabled(false);
            nlr_pop();
        }
    }

    gc_sweep_all();
    mp_deinit();
#if MICROPY_PY_THREAD
    mp_thread_deinit();
#endif
    first_soft_reset = false;
    goto OMV_RESTART;
}

static void exec_boot_script(const char *path, bool interruptible)
{
    nlr_buf_t nlr;
    bool interrupted = false;
    if (nlr_push(&nlr) == 0)
    {
        // Enable IDE interrupts if allowed.
        if (interruptible)
        {
            usbdbg_set_irq_enabled(true);
            usbdbg_set_script_running(true);
        }

        // Parse, compile and execute the script.
        pyexec_file_if_exists(path);
        nlr_pop();
    }
    else
    {
        interrupted = true;
    }

    // Disable IDE interrupts
    usbdbg_set_irq_enabled(false);
    usbdbg_set_script_running(false);

    if (interrupted)
    {
        mp_obj_print_exception(&mp_plat_print, (mp_obj_t) nlr.ret_val);
    }
}

#pragma clang section text = ".itcm_data"
static void omv_init_func(void)
{
    rt_thread_t tid;

    tid = rt_thread_create("omv", omv_entry, RT_NULL,
                           MP_TASK_STACK_SIZE / sizeof(uint32_t), 22, 20);
    RT_ASSERT(tid != RT_NULL);

    rt_thread_startup(tid);
}
#pragma clang section text = ""
#endif  /* BSP_USING_OPENMV */

void hal_entry(void)
{
    LOG_I("\nHello RT-Thread & OpenMV!\n");

#ifdef BSP_USING_OPENMV
    omv_init_func();
#endif
}

#ifdef BSP_USING_SDRAM
static int SDRAM_Init(void)
{
    bsp_sdram_init();

    LOG_D("sdram init success, mapped at 0x%X, size is %d bytes, data width is %d", 0x68000000, BSP_USING_SDRAM_SIZE, 16);
#ifdef RT_USING_MEMHEAP_AS_HEAP
    /* If RT_USING_MEMHEAP_AS_HEAP is enabled, SDRAM is initialized to the heap */
    rt_memheap_init(&system_heap, "sdram", (void *)0x68000000, BSP_USING_SDRAM_SIZE);
#endif
    return RT_EOK;
}
INIT_BOARD_EXPORT(SDRAM_Init);
#endif
