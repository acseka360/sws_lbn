#ifndef _VARIANT_E73_E22_900MM22S_USB_
#define _VARIANT_E73_E22_900MM22S_USB_

#define VARIANT_MCK (64000000ul)

/* E73 module has no external 32.768 kHz crystal; use internal RC oscillator */
#define USE_LFRC

/* Board capabilities */
#define PRIVATE_HW
#define HAS_SCREEN            0
#define HAS_WIRE              0
#define HAS_GPS               0
#define HAS_SENSOR            0
#define HAS_PHYSICAL_KEYBOARD 0
#define HAS_CPU_SHUTDOWN      0

/* Exclude unused Meshtastic modules */
#define MESHTASTIC_EXCLUDE_I2C                   1
#define MESHTASTIC_EXCLUDE_ENVIRONMENTAL_SENSOR  1
#define MESHTASTIC_EXCLUDE_AIR_QUALITY_SENSOR    1
#define MESHTASTIC_EXCLUDE_DETECTIONSENSOR       1
#define MESHTASTIC_EXCLUDE_INPUTBROKER           1
#define MESHTASTIC_EXCLUDE_CANNEDMESSAGES        1
#define MESHTASTIC_EXCLUDE_GPS                   1
#define MESHTASTIC_EXCLUDE_SCREEN                1
#define MESHTASTIC_EXCLUDE_WAYPOINT              1

#include "WVariant.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * E73-2G4M08S1C + E22-900MM22S pin assignment
 *
 * MCU pin   Function
 * -------   --------------------------------------------------------
 * P0.02     SPI MISO
 * P0.03     SX1262 DIO1 / IRQ
 * P0.05     LED (active-high)
 * P0.13     3.3V rail enable for E22 and buzzer (shared supply)
 * P0.28     Battery voltage sense, 1/2 resistor divider
 * P0.29     SPI MOSI
 * P0.30     SPI SCK
 * P0.31     SX1262 NSS / CS
 * P1.09     SX1262 RXEN
 * P1.10     Buzzer via N-channel MOSFET (active-high gate)
 * P1.11     SX1262 NRST
 * P1.13     SX1262 BUSY
 *
 * Notes:
 * - On the E22-900MM22S, DIO2 is wired internally to TXEN, so the
 *   radio handles TX switching autonomously via SX126X_DIO2_AS_RF_SWITCH.
 *   The MCU only needs to drive RXEN (P1.09).
 * - P0.13 powers both the E22 and the buzzer MOSFET drain supply.
 *   PIN_POWER_EN raises this rail early in boot so the buzzer is
 *   available before the radio driver initialises.
 * - No button, GPS, I2C, or display on this PCB.
 */

#define PINS_COUNT           (48)
#define NUM_DIGITAL_PINS     (48)
#define NUM_ANALOG_INPUTS    (1)
#define NUM_ANALOG_OUTPUTS   (0)

#define BATTERY_PIN    (0 + 28)
#define ADC_MULTIPLIER 2.0      /* 1/2 resistor divider on BATTERY_PIN */

#define PIN_LED1      (0 + 5)  /* P0.05 */
#define LED_STATE_ON  1

#define PIN_BUZZER    (32 + 10) /* P1.10 — N-channel MOSFET, active-high gate */
#define BUZZER_STATE  1

/* No UART pins routed on this PCB */
#define PIN_SERIAL1_RX  (-1)
#define PIN_SERIAL1_TX  (-1)
#define PIN_SERIAL2_RX  (-1)
#define PIN_SERIAL2_TX  (-1)

/* No I2C on this PCB. Count kept at 1 so third-party library headers that
   reference the global Wire object still compile under MESHTASTIC_EXCLUDE_I2C. */
#define WIRE_INTERFACES_COUNT 1
#define PIN_WIRE_SDA  (-1)
#define PIN_WIRE_SCL  (-1)

/* SPI — shared with SX1262 */
#define SPI_INTERFACES_COUNT 1
#define PIN_SPI_MISO  (0 + 2)   /* P0.02 */
#define PIN_SPI_MOSI  (0 + 29)  /* P0.29 */
#define PIN_SPI_SCK   (0 + 30)  /* P0.30 */

#define LORA_MISO  PIN_SPI_MISO
#define LORA_MOSI  PIN_SPI_MOSI
#define LORA_SCK   PIN_SPI_SCK
#define LORA_CS    (0 + 31)     /* P0.31 */
#define LORA_DIO1  (0 + 3)      /* P0.03 */
#define LORA_RESET (32 + 11)    /* P1.11 */
#define LORA_BUSY  (32 + 13)    /* P1.13 */

/* SX1262 radio */
#define USE_SX1262

#define SX126X_CS     LORA_CS
#define SX126X_DIO1   LORA_DIO1
#define SX126X_BUSY   LORA_BUSY
#define SX126X_RESET  LORA_RESET
#define SX126X_RXEN   (32 + 9)  /* P1.09 — driven by MCU */
#define SX126X_TXEN   RADIOLIB_NC /* TXEN handled internally by DIO2 on E22-900MM22S */
#define SX126X_DIO2_AS_RF_SWITCH  /* DIO2 wired to TXEN inside E22-900MM22S module */

/* P0.13 enables the 3.3V rail for the E22 and buzzer.
   PIN_POWER_EN causes main.cpp to raise this before any module init,
   ensuring the buzzer supply is live for the boot melody.
   SX126X_POWER_EN lets the radio driver gate it for power management. */
#define PIN_POWER_EN    (0 + 13)
#define SX126X_POWER_EN (0 + 13)

#ifdef __cplusplus
}
#endif

static const uint8_t SS   = LORA_CS;
static const uint8_t MOSI = PIN_SPI_MOSI;
static const uint8_t MISO = PIN_SPI_MISO;
static const uint8_t SCK  = PIN_SPI_SCK;

#endif /* _VARIANT_E73_E22_900MM22S_USB_ */
