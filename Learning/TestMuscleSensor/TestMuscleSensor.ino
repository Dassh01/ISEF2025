const int analogInPin = A0; 

int sensorValue = 0;
int staticVariable = 20;

void setup() {
  Serial.begin(9600);
}

void loop() {
  //read the analog in value:
  sensorValue = analogRead(analogInPin);
  
  Serial.print("Muscle sensor feedback:");
  Serial.print(sensorValue);
  Serial.print(",");
  Serial.print(" CONST BASELINE: ");
  Serial.println( staticVariable);

  delay(2);
}
