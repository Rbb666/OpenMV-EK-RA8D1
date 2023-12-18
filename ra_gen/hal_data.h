/* generated HAL header file - do not edit */
#ifndef HAL_DATA_H_
#define HAL_DATA_H_
#include <stdint.h>
#include "bsp_api.h"
#include "common_data.h"
#include "r_gpt.h"
#include "r_timer_api.h"
#include "r_sci_b_uart.h"
            #include "r_uart_api.h"
#include "r_capture_api.h"
            #include "r_ceu.h"
#include "r_sci_b_spi.h"
#include "r_spi_api.h"
#include "r_flash_hp.h"
#include "r_flash_api.h"
FSP_HEADER
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer6;

/** Access the GPT instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_instance_ctrl_t g_timer6_ctrl;
extern const timer_cfg_t g_timer6_cfg;

#ifndef NULL
void NULL(timer_callback_args_t * p_args);
#endif
/** UART on SCI Instance. */
            extern const uart_instance_t      g_uart3;

            /** Access the UART instance using these structures when calling API functions directly (::p_api is not used). */
            extern sci_b_uart_instance_ctrl_t     g_uart3_ctrl;
            extern const uart_cfg_t g_uart3_cfg;
            extern const sci_b_uart_extended_cfg_t g_uart3_cfg_extend;

            #ifndef user_uart3_callback
            void user_uart3_callback(uart_callback_args_t * p_args);
            #endif
/* CEU on CAPTURE instance */
            extern const capture_instance_t g_ceu_64X32;
            /* Access the CEU instance using these structures when calling API functions directly (::p_api is not used). */
            extern ceu_instance_ctrl_t g_ceu_64X32_ctrl;
            extern const capture_cfg_t g_ceu_64X32_cfg;
            #ifndef g_ceu_callback
            void g_ceu_callback(capture_callback_args_t * p_args);
            #endif
/* CEU on CAPTURE instance */
            extern const capture_instance_t g_ceu_320X320;
            /* Access the CEU instance using these structures when calling API functions directly (::p_api is not used). */
            extern ceu_instance_ctrl_t g_ceu_320X320_ctrl;
            extern const capture_cfg_t g_ceu_320X320_cfg;
            #ifndef g_ceu_callback
            void g_ceu_callback(capture_callback_args_t * p_args);
            #endif
/* CEU on CAPTURE instance */
            extern const capture_instance_t g_ceu_160X160;
            /* Access the CEU instance using these structures when calling API functions directly (::p_api is not used). */
            extern ceu_instance_ctrl_t g_ceu_160X160_ctrl;
            extern const capture_cfg_t g_ceu_160X160_cfg;
            #ifndef g_ceu_callback
            void g_ceu_callback(capture_callback_args_t * p_args);
            #endif
/* CEU on CAPTURE instance */
            extern const capture_instance_t g_ceu_128X128;
            /* Access the CEU instance using these structures when calling API functions directly (::p_api is not used). */
            extern ceu_instance_ctrl_t g_ceu_128X128_ctrl;
            extern const capture_cfg_t g_ceu_128X128_cfg;
            #ifndef g_ceu_callback
            void g_ceu_callback(capture_callback_args_t * p_args);
            #endif
/* CEU on CAPTURE instance */
            extern const capture_instance_t g_ceu_128X64;
            /* Access the CEU instance using these structures when calling API functions directly (::p_api is not used). */
            extern ceu_instance_ctrl_t g_ceu_128X64_ctrl;
            extern const capture_cfg_t g_ceu_128X64_cfg;
            #ifndef g_ceu_callback
            void g_ceu_callback(capture_callback_args_t * p_args);
            #endif
/* CEU on CAPTURE instance */
            extern const capture_instance_t g_ceu_64X64;
            /* Access the CEU instance using these structures when calling API functions directly (::p_api is not used). */
            extern ceu_instance_ctrl_t g_ceu_64X64_ctrl;
            extern const capture_cfg_t g_ceu_64X64_cfg;
            #ifndef g_ceu_callback
            void g_ceu_callback(capture_callback_args_t * p_args);
            #endif
/** SPI on SCI Instance. */
extern const spi_instance_t g_sci_spi2;

/** Access the SCI_B_SPI instance using these structures when calling API functions directly (::p_api is not used). */
extern sci_b_spi_instance_ctrl_t g_sci_spi2_ctrl;
extern const spi_cfg_t g_sci_spi2_cfg;

/** Called by the driver when a transfer has completed or an error has occurred (Must be implemented by the user). */
#ifndef sci_spi2_callback
void sci_spi2_callback(spi_callback_args_t * p_args);
#endif
/* Flash on Flash HP Instance */
extern const flash_instance_t g_flash;

/** Access the Flash HP instance using these structures when calling API functions directly (::p_api is not used). */
extern flash_hp_instance_ctrl_t g_flash_ctrl;
extern const flash_cfg_t g_flash_cfg;

#ifndef NULL
void NULL(flash_callback_args_t * p_args);
#endif
/* CEU on CAPTURE instance */
            extern const capture_instance_t g_ceu_hqqvga;
            /* Access the CEU instance using these structures when calling API functions directly (::p_api is not used). */
            extern ceu_instance_ctrl_t g_ceu_hqqvga_ctrl;
            extern const capture_cfg_t g_ceu_hqqvga_cfg;
            #ifndef g_ceu_callback
            void g_ceu_callback(capture_callback_args_t * p_args);
            #endif
/* CEU on CAPTURE instance */
            extern const capture_instance_t g_ceu_hvga;
            /* Access the CEU instance using these structures when calling API functions directly (::p_api is not used). */
            extern ceu_instance_ctrl_t g_ceu_hvga_ctrl;
            extern const capture_cfg_t g_ceu_hvga_cfg;
            #ifndef g_ceu_callback
            void g_ceu_callback(capture_callback_args_t * p_args);
            #endif
/* CEU on CAPTURE instance */
            extern const capture_instance_t g_ceu_hqvga;
            /* Access the CEU instance using these structures when calling API functions directly (::p_api is not used). */
            extern ceu_instance_ctrl_t g_ceu_hqvga_ctrl;
            extern const capture_cfg_t g_ceu_hqvga_cfg;
            #ifndef g_ceu_callback
            void g_ceu_callback(capture_callback_args_t * p_args);
            #endif
/* CEU on CAPTURE instance */
            extern const capture_instance_t g_ceu_qqqvga;
            /* Access the CEU instance using these structures when calling API functions directly (::p_api is not used). */
            extern ceu_instance_ctrl_t g_ceu_qqqvga_ctrl;
            extern const capture_cfg_t g_ceu_qqqvga_cfg;
            #ifndef g_ceu_callback
            void g_ceu_callback(capture_callback_args_t * p_args);
            #endif
/* CEU on CAPTURE instance */
            extern const capture_instance_t g_ceu_svga;
            /* Access the CEU instance using these structures when calling API functions directly (::p_api is not used). */
            extern ceu_instance_ctrl_t g_ceu_svga_ctrl;
            extern const capture_cfg_t g_ceu_svga_cfg;
            #ifndef g_ceu_callback
            void g_ceu_callback(capture_callback_args_t * p_args);
            #endif
/* CEU on CAPTURE instance */
            extern const capture_instance_t g_ceu_vga;
            /* Access the CEU instance using these structures when calling API functions directly (::p_api is not used). */
            extern ceu_instance_ctrl_t g_ceu_vga_ctrl;
            extern const capture_cfg_t g_ceu_vga_cfg;
            #ifndef g_ceu_callback
            void g_ceu_callback(capture_callback_args_t * p_args);
            #endif
/* CEU on CAPTURE instance */
            extern const capture_instance_t g_ceu_qvga;
            /* Access the CEU instance using these structures when calling API functions directly (::p_api is not used). */
            extern ceu_instance_ctrl_t g_ceu_qvga_ctrl;
            extern const capture_cfg_t g_ceu_qvga_cfg;
            #ifndef g_ceu_callback
            void g_ceu_callback(capture_callback_args_t * p_args);
            #endif
/* CEU on CAPTURE instance */
            extern const capture_instance_t g_ceu_qqvga;
            /* Access the CEU instance using these structures when calling API functions directly (::p_api is not used). */
            extern ceu_instance_ctrl_t g_ceu_qqvga_ctrl;
            extern const capture_cfg_t g_ceu_qqvga_cfg;
            #ifndef g_ceu_callback
            void g_ceu_callback(capture_callback_args_t * p_args);
            #endif
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer3;

/** Access the GPT instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_instance_ctrl_t g_timer3_ctrl;
extern const timer_cfg_t g_timer3_cfg;

#ifndef NULL
void NULL(timer_callback_args_t * p_args);
#endif
/** UART on SCI Instance. */
            extern const uart_instance_t      g_uart9;

            /** Access the UART instance using these structures when calling API functions directly (::p_api is not used). */
            extern sci_b_uart_instance_ctrl_t     g_uart9_ctrl;
            extern const uart_cfg_t g_uart9_cfg;
            extern const sci_b_uart_extended_cfg_t g_uart9_cfg_extend;

            #ifndef user_uart9_callback
            void user_uart9_callback(uart_callback_args_t * p_args);
            #endif
void hal_entry(void);
void g_hal_init(void);
FSP_FOOTER
#endif /* HAL_DATA_H_ */
