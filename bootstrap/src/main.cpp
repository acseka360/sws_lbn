#include <Arduino.h>
#include "Adafruit_TinyUSB.h"
#include "nrf.h"

static constexpr uint8_t LED_PIN = PIN_LED1;
static constexpr bool LED_ACTIVE_HIGH = true;

static void setLed(bool on) {
  digitalWrite(LED_PIN, (on == LED_ACTIVE_HIGH) ? HIGH : LOW);
}

static void waitForNvmc() {
  while (NRF_NVMC->READY == NVMC_READY_READY_Busy) {
  }
}

static const char *regout0_to_str(uint32_t v) {
  switch (v & UICR_REGOUT0_VOUT_Msk) {
    case (UICR_REGOUT0_VOUT_DEFAULT << UICR_REGOUT0_VOUT_Pos): return "DEFAULT";
#ifdef UICR_REGOUT0_VOUT_1V8
    case (UICR_REGOUT0_VOUT_1V8 << UICR_REGOUT0_VOUT_Pos): return "1.8V";
#endif
#ifdef UICR_REGOUT0_VOUT_2V1
    case (UICR_REGOUT0_VOUT_2V1 << UICR_REGOUT0_VOUT_Pos): return "2.1V";
#endif
#ifdef UICR_REGOUT0_VOUT_2V4
    case (UICR_REGOUT0_VOUT_2V4 << UICR_REGOUT0_VOUT_Pos): return "2.4V";
#endif
#ifdef UICR_REGOUT0_VOUT_2V7
    case (UICR_REGOUT0_VOUT_2V7 << UICR_REGOUT0_VOUT_Pos): return "2.7V";
#endif
#ifdef UICR_REGOUT0_VOUT_3V0
    case (UICR_REGOUT0_VOUT_3V0 << UICR_REGOUT0_VOUT_Pos): return "3.0V";
#endif
#ifdef UICR_REGOUT0_VOUT_3V3
    case (UICR_REGOUT0_VOUT_3V3 << UICR_REGOUT0_VOUT_Pos): return "3.3V";
#endif
    default: return "UNKNOWN";
  }
}

static void dumpPowerState() {
  uint32_t dcdcen  = NRF_POWER->DCDCEN;
  uint32_t dcdcen0 = NRF_POWER->DCDCEN0;
  uint32_t mainreg = NRF_POWER->MAINREGSTATUS;
  uint32_t regout0 = NRF_UICR->REGOUT0;

  Serial.println("=== POWER STATE ===");
  Serial.print("NRF_POWER->DCDCEN         = 0x"); Serial.println(dcdcen, HEX);
  Serial.print("NRF_POWER->DCDCEN0        = 0x"); Serial.println(dcdcen0, HEX);
  Serial.print("NRF_POWER->MAINREGSTATUS  = 0x"); Serial.println(mainreg, HEX);
  Serial.print("NRF_UICR->REGOUT0         = 0x"); Serial.println(regout0, HEX);
  Serial.print("REGOUT0 decoded           = ");   Serial.println(regout0_to_str(regout0));
  Serial.println();
}

static bool setRegout0To3V3() {
#ifdef UICR_REGOUT0_VOUT_3V3
  const uint32_t wanted = (UICR_REGOUT0_VOUT_3V3 << UICR_REGOUT0_VOUT_Pos);
#else
  return false;
#endif

  if ((NRF_UICR->REGOUT0 & UICR_REGOUT0_VOUT_Msk) == wanted) {
    return true;
  }

  NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Wen;
  waitForNvmc();

  NRF_UICR->REGOUT0 = (NRF_UICR->REGOUT0 & ~UICR_REGOUT0_VOUT_Msk) | wanted;
  waitForNvmc();

  NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Ren;
  waitForNvmc();

  return ((NRF_UICR->REGOUT0 & UICR_REGOUT0_VOUT_Msk) == wanted);
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  setLed(false);

  Serial.begin(115200);
  delay(1500);

  Serial.println();
  Serial.println("E73 REGOUT0 3.3V provisioner");
  Serial.println("This writes UICR->REGOUT0 once, then blinks forever.");
  Serial.println();

  NRF_POWER->DCDCEN  = 1;
  NRF_POWER->DCDCEN0 = 1;

  Serial.println("Before programming:");
  dumpPowerState();

  bool ok = setRegout0To3V3();

  Serial.print("setRegout0To3V3() = ");
  Serial.println(ok ? "OK" : "FAILED");
  Serial.println();

  Serial.println("After programming readback:");
  dumpPowerState();

  Serial.println("Now power-cycle the board and re-measure E73 VDD.");
  Serial.println("Expected result: VDD near 3.3V instead of ~1.8V.");
}

void loop() {
  static uint32_t last = 0;
  static bool led = false;

  uint32_t now = millis();
  if (now - last >= 500) {
    last = now;
    led = !led;
    setLed(led);
    Serial.print("uptime_ms=");
    Serial.println(now);
  dumpPowerState();
  }
}
