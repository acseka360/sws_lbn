#pragma once

#include <stdint.h>

#ifdef __cplusplus
#include "WVariant.h"
extern "C" {
#endif

#define _PINNUM(port, pin)  ((port) * 32 + (pin))

#define PINS_COUNT           (48u)
#define NUM_DIGITAL_PINS     (48u)
#define NUM_ANALOG_INPUTS    (6u)
#define NUM_ANALOG_OUTPUTS   (0u)
#define USE_LFRC

#define PIN_LED1             _PINNUM(0, 5)
#define LED_BUILTIN          PIN_LED1
#define LED_STATE_ON         1

#define PIN_BUTTON1          (-1)

#define PIN_SERIAL1_RX       (-1)
#define PIN_SERIAL1_TX       (-1)

#define PIN_WIRE_SDA         (-1)
#define PIN_WIRE_SCL         (-1)

#define PIN_SPI_MISO         _PINNUM(0, 2)
#define PIN_SPI_MOSI         _PINNUM(0, 29)
#define PIN_SPI_SCK          _PINNUM(0, 30)
#define SS                   _PINNUM(0, 31)

static const uint8_t A0 = 4;
static const uint8_t A1 = 5;
static const uint8_t A2 = 28;
static const uint8_t A3 = 29;
static const uint8_t A4 = 30;
static const uint8_t A5 = 31;

#ifdef __cplusplus
}
#endif
