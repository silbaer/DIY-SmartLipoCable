int analogInput = 0;
float vout = 0.0;
float vin = 0.0;
float R2 = 465; // Widerstandswert R1 (100K) - siehe Schaltskizze!
float R1 = 9900.0; // Widerstandswert R2 (10K) - siehe Schaltskizze!
int values = 0;
float reference = 1.09;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(analogInput,INPUT);
  analogReference(INTERNAL);
  delay(10);

}

void loop() {
  // put your main code here, to run repeatedly:
  values=analogRead(analogInput);
  vout = (values*1.09)/1024.0;
  vin = vout/(R2/(R1+R2));
  Serial.print("value: ");
  Serial.print(values);
  Serial.print(" / vin: ");
  Serial.print(vin);
  Serial.print(" / vout: ");
  Serial.print(vout);

  Serial.println();
  delay(500);

}
