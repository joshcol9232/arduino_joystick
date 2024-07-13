#pragma once

class ButtonToggleState {
 public:
  ButtonToggleState(const uint8_t buttonPin) :
    buttonPin_(buttonPin), state_(false), lastState_(false), justSwitched_(false)
  {}

  void poll() {
    const bool currState = buttonDown();
    const bool justSwitched_ = lastState_ == false && currState == true;
    if (justSwitched_) { state_ = !state_; }
    lastState_ = currState;
  }

  bool active() const { return state_; }
  bool justSwitched() const { return justSwitched_; }
 private:
  bool buttonDown() const { return digitalRead(buttonPin_) == HIGH; }

  const uint8_t buttonPin_;
  bool state_, lastState_, justSwitched_;
};

