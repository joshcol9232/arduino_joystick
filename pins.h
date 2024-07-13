#pragma once

constexpr uint8_t X_PIN = A0;
constexpr uint8_t Y_PIN = A1;

// Digital
constexpr uint8_t CALIBRATION_LED_PIN     = 2;
constexpr uint8_t INPUT_TOGGLE_LED_PIN    = 7;
constexpr uint8_t INPUT_TOGGLE_BUTTON_PIN = 8;

// PWM
namespace directionPins {
  constexpr uint8_t UP    = 9;
  constexpr uint8_t LEFT  = 5;
  constexpr uint8_t DOWN  = 3;
  constexpr uint8_t RIGHT = 10;
};

class PinSetup {
  public:
    PinSetup() {
      pinMode(CALIBRATION_LED_PIN, OUTPUT);

      pinMode(INPUT_TOGGLE_LED_PIN, OUTPUT);
      pinMode(INPUT_TOGGLE_BUTTON_PIN, INPUT);

      pinMode(directionPins::UP, OUTPUT);
      pinMode(directionPins::LEFT, OUTPUT);
      pinMode(directionPins::DOWN, OUTPUT);
      pinMode(directionPins::RIGHT, OUTPUT);
    }
};

