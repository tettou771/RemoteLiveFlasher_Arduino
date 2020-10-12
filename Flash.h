#ifndef __Flash_h__
#define __Flash_h__

#include <Arduino.h>

class Flash {
  public:
    Flash(int _pin) {
      pin = _pin;
      flashState = false;
      pinMode(pin, OUTPUT);
      digitalWrite(pin, LOW);
    }

    void update() {
      if (flashState) {
        uint32_t now = millis();
        if (now > flashStartTime + flashDuration) {
          flashState = false;
          digitalWrite(pin, LOW);
        }
      }
    }

    void flash() {
      flashState = true;
      digitalWrite(pin, HIGH);
      flashStartTime = millis();
    }

  private:
    int pin;
    bool flashState;
    uint32_t flashStartTime;
    static const uint32_t flashDuration = 100;
};

#endif
