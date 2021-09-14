
class TimeString {

DateTime today;

public:

  TimeString() {

  }

  String getTimeStr(DateTime today)
  // get current time in nice format
  {
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
