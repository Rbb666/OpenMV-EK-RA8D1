
// MCU config

// module config

// peripheral config

// board config

// UART

// I2C

// SPI

// PWM

// DAC

// Switch

// LEDs
#define MICROPY_HW_LED1             (0x0600)
#define MICROPY_HW_LED2             (0x040E)
#define MICROPY_HW_LED3             (0x0107)
#define MICROPY_HW_LED_ON(pin)      mp_hal_pin_high(pin)
#define MICROPY_HW_LED_OFF(pin)     mp_hal_pin_low(pin)
#define MICROPY_HW_LED_TOGGLE(pin)  mp_hal_pin_toggle(pin)
