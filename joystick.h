#pragma once

#include "vec.h"
#include "common.h"

namespace {

float potentiometerPercent(const int val, const int max_val = 1023) {
  return (float)val / (float)max_val;
}

}  // namespace

// Joystick representation.
class JoyStick {
 public:
  JoyStick() : calibrated_(false) {}

  JoyStick(const uint8_t x_pin, const uint8_t y_pin)
    : calibrated_(false), xPin_(x_pin), yPin_(y_pin),
      max_{ -1e3, -1e3 }, min_{ 1e3, 1e3 } {
    // Initialisation phase.
    lastPos_ = rawRead();
  }

  void printState() {
    Serial.print("JoyStick { pos = ");
    lastPos_.print();
    Serial.print(", min = ");
    min_.print();
    Serial.print(", max = ");
    max_.print();
    Serial.print(", centre_pos = ");
    centrePos_.print();
    Serial.print(" }");
  }

  void poll() {
    lastPos_ = read();

    if (!calibrated_) {
      calibrated_ = calibrateStep();
    }

    if constexpr (ENABLE_JOYSTICK_PRINTS) {
      printState();
      Serial.println();
    }
  }

  const Vec& pos() const { return lastPos_; }
  float x() const { return pos().x_; }
  float y() const { return pos().y_; }

  float xCentred() const { return pos().x_ - centrePos_.x_; }
  float yCentred() const { return pos().y_ - centrePos_.y_; }
  Vec posCentred() const { return Vec { xCentred(), yCentred() }; }

 private:
  bool calibrateStep() {
    centrePos_ = rawRead();
    return true;
  }
  // // Calibration notes:
  // // - Assumes that the starting position of the joystick is the centre (i.e, no one is touching the joystick).
  // // - Length of the extent from the starting position - first min/max position defines the dead zones.
  // bool calibrate_step() {
  //   constexpr int DELAY_MS = 20;
  //   // N * delay =~ roughly total time scanning in ms.
  //   constexpr int NUM_CALIBRATION_READINGS = CALIBRATION_DURATION_MS / DELAY_MS;

  //   static int curr_step = NUM_CALIBRATION_READINGS;

  //   if (curr_step == NUM_CALIBRATION_READINGS) {
  //     digitalWrite(CALIBRATION_LED_PIN, HIGH);
  //     centre_pos_ = raw_read();
  //   }

  //   {
  //     // set_pwm_led((float)(curr_step) / (float)NUM_CALIBRATION_READINGS, debug::STATUS_LED_PIN);

  //     const float x_read = raw_read_x() - centre_pos_.x_;
  //     const float y_read = raw_read_y() - centre_pos_.y_;

  //     if (x_read > max_.x_) {
  //       max_.x_ = x_read;
  //     } else if (x_read < min_.x_) {
  //       min_.x_ = x_read;
  //     }

  //     if (y_read > max_.y_) {
  //       max_.y_ = y_read;
  //     } else if (y_read < min_.y_) {
  //       min_.y_ = y_read;
  //     }
  //   }

  //   --curr_step;

  //   // Finish calibration
  //   if (curr_step <= 0) {
  //     // Clamp based on whichever direction is the smallest.
  //     if (abs(min_.x_) < abs(max_.x_)) {
  //       max_.x_ = -min_.x_;
  //     } else {
  //       min_.x_ = -max_.x_;
  //     }
  //     if (abs(min_.y_) < abs(max_.y_)) {
  //       max_.y_ = -min_.y_;
  //     } else {
  //       min_.y_ = -max_.y_;
  //     }

  //     digitalWrite(CALIBRATION_LED_PIN, LOW);
  //     return true;
  //   } else {
  //     // Otherwise keep going, delay.
  //     delay(DELAY_MS);
  //     return false;
  //   }
  // }

  // // Function reads from the pin, and then adjusts based on the calibration.
  // float read_x() const {
  //   const float read = raw_read_x() - centre_pos;
    
  // }
  // float read_y() const {
  //   return 0.0;
  // }
  // inline Vec read() const {
  //   return Vec { read_x(), read_y() };
  // }

  // "Calibrated" output - for now just raw.
  inline float readX() const { return rawReadX(); }
  inline float readY() const { return rawReadY(); }
  inline Vec read() const { return rawRead(); }
  // ---
  inline float rawReadPot(const uint8_t pin) const {
    const int reading = analogRead(pin);
    return potentiometerPercent(reading);
  }
  inline float rawReadX() const {
    return rawReadPot(xPin_);
  }
  inline float rawReadY() const {
    return rawReadPot(yPin_);
  }
  inline Vec rawRead() const {
    return Vec{ rawReadX(), rawReadY() };
  }

  bool calibrated_;
  uint8_t xPin_, yPin_;
  // Starting position of the joystick assumed to be the centre.
  Vec centrePos_;
  // Extents of the joystick inputs.
  Vec max_, min_;

  Vec lastPos_;
};