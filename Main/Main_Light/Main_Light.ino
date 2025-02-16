#include <Servo.h>
Servo frontServo;
int servoPos;
int muscleSensorOutput;
int MIN_MUSCLE_SENSOR_OUTPUT = 20;
int MAX_MUSCLE_SENSOR_OUTPUT = 600;
int MIN_SERVO_TICKS = 0;
int SERVO_MAXIMUM_MOVEMENT_LIMIT = 60;

void setup() {
  frontServo.attach(7);
  frontServo.write(20);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  muscleSensorOutput = analogRead(A0);
  servoPos = map(muscleSensorOutput,MIN_MUSCLE_SENSOR_OUTPUT,MAX_MUSCLE_SENSOR_OUTPUT,MIN_SERVO_TICKS,SERVO_MAXIMUM_MOVEMENT_LIMIT);

  Serial.print("Servo Pos:");
  Serial.print(servoPos);
  Serial.print(",");
  Serial.print("Muscle sensor:");
  Serial.println(muscleSensorOutput);

  frontServo.write(servoPos);
  delay(50);
}
