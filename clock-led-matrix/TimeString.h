#include "RTClib.h"

class RTCTimeString {

int _selectPin;
int _minusPin;
int _plusPin;
//int _finishPin = 3; //interrupts only work on D2 and D3
bool _changing_hour = true;


RTC_DS3231 rtc;
// rtc connected with i2c pins. For arduino nano use A4 and A5. (see google for more)

public:

  RTCTimeString(int selectpin, int minuspin, int pluspin) {
    _selectPin = selectpin;
    _minusPin = minuspin;
    _plusPin = pluspin;
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


  int adjustTime(int _hour_min[2], bool _change_hour)

  {
    int button_state = read_buttons();
    const int _minus_state = 2;
    const int _plus_state = 3;
    if (button_state == 0) {}
    else {
      int index;
      int maximum;

      if (_change_hour) {
        index = 0;
        maximum = 24;
      }

      else {
        index = 1;
        maximum = 60;
      }
      
      int new_digit = _hour_min[index];
      
      if (button_state == _minus_state) {
        new_digit -= 1;
      }
      if (button_state == _plus_state) {
        new_digit += 1;
      }
      
      new_digit = new_digit % maximum;
      if (new_digit < 0) {
        new_digit += maximum;
      }
      _hour_min[index] = new_digit;
    }
    return button_state;
  }

  
  String getChangeStr(int _hour_min[2])
  // for when adjusting time
  {
    char colon = '!';
    String timeStr = getHourStr(_hour_min[0]) + colon + getMinStr(_hour_min[1]) + '\0';
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
    if (timebit < 10) {
      timeStr = ' ' + timeStr;
    }
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

  int read_buttons()  {
    int button_state = 0;
    // read buttons in order of least important. finish pin is dealt with separately.
    if (digitalRead(_minusPin)) button_state = 2; // states correspond to position of buttons
    if (digitalRead(_plusPin)) button_state = 3;  // on breadboard
    if (digitalRead(_selectPin)) button_state = 1;
    return button_state;
  }

  DateTime getNow() {
    return rtc.now();
  }

  void finish_adjusting(int _hour_min[2])

  {
    DateTime ct = rtc.now(); // current time
    rtc.adjust(DateTime(ct.year(), ct.month(), ct.day(), _hour_min[0], _hour_min[1], 0));
  }

};
