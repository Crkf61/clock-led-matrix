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

public:

  MatrixPrinter() {
    mx.begin();
  }

  void printString(String message)
  // print string of length 5 to led matrix
  {
    mx.update(MD_MAX72XX::OFF);
    mx.clear();
    
    mx.setChar((4*COL_SIZE-1), message[0]);
    mx.setChar((3*COL_SIZE+1), message[1]);
    mx.setChar((2*COL_SIZE+1), message[2]);
    mx.setChar((2*COL_SIZE-4), message[3]);
    mx.setChar(COL_SIZE-4, message[4]);
  
    mx.update(MD_MAX72XX::ON);
  }

};
