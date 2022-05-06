#include "include/aleshalib.h"

void setup() {
  alesha_init ();  
}

void loop() {
  String data;
  while (Serial.available () > 0) {
    char incoming = Serial.read ();
    data = data + String{incoming};
    delay(4);
  }
  if (data.length() > 0) {
    aputs(data);
    data = "";
  }
}

