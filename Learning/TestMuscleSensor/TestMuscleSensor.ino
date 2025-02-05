const int analogInPin = A0; 

int sensorValue = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  //read the analog in value:
  sensorValue = analogRead(analogInPin);
  
  Serial.print("muscle sensor value: ");
  Serial.print(sensorValue);

  delay(2);
}
