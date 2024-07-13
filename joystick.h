#pragma once

#include "vec.h"
#include "common.h"

namespace {

float potentiometer_percent(const int val, const int max_val = 1023) {
  return (float)val / (float)max_val;
}

}  // namespace

class JoyStick {
public:
  JoyStick()
    : calibrated_(false) {}

  JoyStick(const uint8_t x_pin, const uint8_t y_pin)
    : calibrated_(false), x_pin_(x_pin), y_pin_(y_pin),
      max_{ -1e3, -1e3 }, min_{ 1e3, 1e3 } {
    // Initialisation phase.
    centre_pos_ = Vec{ read_x(), read_y() };
    last_pos_ = centre_pos_;
  }

  void update() {
    last_pos_ = read();

    if (!calibrated_) {
      calibrate_step();
      Serial.print("max = ");
      max_.print();
      Serial.print("min = ");
      min_.print();
      Serial.println();

    } else {
      Serial.print("x = ");
      Serial.println(last_pos_.x_);
      Serial.print("y = ");
      Serial.println(last_pos_.y_);
    }
  }

private:
  void calibrate_step() {
    constexpr int DELAY_MS = 20;
    // N * delay =~ roughly total time scanning in ms.
    constexpr int NUM_CALIBRATION_READINGS = CALIBRATION_DURATION_MS / DELAY_MS;

    static int curr_step = NUM_CALIBRATION_READINGS;

    if (curr_step == NUM_CALIBRATION_READINGS) {
      digitalWrite(CALIBRATION_LED_PIN, LOW);
    }

    {
      set_pwm_led((float)(curr_step) / (float)NUM_CALIBRATION_READINGS, debug::STATUS_LED_PIN);

      const float x_read = read_x();
      const float y_read = read_y();

      if (x_read > max_.x_) {
        max_.x_ = x_read;
      } else if (x_read < min_.x_) {
        min_.x_ = x_read;
      }

      if (y_read > max_.y_) {
        max_.y_ = y_read;
      } else if (y_read < min_.y_) {
        min_.y_ = y_read;
      }
    }

    --curr_step;

    // Finish calibration
    if (curr_step <= 0) {
      digitalWrite(CALIBRATION_LED_PIN, LOW);
      calibrated_ = true;
    } else {
      // Otherwise keep going, delay.
      delay(DELAY_MS);
    }
  }

  inline float read_pot(const uint8_t pin) const {
    const int reading = analogRead(pin);
    return potentiometer_percent(reading);
  }
  inline float read_x() const {
    return read_pot(x_pin_);
  }
  inline float read_y() const {
    return read_pot(y_pin_);
  }
  inline Vec read() const {
    return Vec{ read_x(), read_y() };
  }

  bool calibrated_;
  uint8_t x_pin_, y_pin_;
  // Starting position of the joystick assumed to be the centre.
  Vec centre_pos_;
  // Extents of the joystick inputs.
  Vec max_, min_;

  Vec last_pos_;
};