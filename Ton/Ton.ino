void setup() {
  // put your setup code here, to run once:
  
pinMode(13,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(13,HIGH);
delay(200);
digitalWrite(13,LOW);
//tone(1, 3100,100); // Der zweite Ton mit der neuen Tonhöhe “200” ertönt.

delay(5000);
}
