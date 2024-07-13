#pragma once

constexpr uint16_t CALIBRATION_DURATION_MS = 1000;
constexpr bool ENABLE_JOYSTICK_PRINTS = false;
constexpr bool LEONARDO = false;
constexpr bool ENABLE_SERIAL = false;


void setPWM_LED(const float brightness, const uint8_t pin) {
  analogWrite(pin, (int)(brightness * 255.0));
}

