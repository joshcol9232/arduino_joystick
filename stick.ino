#include "joystick.h"
#include "common.h"

constexpr bool LEONARDO = false;

// ===========================

class MainState {
  public:
    MainState(const uint8_t main_x, const uint8_t main_y) : joystick_(main_x, main_y) {}

    void update_loop() {
      joystick_.update();
    }
  private:
    JoyStick joystick_;
};

class PinSetup {
  public:
    PinSetup() {
      pinMode(CALIBRATION_LED_PIN, OUTPUT);
      pinMode(debug::STATUS_LED_PIN, OUTPUT);
    }
};


// Static vars.

PinSetup PINSETUP;
MainState main_state(X_PIN, Y_PIN);

void setup() {
  Serial.begin(LEONARDO ? 57600 : 9600);

  // constexpr int N = 2000/50;
  // for (int n = 0; n < N; ++n) {
  //   set_pwm_led( (float)(n + 1) / (float)N, debug::STATUS_LED_PIN );
  //   delay(50);
  // }
  // set_pwm_led(0.0, debug::STATUS_LED_PIN);

  if constexpr (LEONARDO) {
    while (!Serial) {
      // wait for serial port to connect. Needed for Leonardo only
    }
  }
}

void loop() {
  main_state.update_loop();
  // delay(100);
}
