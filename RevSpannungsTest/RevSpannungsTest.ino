const float VCC = 4.63; // Gemessen in Volt!

void readInternalRef11() {
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
  float rvcc = 1.10 * 1023L / result;
  float internal1_1Ref = 1.1 * VCC / rvcc;
  Serial.print("Interne Referenz (1.1V): ");Serial.println(internal1_1Ref);
}

void setup() {
  Serial.begin(115200);
  Serial.println("Start");
}

void loop() {
  readInternalRef11();
  delay(2000);
}
