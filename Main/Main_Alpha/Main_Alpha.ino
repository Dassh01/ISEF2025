const int frontMuscleSensorCommsPin = A0; 
const int backMuscleSensorCommsPin = A1;

const int frontServoCommsPin = 9;
const int backServoCommsPin = 8;

const int MAX_SERVO_TICKS = 180;
const int MIN_SERVO_TICKS = 0;

const int SERVO_MAXIMUM_MOVEMENT_LIMIT
const int FRONT_SERVO_INIT_POS = 0; //TODO: UPDATE
const int BACK_SERVO_INIT_POS = 0; //TODO: UPDATE

const int MAX_MUSCLE_SENSOR_OUTPUT = 0; //TODO: UPDATE
const int MIN_MUSCLE_SENSOR_OUTPUT = 0 //TODO: UPDATE

int frontServoPosition = 0;
int backServoPosition = 0;

Servo frontServo;
Servo backServo;

int getFrontMuscleSensorValue() {
  return analogRead(frontMuscleSensorCommsPin);
}

int getBackMuscleSensorValue() {
  return analogRead(backMuscleSensorCommsPin);
}

int getFrontServoPositio() {
  return map(getFrontMuscleSensorValue(),MIN_MUSCLE_SENSOR_OUTPUT,MAX_MUSCLE_SENSOR_OUTPUT,MIN_SERVO_TICKS,MAX_SERVO_TICKS);
}

int getbackServoPosition() {
  return map(getFrontMuscleSensorValue(),MIN_MUSCLE_SENSOR_OUTPUT,MAX_MUSCLE_SENSOR_OUTPUT,MIN_SERVO_TICKS,MAX_SERVO_TICKS);
}

void setup() {
  frontServo.attach(frontServoCommsPin);
  backServo.attach(backServoCommsPin);

  frontServo.write(FRONT_SERVO_INIT_POS)
  backServo.write(BACK_SERVO_INIT_POS)

  Serial.begin(9600);
}

void loop() {
  frontServoPosition = getFrontServoPosition();
  backServoPosition = getbackServoPosition();

  frontServo.write(frontServoPosition);
  backServo.write(backServoPosition);
}
