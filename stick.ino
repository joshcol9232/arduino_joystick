// #include <HID-Project.h>

#include "joystick.h"
#include "button_toggle.h"
#include "common.h"
#include "pins.h"

// ===========================

class MainState {
  public:
    MainState(const uint8_t mainX, const uint8_t mainY) :
      inputToggle_(INPUT_TOGGLE_BUTTON_PIN), joystick_(mainX, mainY)
    {}

    void updateLoop() {
      joystick_.poll();
      inputToggle_.poll();

      digitalWrite(INPUT_TOGGLE_LED_PIN, inputToggle_.active());

      if constexpr (ENABLE_SERIAL) Serial.println("BUTTON = " + String(inputToggle_.active()));

      // Handle reading from the joystick.
      if (inputToggle_.active()) {  // Normal print mode.
        if constexpr (ENABLE_SERIAL) {
          joystick_.printState();
          Serial.println();
        }

        setDirectionLEDs();
      }
    }
  private:
    void setDirectionLEDs() {
      const Vec posCentred = joystick_.posCentred();
      if (posCentred.x_ > 0.0) {
        setPWM_LED(posCentred.x_ * 2.0, directionPins::RIGHT);
        setPWM_LED(0.0, directionPins::LEFT);
      } else {
        setPWM_LED(-posCentred.x_ * 2.0, directionPins::LEFT);
        setPWM_LED(0.0, directionPins::RIGHT);
      }

      if (posCentred.y_ > 0.0) {
        setPWM_LED(posCentred.y_ * 2.0, directionPins::UP);
        setPWM_LED(0.0, directionPins::DOWN);
      } else {
        setPWM_LED(-posCentred.y_ * 2.0, directionPins::DOWN);
        setPWM_LED(0.0, directionPins::UP);
      }
    }

    ButtonToggleState inputToggle_;
    JoyStick joystick_;
};

// Static vars.

PinSetup PINSETUP;
MainState mainState(X_PIN, Y_PIN);

void setup() {
  if constexpr (ENABLE_SERIAL) {
    Serial.begin(9600);

    if constexpr (LEONARDO) {
      while (!Serial) {
        // wait for serial port to connect. Needed for Leonardo only
      }
    }
  }
}

void loop() {
  mainState.updateLoop();
  // delay(100);
}
