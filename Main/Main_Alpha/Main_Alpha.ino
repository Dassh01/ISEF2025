#include <Servo.h>

//TODO: CONSTANTS DOCUMENTATION
/*
PINS:
FRONT MUSCLE SENSOR COMMS: A0
BACK MUSCLE SENSOR COMMS: A1
FRONT SERVO COMMS: 7
BACK SERVO COMMS: 8
*/

//Declare constants
const int frontMuscleSensorCommsPin = A0; 
const int backMuscleSensorCommsPin = A1;

const int frontServoCommsPin = 7;
const int backServoCommsPin = 8;

//In degrees
const int SERVO_INIT_POS = 0; //TODO: UPDATE

const int MAX_SERVO_TICKS = 180;
const int MIN_SERVO_TICKS = SERVO_INIT_POS;
const int SERVO_MAXIMUM_MOVEMENT_LIMIT = 35;

const int FRONT_SERVO_INIT_POS = SERVO_INIT_POS; //TODO: UPDATE
const int BACK_SERVO_INIT_POS = SERVO_INIT_POS; //TODO: UPDATE

const int MAX_MUSCLE_SENSOR_OUTPUT = 0; //TODO: UPDATE
const int MIN_MUSCLE_SENSOR_OUTPUT = 0; //TODO: UPDATE

//Declare variables
int internalFrontServoPosition = 0;
int internalBackServoPosition = 0;

int actualFrontServoPosition = 0;
int actualBackServoPosition = 0;

//Declare variables
Servo frontServo;
Servo backServo;

//TODO: FUNCTION DOCUMENTATION

int getActualFrontServoPosition() {
  return frontServo.read();
}

int getActualBackServoPosition() {
  return backServo.read();
}

int getFrontMuscleSensorValue() {
  return analogRead(frontMuscleSensorCommsPin);
}

int getBackMuscleSensorValue() {
  return analogRead(backMuscleSensorCommsPin);
}

int getInternalFrontServoPosition() {
  return map(getFrontMuscleSensorValue(),MIN_MUSCLE_SENSOR_OUTPUT,MAX_MUSCLE_SENSOR_OUTPUT,MIN_SERVO_TICKS,SERVO_MAXIMUM_MOVEMENT_LIMIT);
}

int getInternalBackServoPosition() {
  return map(getFrontMuscleSensorValue(),MIN_MUSCLE_SENSOR_OUTPUT,MAX_MUSCLE_SENSOR_OUTPUT,MIN_SERVO_TICKS,SERVO_MAXIMUM_MOVEMENT_LIMIT);
}

void setup() {
  frontServo.attach(frontServoCommsPin);
  frontServo.write(20);
  //backServo.attach(backServoCommsPin);

  //frontServo.write(FRONT_SERVO_INIT_POS);
  //backServo.write(BACK_SERVO_INIT_POS);
  
  Serial.begin(9600);
}

void loop() {
  //Get positions to send servos to
  internalFrontServoPosition = getInternalFrontServoPosition();
  internalBackServoPosition = getInternalBackServoPosition();

  //Print internal servo positions
  Serial.print("Front servo position (internal): ");
  Serial.println(internalFrontServoPosition);
  Serial.print("Back servo position (internal): ");
  Serial.println(internalBackServoPosition);

  //Send positions to go to servos
  frontServo.write(internalFrontServoPosition);
  backServo.write(internalBackServoPosition);

  //Get actual servo positions
  actualFrontServoPosition = getActualFrontServoPosition();
  actualBackServoPosition = getActualBackServoPosition();

  //Print actual servo positions
  Serial.print("Front servo position (actual): ");
  Serial.println(actualFrontServoPosition);
  Serial.print("Back servo position (actual): ");
  Serial.println(actualBackServoPosition);

  //"Clear" screen
  for (int i=0; i<100; i++) {
   Serial.print("\n");
  }
}
