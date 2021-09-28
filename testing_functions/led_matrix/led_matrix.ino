#include "MatrixPrint.h"

MatrixPrinter mxprinter;

void setup() {
  
}

void loop() {

  String text = "11:03";
  mxprinter.printString(text);
  delay(1000);
//  text = " 8:10";
//  mxprinter.printString(text);
//  delay(1000);
}
