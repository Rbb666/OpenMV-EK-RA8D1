#ifndef __CAM_HAL_H
#define __CAM_HAL_H

#include <rtthread.h>
#include "sensor.h"

/**
 * @brief Data structure of camera frame buffer
 */
typedef struct
{
    uint8_t *buf;               /*!< Pointer to the pixel data */
    size_t len;                 /*!< Length of the buffer in bytes */
    size_t width;               /*!< Width of the buffer in pixels */
    size_t height;              /*!< Height of the buffer in pixels */
    framesize_t framesize;      /*!< Format of the pixel data */
} camera_fb_t;

typedef struct {
    camera_fb_t fb;
    size_t fb_offset;
} cam_frame_t;

typedef struct
{
    cam_frame_t *frames;
    uint32_t frame_cnt;

    //QueueHandle_t event_queue;
    rt_mq_t frame_buffer_queue;
    struct rt_completion ceu_completion;

    capture_instance_t *ceu_instance;

    //for RGB/YUV modes
    uint16_t width;
    uint16_t height;

} cam_obj_t;

#endif
