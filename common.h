#pragma once

constexpr uint8_t X_PIN = A0;
constexpr uint8_t Y_PIN = A1;
constexpr uint8_t CALIBRATION_LED_PIN = 2;

constexpr uint16_t CALIBRATION_DURATION_MS = 1000;

namespace debug {

constexpr uint8_t STATUS_LED_PIN = 3;

}  // namespace debug


void set_pwm_led(const float brightness, const uint8_t pin) {
  analogWrite(pin, (int)(brightness * 255.0));
}
