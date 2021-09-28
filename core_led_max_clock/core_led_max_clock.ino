#include "MatrixPrint.h"
#include "TimeString.h"


MatrixPrinter mxprinter;

void setup() {}

void loop() {
  RTCTimeString timestring;
  String time_message = timestring.getTimeStr();
  bool changed_display = mxprinter.printIfNeeded(time_message);
  digitalWrite(12, changed_display);
  delay(25);
}
