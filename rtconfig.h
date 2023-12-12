#ifndef RT_CONFIG_H__
#define RT_CONFIG_H__

/* Automatically generated file; DO NOT EDIT. */
/* RT-Thread Configuration */

/* RT-Thread Kernel */

#define RT_NAME_MAX 12
#define RT_CPUS_NR 1
#define RT_ALIGN_SIZE 8
#define RT_THREAD_PRIORITY_32
#define RT_THREAD_PRIORITY_MAX 32
#define RT_TICK_PER_SECOND 1000
#define RT_USING_OVERFLOW_CHECK
#define RT_USING_HOOK
#define RT_HOOK_USING_FUNC_PTR
#define RT_USING_IDLE_HOOK
#define RT_IDLE_HOOK_LIST_SIZE 4
#define IDLE_THREAD_STACK_SIZE 256
#define RT_USING_TIMER_SOFT
#define RT_TIMER_THREAD_PRIO 4
#define RT_TIMER_THREAD_STACK_SIZE 512

/* kservice optimization */

#define RT_USING_DEBUG
#define RT_DEBUGING_COLOR
#define RT_DEBUGING_CONTEXT
#define RT_DEBUGING_INIT

/* Inter-Thread communication */

#define RT_USING_SEMAPHORE
#define RT_USING_MUTEX
#define RT_USING_EVENT
#define RT_USING_MAILBOX
#define RT_USING_MESSAGEQUEUE

/* Memory Management */

#define RT_USING_MEMPOOL
#define RT_USING_MEMHEAP
#define RT_MEMHEAP_FAST_MODE
#define RT_USING_MEMHEAP_AS_HEAP
#define RT_USING_MEMHEAP_AUTO_BINDING
#define RT_USING_HEAP
#define RT_USING_DEVICE
#define RT_USING_CONSOLE
#define RT_CONSOLEBUF_SIZE 128
#define RT_CONSOLE_DEVICE_NAME "uart9"
#define RT_VER_NUM 0x50100
#define RT_BACKTRACE_LEVEL_MAX_NR 32
#define RT_USING_HW_ATOMIC
#define RT_USING_CPU_FFS
#define ARCH_ARM
#define ARCH_ARM_CORTEX_M
#define ARCH_ARM_CORTEX_M85

/* RT-Thread Components */

#define RT_USING_COMPONENTS_INIT
#define RT_USING_USER_MAIN
#define RT_MAIN_THREAD_STACK_SIZE 2048
#define RT_MAIN_THREAD_PRIORITY 10
#define RT_USING_MSH
#define RT_USING_FINSH
#define FINSH_USING_MSH
#define FINSH_THREAD_NAME "tshell"
#define FINSH_THREAD_PRIORITY 20
#define FINSH_THREAD_STACK_SIZE 4096
#define FINSH_USING_HISTORY
#define FINSH_HISTORY_LINES 5
#define FINSH_USING_SYMTAB
#define FINSH_CMD_SIZE 80
#define MSH_USING_BUILT_IN_COMMANDS
#define FINSH_USING_DESCRIPTION
#define FINSH_ARG_MAX 10
#define FINSH_USING_OPTION_COMPLETION

/* DFS: device virtual file system */

#define RT_USING_DFS
#define DFS_USING_POSIX
#define DFS_USING_WORKDIR
#define DFS_FD_MAX 16
#define RT_USING_DFS_V1
#define DFS_FILESYSTEMS_MAX 4
#define DFS_FILESYSTEM_TYPES_MAX 4
#define RT_USING_DFS_ELMFAT

/* elm-chan's FatFs, Generic FAT Filesystem Module */

#define RT_DFS_ELM_CODE_PAGE 437
#define RT_DFS_ELM_WORD_ACCESS
#define RT_DFS_ELM_USE_LFN_3
#define RT_DFS_ELM_USE_LFN 3
#define RT_DFS_ELM_LFN_UNICODE_0
#define RT_DFS_ELM_LFN_UNICODE 0
#define RT_DFS_ELM_MAX_LFN 255
#define RT_DFS_ELM_DRIVES 2
#define RT_DFS_ELM_MAX_SECTOR_SIZE 512
#define RT_DFS_ELM_REENTRANT
#define RT_DFS_ELM_MUTEX_TIMEOUT 3000
#define RT_USING_DFS_DEVFS
#define RT_USING_FAL
#define FAL_DEBUG_CONFIG
#define FAL_DEBUG 1
#define FAL_PART_HAS_TABLE_CFG

/* Device Drivers */

#define RT_USING_DEVICE_IPC
#define RT_UNAMED_PIPE_NUMBER 64
#define RT_USING_SERIAL
#define RT_USING_SERIAL_V2
#define RT_SERIAL_USING_DMA
#define RT_USING_HWTIMER
#define RT_USING_I2C
#define RT_USING_I2C_BITOPS
#define RT_USING_PIN
#define RT_USING_MTD_NOR
#define RT_USING_RTC
#define RT_USING_SOFT_RTC
#define RT_USING_SPI
#define RT_USING_SPI_MSD

/* Using USB */

#define RT_USING_USB

/* C/C++ and POSIX layer */

/* ISO-ANSI C layer */

/* Timezone and Daylight Saving Time */

#define RT_LIBC_USING_LIGHT_TZ_DST
#define RT_LIBC_TZ_DEFAULT_HOUR 8
#define RT_LIBC_TZ_DEFAULT_MIN 0
#define RT_LIBC_TZ_DEFAULT_SEC 0

/* POSIX (Portable Operating System Interface) layer */

#define RT_USING_POSIX_FS

/* Interprocess Communication (IPC) */


/* Socket is in the 'Network' category */


/* Network */


/* Utilities */


/* Memory management */


/* Memory protection */


/* RT-Thread online packages */

/* IoT - internet of things */


/* Wi-Fi */

/* Marvell WiFi */


/* Wiced WiFi */


/* CYW43012 WiFi */


/* IoT Cloud */


/* security packages */


/* language packages */

/* JSON: JavaScript Object Notation, a lightweight data-interchange format */


/* XML: Extensible Markup Language */

#define PKG_USING_MICROPYTHON

/* Hardware Module */

#define MICROPYTHON_USING_MACHINE_UART
#define MICROPYTHON_USING_MACHINE_RTC
#define MICROPYTHON_USING_MACHINE_TIMER

/* System Module */

#define MICROPYTHON_USING_UOS
#define MICROPYTHON_USING_FILE_SYNC_VIA_IDE
#define MICROPYTHON_USING_THREAD

/* Tools Module */

#define MICROPYTHON_USING_CMATH
#define MICROPYTHON_USING_UJSON
#define MICROPYTHON_USING_URE
#define MICROPYTHON_USING_UZLIB
#define MICROPYTHON_USING_URANDOM

/* Network Module */


/* User Extended Module */

#define PKG_MICROPYTHON_HEAP_SIZE 16384
#define PKG_USING_MICROPYTHON_V11300
#define PKG_MICROPYTHON_VER_NUM 0x11300

/* multimedia packages */

/* LVGL: powerful and easy-to-use embedded GUI library */


/* u8g2: a monochrome graphic library */


/* tools packages */

#define PKG_USING_CMBACKTRACE
#define PKG_CMBACKTRACE_PLATFORM_M7
#define PKG_CMBACKTRACE_DUMP_STACK
#define PKG_CMBACKTRACE_PRINT_ENGLISH
#define PKG_USING_CMBACKTRACE_V10401
#define PKG_CMBACKTRACE_VER_NUM 0x10401

/* system packages */

/* enhanced kernel services */


/* acceleration: Assembly language or algorithmic acceleration packages */


/* CMSIS: ARM Cortex-M Microcontroller Software Interface Standard */


/* Micrium: Micrium software products porting for RT-Thread */

#define PKG_USING_FREERTOS_WRAPPER
#define PKG_USING_FREERTOS_WRAPPER_LATEST_VERSION
#define PKG_USING_TINYUSB
#define PKG_TINYUSB_STACK_SIZE 2048
#define PKG_TINYUSB_THREAD_PRIORITY 8
#define PKG_TINYUSB_MEM_SECTION ".data"
#define PKG_TINYUSB_MEM_ALIGN 4
#define PKG_TINYUSB_RHPORT_NUM_2
#define PKG_TINYUSB_RHPORT_NUM 1
#define PKG_TINYUSB_HIGH_SPEED
#define PKG_TINYUSB_DEVICE_PORT_SPEED 0x20
#define PKG_TINYUSB_DEVICE_ENABLE
#define PKG_TINYUSB_DEVICE_VID 0x1209
#define PKG_TINYUSB_DEVICE_PID 0xABD1
#define PKG_TINYUSB_DEVICE_MANUFACTURER "RA8"
#define PKG_TINYUSB_DEVICE_PRODUCT "OpenMV Cam USB COM Port"
#define PKG_TINYUSB_EDPT0_SIZE 64
#define PKG_TINYUSB_DEVICE_CURRENT 100
#define PKG_TINYUSB_DEVICE_CDC
#define CFG_TUD_CDC 1
#define PKG_TINYUSB_DEVICE_CDC_STRING "TinyUSB CDC"
#define PKG_TINYUSB_DEVICE_CDC_EPNUM_NOTIF 1
#define PKG_TINYUSB_DEVICE_CDC_EPNUM 2
#define PKG_TINYUSB_DEVICE_CDC_RX_BUFSIZE 512
#define PKG_TINYUSB_DEVICE_CDC_TX_BUFSIZE 512
#define PKG_TINYUSB_DEBUG_ERROR
#define CFG_TUSB_DEBUG 1
#define PKG_USING_TINYUSB_V01400

/* peripheral libraries and drivers */

/* sensors drivers */


/* touch drivers */


/* Kendryte SDK */


/* AI packages */


/* Signal Processing and Control Algorithm Packages */


/* miscellaneous packages */

/* project laboratory */

/* samples: kernel and components samples */


/* entertainment: terminal games and other interesting software packages */


/* Arduino libraries */


/* Projects and Demos */


/* Sensors */


/* Display */


/* Timing */


/* Data Processing */


/* Data Storage */

/* Communication */


/* Device Control */


/* Other */


/* Signal IO */


/* Uncategorized */

#define SOC_FAMILY_RENESAS
#define SOC_SERIES_R7FA8M85

/* Hardware Drivers Config */

#define SOC_R7FA8D1AH

/* On-chip Peripheral Drivers */

#define BSP_USING_GPIO
#define BSP_USING_ONCHIP_FLASH
#define BSP_USING_UART
#define BSP_USING_UART9
#define BSP_UART9_RX_BUFSIZE 256
#define BSP_UART9_TX_BUFSIZE 0
#define BSP_USING_SCI_SPI
#define BSP_USING_SCI_SPI2
#define BSP_USING_SCI
#define BSP_USING_I2C
#define BSP_USING_I2C1
#define BSP_I2C1_SCL_PIN 0x050C
#define BSP_I2C1_SDA_PIN 0x050B
#define BSP_USING_FS
#define BSP_USING_SPICARD_FS
#define BSP_USING_LCD
#define BSP_USING_OPENMV

/* OpenMV Buffer Size Configure */

#define OPENMV_FB_SIZE 1048576
#define OPENMV_FB_ALLOC_SIZE 102400
#define OPENMV_JPEG_BUF_SIZE 1048576
#define OPENMV_HEAP_SIZE 233472
#define OPENMV_LINE_BUF_SIZE 10240

/* Camera Pins Configure */

#define DCMI_RESET_PIN_NUM 0x0705F
#define DCMI_POWER_PIN_NUM 0x0706F

/* OpenMV Extra Peripheral Configure */

#define OPENMV_USING_LCD
#define SENSOR_BUS_NAME "i2c1"
#define SENSOR_MT9V034 1
#define SENSOR_OV2640 1
#define SENSOR_OV5640 1
#define SENSOR_OV7725 1
#define SENSOR_OV7670 1
#define SENSOR_OV7690 0
#define SENSOR_OV9650 0

#endif
