#include <MD_MAX72xx.h>

// Define the number of devices we have in the chain and the hardware interface
// NOTE: These pin numbers will probably not work with your hardware and may
// need to be adapted


#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES  4

#define CLK_PIN   13  // or SCK
#define DATA_PIN  11  // or MOSI
#define CS_PIN    10  // or SS


class MatrixPrinter {

MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
// Arbitrary pins
//MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

String _displayed_message;

int _brightness = 0;

public:

  MatrixPrinter() {
    mx.begin();
    mx.control(MD_MAX72XX::INTENSITY, _brightness);
    //mx.update(MD_MAX72XX::OFF);
  }

  bool printIfNeeded(String message)
  // only print if message is different to _displayed_message
  {
    bool different = false;
    for (int i=0; i<5; i++) {
      if (message[i] != _displayed_message[i]) different = true;
    }

    if (different) {
      printString(message);
      _displayed_message = message;
    }

    return different;
  }

  void printString(String message)
  // print string of length 5 to led matrix
  {
    mx.clear(3);
    //mx.update(MD_MAX72XX::OFF);
    mx.setChar((4*COL_SIZE-1), message[0]);
    mx.clear(2);
    mx.setChar((3*COL_SIZE+1), message[1]);
    mx.setChar((2*COL_SIZE+1), message[2]);
    mx.clear(1);
    mx.setChar((2*COL_SIZE-4), message[3]);
    mx.clear(0);
    mx.setChar(COL_SIZE-4, message[4]);

    mx.update();

    //mx.update(MD_MAX72XX::ON);
  }

  void changeBrightness(bool up)
  {
    if (up) {
      _brightness += 1;
    }

    else {
      _brightness -= 1;
    }

    if (_brightness < 0) _brightness = 0;
    if (_brightness > 15) _brightness = 15;

    mx.control(MD_MAX72XX::INTENSITY, _brightness);
  }

};
