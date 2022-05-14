#include "include/aleshalib.h"

String *data = new String[1];
int idx = 0, maxsize = 1;

void setup() {
  alesha_init ();  
}

void loop() {  
  String buf;
  while (Serial.available () > 0) {
    char incoming = Serial.read ();
    buf = buf + String{incoming};
    delay(4);
  }
  // Roll
  if (buf[0] == '`') {
    astep_v(50);
  }
  // Inversed roll
  else if (buf[0] == '$') {
    astep_v(-50);
  }
  // Flush
  else if (buf[0] == '~') {
    for (int i = 0; i < idx; ++i) {
      aputs (data[i]);
    }
    idx = 0;
  }
  // Add new string to buffer
  else if (buf.length () > 0) {
    // Increase buffer size
    if (maxsize == idx + 1) {
      String *tmp = new String[++maxsize];
      for (int i = 0; i < maxsize - 1; ++i) {
        tmp[i] = data[i];
      }
      data = tmp;
    }
    data[idx++] = buf;
    buf = "";
  }
}
