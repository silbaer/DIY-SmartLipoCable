const float INTERN = 1.09; // bestimmt pro IC
float vcc = 5.0; // wird dann gemessen

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
  float rvcc = INTERN * 1023L / result;
  Serial.print("Betriebsspannung: ");Serial.println(rvcc);
  analogReference(DEFAULT);  // zurückstellen auf Vcc als Referenz
  delay(10); // Warten bis Referenz eingeschwungen
  return rvcc;
}

void setup() {
  Serial.begin(115200);
  Serial.println("Start");
  vcc  = messenBetrieb();
}

void loop() {
  float mess = vcc / 1023 * analogRead(A0);
  Serial.print("V = ");
  Serial.println(mess);
  delay(2000);
}
