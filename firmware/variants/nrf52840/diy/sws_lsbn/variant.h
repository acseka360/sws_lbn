#ifndef _VARIANT_E73_E22_900MM22S_USB_
#define _VARIANT_E73_E22_900MM22S_USB_

/** Master clock frequency */
#define VARIANT_MCK (64000000ul)

/* No external 32.768 kHz crystal fitted on the E73 module carrier */
#define USE_LFRC

#include "WVariant.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * E73-2G4M08S1C + E22-900MM22S pin assignment
 *
 * MCU pin   Function
 * -------   ---------------------------------
 * P0.02     SPI MISO
 * P0.03     SX1262 DIO1 / IRQ
 * P0.29     SPI MOSI
 * P0.30     SPI SCK
 * P0.31     SX1262 NSS / CS
 * P1.09     SX1262 RXEN
 * P1.10     Buzzer
 * P1.11     SX1262 NRST
 * P1.13     SX1262 BUSY
 * P0.05     Heartbeat LED
 * P0.13     3.3V regulator enable
 * P0.28     Battery analog sense with /2 rdivider
 *
 * Notes:
 * - DIO2 is wired internally inside the E22-900MM22S to TXEN, so the firmware
 *   only needs to drive RXEN from the MCU.
 * - This variant intentionally disables button, GPS, I2C and display support.
 * - USB CDC remains available through the chosen nRF52 board family.
 */

#define PINS_COUNT           (48)
#define NUM_DIGITAL_PINS     (48)
#define NUM_ANALOG_INPUTS    (0)
#define NUM_ANALOG_OUTPUTS   (0)

#define BATTERY_PIN (0 + 28)
#define ADC_MULTIPLIER 2.0

/*
 * LEDs
 * Change LED_STATE_ON to 0 if your LED is wired active-low.
 */
#define PIN_LED1             (0 + 5)   /* P0.05 */
#define LED_STATE_ON         1

#define PIN_BUZZER (32 + 10)      // P1.10
#define BUZZER_STATE 1     // 1 = High to sound, 0 = Low to sound

/* No user button */

/* No hardware UART peripherals used by this board variant */
#define PIN_SERIAL1_RX       (-1)
#define PIN_SERIAL1_TX       (-1)
#define PIN_SERIAL2_RX       (-1)
#define PIN_SERIAL2_TX       (-1)

/* No external I2C bus on this hardware */
#define WIRE_INTERFACES_COUNT 1
#define PIN_WIRE_SDA         (-1)
#define PIN_WIRE_SCL         (-1)
static const uint8_t SDA = PIN_WIRE_SDA;
static const uint8_t SCL = PIN_WIRE_SCL;

/* SPI */
#define SPI_INTERFACES_COUNT 1
#define PIN_SPI_MISO         (0 + 2)   /* P0.02 */
#define PIN_SPI_MOSI         (0 + 29)  /* P0.29 */
#define PIN_SPI_SCK          (0 + 30)  /* P0.30 */

#define LORA_MISO            PIN_SPI_MISO
#define LORA_MOSI            PIN_SPI_MOSI
#define LORA_SCK             PIN_SPI_SCK
#define LORA_CS              (0 + 31)  /* P0.31 */
#define LORA_DIO1            (0 + 3)   /* P0.03 */
#define LORA_RESET           (32 + 11) /* P1.11 */
#define LORA_BUSY            (32 + 13) /* P1.13 */

static const uint8_t SS   = LORA_CS;
static const uint8_t MOSI = PIN_SPI_MOSI;
static const uint8_t MISO = PIN_SPI_MISO;
static const uint8_t SCK  = PIN_SPI_SCK;

/* Radio */
#define USE_SX1262

#define SX126X_CS            LORA_CS
#define SX126X_DIO1          LORA_DIO1
#define SX126X_BUSY          LORA_BUSY
#define SX126X_RESET         LORA_RESET
#define SX126X_RXEN          (32 + 9)  /* P1.09 */
#define SX126X_TXEN          RADIOLIB_NC
#define SX126X_DIO2_AS_RF_SWITCH
#define SX126X_POWER_EN			(0 + 13) /* P0.13 */

/* Radio power rail is always on from the 3V3 supply */
#define PIN_3V3_EN           (-1)


#ifdef __cplusplus
}
#endif

#endif /* _VARIANT_E73_E22_900MM22S_USB_ */
