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
const float reference = 1.09;
float vcc = 5.0; // wird dann gemessen

int digits = 2;
int number;

float messenBetrieb() {
  // Lesen 1,1V-Referenz als Input mit Referenz Betriebsspannung vcc
  // Referenz Vcc und analog Input = interne Referenz 1,1V
  #if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
    ADMUX = _BV(REFS0) | _BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  #elif defined (__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__)
    ADMUX = _BV(MUX5) | _BV(MUX0);
  #elif defined (__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
    ADMUX = _BV(MUX3) | _BV(MUX2);
  #else
    ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  #endif  

  delay(10); // Warten bis Referenz eingeschwungen
  ADCSRA |= _BV(ADSC); // Start Umwandlung
  while (bit_is_set(ADCSRA,ADSC)); // Messen

  uint8_t low  = ADCL; // must read ADCL first - it then locks ADCH  
  uint8_t high = ADCH; // unlocks both

  long result = (high<<8) | low;
  float rvcc = reference * 1023L / result;
  Serial.print("Betriebsspannung: ");Serial.println(rvcc);
  analogReference(DEFAULT);  // zurückstellen auf Vcc als Referenz
  delay(10); // Warten bis Referenz eingeschwungen
  return rvcc;
}



void setup(){
  disp.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,
  updateWithDelays, leadingZeros, disableDecPoint);
  Timer1.initialize(1000); // alle 1000µs
  Timer1.attachInterrupt(updateDisplay);
  disp.setNumber(0);

  pinMode(analogInput,INPUT);
  vcc  = messenBetrieb();

}

void updateDisplay(){
  disp.refreshDisplay();
    if(vcc > 9.99){
    digits = 1;
    number = vcc * 10;
  } else {
    digits = 2;
    number = vcc * 100;
  }
  
    disp.setNumber(number,digits);

  
}

void loop(){  
//  values=analogRead(analogInput);
//  vout = (values*1.09)/1024.0;
//  vin = vout/(R2/(R1+R2));
//
//  if(vin > 9.99){
//    digits = 1;
//    number = vin * 10;
//  } else {
//    digits = 2;
//    number = vin * 100;
//  }
//  
//    disp.setNumber(number,digits);
//    delay(1000);
  
  
}
