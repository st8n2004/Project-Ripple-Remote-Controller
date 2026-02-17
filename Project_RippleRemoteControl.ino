#include "LoRaWan_APP.h"
#include "Arduino.h"

#define VRX_PIN  2
#define VRY_PIN  3

#define RF_FREQUENCY       915000000
#define TX_OUTPUT_POWER    21
#define LORA_BANDWIDTH     0
#define LORA_SPREADING_FACTOR 10
#define LORA_CODINGRATE    1
#define LORA_PREAMBLE_LENGTH 12
#define LORA_FIX_LENGTH_PAYLOAD_ON false
#define LORA_IQ_INVERSION_ON false

char txpacket[50];
bool lora_idle = true;

static RadioEvents_t RadioEvents;
void OnTxDone(void);
void OnTxTimeout(void);

void setup() {
  Serial.begin(115200);
  Mcu.begin(HELTEC_BOARD, SLOW_CLK_TPYE);

  analogSetAttenuation(ADC_11db);
  analogReadResolution(12);

  RadioEvents.TxDone = OnTxDone;
  RadioEvents.TxTimeout = OnTxTimeout;
  Radio.Init(&RadioEvents);
  Radio.SetChannel(RF_FREQUENCY);

  Radio.SetTxConfig(MODEM_LORA, TX_OUTPUT_POWER, 0, LORA_BANDWIDTH,
                    LORA_SPREADING_FACTOR, LORA_CODINGRATE,
                    LORA_PREAMBLE_LENGTH, LORA_FIX_LENGTH_PAYLOAD_ON,
                    true, 0, 0, LORA_IQ_INVERSION_ON, 2000);

  Serial.println("🎮 Joystick Transmitter Ready...");
}

void loop() {
  if (lora_idle) {
    int x = analogRead(VRX_PIN);  // Steering
    int y = analogRead(VRY_PIN);  // Throttle

    sprintf(txpacket, "X=%d,Y=%d", x, y);
    Serial.printf("📡 Sending: %s\n", txpacket);

    Radio.Send((uint8_t *)txpacket, strlen(txpacket));
    lora_idle = false;
    delay(150);
  }
  Radio.IrqProcess();
}

void OnTxDone(void) {
  Serial.println("✔️ TX Done");
  lora_idle = true;
}

void OnTxTimeout(void) {
  Serial.println("⚠️ TX Timeout");
  lora_idle = true;
}
