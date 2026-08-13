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
