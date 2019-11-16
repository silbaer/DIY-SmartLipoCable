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

int analogInput = 0;
float vout = 0.0;
float vin = 0.0;
float R2 = 465; // Widerstandswert R2
float R1 = 9750.0; // Widerstandswert R1
int values = 0;
float reference = 1.09;

int digits = 2;
int number;




void setup(){
  disp.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,
  updateWithDelays, leadingZeros, disableDecPoint);
  Timer1.initialize(1000); // alle 1000µs
  Timer1.attachInterrupt(updateDisplay);
  disp.setNumber(0);

  pinMode(analogInput,INPUT);
  analogReference(INTERNAL);
  delay(10);


}

void updateDisplay(){
  disp.refreshDisplay();
}

void loop(){  

  

  values=analogRead(analogInput);
  vout = (values*1.09)/1024.0;
  vin = vout/(R2/(R1+R2));

  if(vin > 9.99){
    digits = 1;
    number = vin * 10;
  } else {
    digits = 2;
    number = vin * 100;
  }
  
    disp.setNumber(number,digits);
    delay(1000);
  
  
}
