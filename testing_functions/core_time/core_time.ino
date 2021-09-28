#include "TimeString.h"



void setup() {
  Serial.begin(9600);
}


void loop() {
  RTCTimeString timestring;
  delay(100);
  String time_message = timestring.getTimeStr();
  Serial.println(time_message);
}
