#include <Arduino.h>

#define POT_PIN 4
#define SERVO_PIN 5


constexpr int POT_RAW_MIN = 0;
constexpr int POT_RAW_MAX = 4095;
constexpr int SERVO_MIN_ANGLE = 0;
constexpr int SERVO_MAX_ANGLE = 180;
constexpr uint16_t SERVO_MIN_US = 500;
constexpr uint16_t SERVO_MAX_US = 2500;
constexpr uint32_t SERVO_FREQUENCY_HZ = 50;
constexpr uint8_t SERVO_RESOLUTION_BITS = 14;

void writeServoAngle(int angle) {
  angle = constrain(angle, SERVO_MIN_ANGLE, SERVO_MAX_ANGLE);

  const uint32_t periodUs = 1000000UL / SERVO_FREQUENCY_HZ;
  const uint32_t pulseUs = map(angle, SERVO_MIN_ANGLE, SERVO_MAX_ANGLE, SERVO_MIN_US, SERVO_MAX_US);
  const uint32_t maxDuty = (1UL << SERVO_RESOLUTION_BITS) - 1;
  const uint32_t duty = (pulseUs * maxDuty) / periodUs;

  ledcWrite(SERVO_PIN, duty);
}

void setup() {
  Serial.begin(115200);
  pinMode(POT_PIN, INPUT);
  analogSetPinAttenuation(POT_PIN, ADC_11db);

  ledcAttach(SERVO_PIN, SERVO_FREQUENCY_HZ, SERVO_RESOLUTION_BITS);
  writeServoAngle(90);
}
