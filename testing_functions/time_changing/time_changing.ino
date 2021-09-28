#include "TimeString.h"



int selectPin = 8;
int finishPin = 3;

volatile bool changing = false;
volatile bool just_changed = false;

void stop_changing() {
  changing = false;
  just_changed = true;
}

void setup() {
  //digitalWrite(LED_BUILTIN, HIGH);

  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(finishPin), stop_changing, RISING);
}


void loop() {
  RTCTimeString timestring;

  String time_message;

  delay(100);
  time_message = timestring.getTimeStr();
  Serial.println(time_message);
  if (digitalRead(selectPin)) {
    changing = true;
  }

  DateTime today;
  static int hour_min[2];
  bool _changing_hour;
  if (changing) {
    today = timestring.getNow();
    hour_min[0] = today.hour();
    hour_min[1] = today.minute();
    _changing_hour = true;
    Serial.println("^^   ");
    delay(500);
  }
  while (changing) {
    int change_state;
    Serial.println("CHANGING");
    if (digitalRead(selectPin)) _changing_hour = !_changing_hour;
    change_state = timestring.adjustTime(hour_min, _changing_hour);
    time_message = timestring.getChangeStr(hour_min);
    Serial.println(time_message);

    if (change_state == 1) // select
    {
      if (_changing_hour) Serial.println("^^   ");
      else Serial.println("   ^^");
      delay(500);
    }
    else if (change_state == 2 || change_state == 3) // plus or minus
    {
      delay(100);
    }
    else if (change_state == 0) // no button press. don't wait so long)
    {
      delay(25);
    }
    

  }
  if (just_changed) 
  // need to adjust RTC
  {
    timestring.finish_adjusting(hour_min);
    just_changed = false;
  }


}
