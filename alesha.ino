#include "include/aleshalib.h"

#define STRINGS_LIMIT 1111

String data[STRINGS_LIMIT];

void setup() {
  alesha_init ();  
}

void loop() {
  int idx = 0;
  String buf;
  while (Serial.available () > 0) {
    char incoming = Serial.read ();
    buf = buf + String{incoming};
    delay(4);
  }
  if (buf == "<end>") {
    for (int i = 0; i < idx; ++i) {
      aputs (data[i]);
    }
    idx = 0;
  }
  else if (buf.length () > 0) {
    data[idx++] = buf;
    buf = "";
  }
}

