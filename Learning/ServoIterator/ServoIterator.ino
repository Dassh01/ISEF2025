#include <Servo.h>

Servo servo;

const int MAX = 180;
const int MIN = 0;
const int SERVO_PORT = 8;
const int analogInPin = A0;

int tick = 100;
int sensorValue;
char tickAsString[4];
bool goingDownFlag = false;

void setup() {
  
  Serial.begin(9600);
  servo.attach(SERVO_PORT);
}

void loop() {

  sensorValue = analogRead(analogInPin);

  if (tick < MAX && !goingDownFlag) {
    tick++;
  }
  else {
    goingDownFlag = true;
    tick--;
    if (tick <= MIN) {
      goingDownFlag = false;
    }
  }


  Serial.print("Tick: ");
  Serial.print(tick);
  Serial.print(",");
  Serial.print("Muscle sensor: ");
  Serial.println(sensorValue);

  delay(50);
}
