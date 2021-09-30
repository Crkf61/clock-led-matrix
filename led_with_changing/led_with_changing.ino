#include "MatrixPrint.h"
#include "TimeString.h"


MatrixPrinter mxprinter;

const int selectPin = 4;
const int minusPin = 5;
const int plusPin = 6;
const int finishPin = 3;

volatile bool changing = false;
volatile bool just_changed = false;

void stop_changing() {
  changing = false;
  just_changed = true;
}

void setup() {
  //digitalWrite(LED_BUILTIN, HIGH);
  attachInterrupt(digitalPinToInterrupt(finishPin), stop_changing, RISING);
}



void loop() {
  RTCTimeString timestring(selectPin, minusPin, plusPin);
  String time_message = timestring.getTimeStr();
  bool changed_display = mxprinter.printIfNeeded(time_message);
  digitalWrite(12, changed_display);
  delay(25);
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
    mxprinter.printIfNeeded("^^   ");
    delay(500);
  }

  else {
    int _plus = digitalRead(plusPin);
    int _minus = digitalRead(minusPin);
    if (_plus) mxprinter.changeBrightness(up=true);
    if (_minus) mxprinter.changeBrightness(up=false);
  }


  while (changing) {
    int change_state;
    if (digitalRead(selectPin)) _changing_hour = !_changing_hour;
    change_state = timestring.adjustTime(hour_min, _changing_hour);
    time_message = timestring.getChangeStr(hour_min);
    mxprinter.printIfNeeded(time_message);

    if (change_state == 1) // select
    {
      if (_changing_hour) mxprinter.printIfNeeded("^^   ");
      else mxprinter.printIfNeeded("   ^^");
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
