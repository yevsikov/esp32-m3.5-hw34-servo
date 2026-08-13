#include <Arduino.h>

#define POT_PIN 5
#define MIN_TONE_HZ 200
#define MAX_TONE_HZ 2000




void setup() {
  Serial.begin(115200);
  pinMode(POT_PIN, INPUT);
  analogSetPinAttenuation(POT_PIN, ADC_11db);

}

void loop() {
  int potValue = analogRead(POT_PIN);
  int buzzerFrequency = map(potValue, 0, 4095, MIN_TONE_HZ, MAX_TONE_HZ);
  Serial.print("Potentiometer Value: ");
  Serial.print(potValue);
  delay(100);
}

