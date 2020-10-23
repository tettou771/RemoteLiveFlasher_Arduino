#include "global.h"
#include "Flash.h"

Flash *flash[flashNum];

// flash when press btn
// toggle index to 0 > 1 > 2 > 3 > 0
int btnFlashIndex = 0;

void setup() {
  int flashPin[flashNum] = {
    A1, A2, A3, A4
  };
  for (int i = 0; i < flashNum; ++i) {
    flash[i] = new Flash(flashPin[i]);
  }
  pinMode(btnPin, INPUT_PULLUP);
  btnPastState = digitalRead(btnPin);

  Serial.begin(115200);
}

void loop() {
  while (Serial.available()) {
    char c = Serial.read();

    if ('0' <= c && c <= '9') {
      int num = c - '0';

      if (num < flashNum) {
        flash[num]->flash();
      }
    }
  }

  for (int i=0;i<flashNum;++i) {
    flash[i]->update();
  }

  bool btnState = digitalRead(btnPin);
  if (btnState == LOW && btnPastState == HIGH) {
    btnPressed();
    // anti chattering
    delay(50);
  } else if (btnState == HIGH && btnPastState == LOW) {
    btnReleased();
    // anti chattering
    delay(50);
  }
  btnPastState = btnState;
}

void btnPressed() {
    flash[btnFlashIndex++] -> flash();
    if (btnFlashIndex >= flashNum) btnFlashIndex = 0;
}

void btnReleased() {
  
}
