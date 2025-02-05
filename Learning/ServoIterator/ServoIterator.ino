#include <Servo.h>

Servo servo;

const int MAX = 180;
const int MIN = 0;
const int SERVO_PORT = 9;

int tick = 100;
char tickAsString[4];
bool goingDownFlag = false;

void setup() {
  Serial.begin(9600);
  servo.attach(SERVO_PORT);
}

void loop() {

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


  itoa(tick,tickAsString,10);
  servo.write(tick);

  char output[12];
  strcpy(output,"tick = ");
  strcat(output,tickAsString);
  Serial.println(output);

  delay(50);
}
