#include <Arduino.h>

#define POT_PIN 4
#define SERVO_PIN 5

// ADC on ESP32-S3 is 12-bit in this project, so the raw read is 0..4095.
constexpr int POT_RAW_MIN = 0;
constexpr int POT_RAW_MAX = 4095;

// SG90 is not perfectly linear and the safe travel is usually a bit smaller
// than the theoretical 0..180 range, so these pulse widths are the practical
// calibration window for this particular servo.
constexpr int SERVO_MIN_ANGLE = 0;
constexpr int SERVO_MAX_ANGLE = 180;
constexpr uint16_t SERVO_MIN_US = 500;
constexpr uint16_t SERVO_MAX_US = 2500;

// Standard servo PWM is 50 Hz, meaning one period is 20 ms.
constexpr uint32_t SERVO_FREQUENCY_HZ = 50;

// 14-bit resolution was enough for a stable SG90 signal in this setup.
constexpr uint8_t SERVO_RESOLUTION_BITS = 14;

// Convert a logical angle to a PWM duty cycle for LEDC.
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

  // ESP32 Arduino core 3.x LEDC API: attach GPIO5 directly to a PWM channel.
  ledcAttach(SERVO_PIN, SERVO_FREQUENCY_HZ, SERVO_RESOLUTION_BITS);

  // Move to the middle position on boot so the arm doesn't start at an edge.
  writeServoAngle(90);
}

void loop() {
  int potValue = analogRead(POT_PIN);
  int potClamped = constrain(potValue, POT_RAW_MIN, POT_RAW_MAX);

  // Map the potentiometer span directly to servo angle.
  int servoAngle = map(potClamped, POT_RAW_MIN, POT_RAW_MAX, SERVO_MIN_ANGLE, SERVO_MAX_ANGLE);

  writeServoAngle(servoAngle);

  // Log both the raw ADC value and the interpreted angle for calibration/debugging.
  Serial.print("Potentiometer: ");
  Serial.print(potValue);
  Serial.print(" | Angle from left edge: ");
  Serial.print(servoAngle);
  Serial.println(" deg");

  delay(100);
}