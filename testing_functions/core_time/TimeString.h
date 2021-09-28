#include "RTClib.h"

class RTCTimeString {

RTC_DS3231 rtc;
// rtc connected with i2c pins. For arduino nano use A4 and A5. (see google for more)

public:

  RTCTimeString() {
    if (! rtc.begin()) {
      digitalWrite(LED_BUILTIN, HIGH);
      abort();
    }
    if (rtc.lostPower()) {
      Serial.println("RTC lost power, resetting time...");
      rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
  }

  String getTimeStr()
  // get current time in nice format, with blinking colon
  {
    DateTime today = rtc.now();
    char colon = getColon(today);
    String timeStr = getHourStr(today.hour()) + colon + getMinStr(today.minute()) + '\0';
    return timeStr;
  }
  
  
  String getHourStr(int timebit)
  // ensure hour string is in 12 hour format
  {
    String timeStr;
    if (timebit > 12) {
      timebit = timebit % 12;
    }
    timeStr = String(timebit);
    return timeStr;
  }
  
  
  String getMinStr(int timebit)
  // ensure minute string has 2 digits, (an extra 0 if between 0 and 10)
  {
    String timeStr = String(timebit);
    if (timeStr.length() == 1) {
      timeStr = '0' + timeStr;
    }
    return timeStr;
  }
  
  
  char getColon(DateTime today)
  // make colon flash once every second
  {
    char colon;
    if (today.second() % 2 == 0) {
      colon = ':';
    }
    else
    {
      colon = ' ';
    }
    return colon;
  }

};
