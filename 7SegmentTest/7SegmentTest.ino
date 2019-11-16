#include <SevSeg.h>
#include <TimerOne.h>

  byte numDigits = 3;
  byte digitPins[3] = {2,3,4};
  byte segmentPins[8] = {5, 6, 7, 8, 9, 10, 11, 12};
  bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_ANODE; // See README.md for options
  bool updateWithDelays = false; // Default 'false' is Recommended
  bool leadingZeros = true; // Use 'true' if you'd like to keep the leading zeros
  bool disableDecPoint = false; // Use 'true' if your decimal point doesn't exist or isn't connected

  SevSeg disp;


void setup(){
  disp.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,
  updateWithDelays, leadingZeros, disableDecPoint);
  Timer1.initialize(1000); // alle 1000µs
  Timer1.attachInterrupt(updateDisplay);
  disp.setNumber(0);

}

void updateDisplay(){
  disp.refreshDisplay();
}

void loop(){  
  for(int i = 0; i<1000; i++){
    disp.setNumber(i);
    delay(100);
  }
  
  
}
