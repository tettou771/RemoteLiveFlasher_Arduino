#include "global.h"
#include "Flash.h"

Flash *flash[flashNum];

void setup() {
  int flashPin[flashNum] = {
    A1, A2, A3, A4
  };
  for (int i = 0; i < flashNum; ++i) {
    flash[i] = new Flash(flashPin[i]);
  }

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
}
