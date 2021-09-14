//#include <SPI.h>
#include "RTClib.h"
#include "TimeString.h"

//RTC_DS3231 rtc;


void setup() {
  Serial.begin(9600);
}


void loop() {
  TimeString timestring();
  delay(100);
  //DateTime today = rtc.now();
  String time_message = "hello";//timestring.getTimeStr(today);
  Serial.println(time_message);
}
