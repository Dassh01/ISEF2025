#include <Servo.h>
#include <stdio.h>
#include <stdlib.h>

//baseline = 34
Servo frontServo;
Servo backServo;

const int frontServoInitPos = 68;
const int backServoInitPos = 131; //NOTE: Limit on this servos ticks are 20-140
char receivedChar;
boolean newData = false;

const byte numChars = 32;
char receivedChars[numChars];


void setup() {
  frontServo.attach(8);
  backServo.attach(12);

  frontServo.write(frontServoInitPos);
  backServo.write(backServoInitPos);

  Serial.begin(9600);
}

void recvWithEndMarker() {
    static byte ndx = 0;
    char endMarker = '\n';
    char rc;
    
    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (rc != endMarker) {
            receivedChars[ndx] = rc;
            ndx++;
            if (ndx >= numChars) {
                ndx = numChars - 1;
            }
        }
        else {
            receivedChars[ndx] = '\0'; // terminate the string
            ndx = 0;
            newData = true;
        }
    }
}

void showNewData() {
    if (newData == true) {
        Serial.print("Received: ");
        Serial.println(receivedChars);
        newData = false;
    }
}

void removeChar(char *str, char charToRemove) {
    int i, j = 0;
    int len = strlen(str);
    for (i = 0; i < len; i++) {
        if (str[i] != charToRemove) {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

void loop() {
  recvWithEndMarker();
  showNewData();

  //Front servo specifier = '!'
  //Back servo specifier = '?'

  if (receivedChars[0] == '!') {
    
    if (receivedChars == "!init") {
      Serial.println("Running to init...");
      frontServo.write(frontServoInitPos);
    }

    removeChar(receivedChars,'!');
    Serial.print("Processed: ");
    Serial.println(receivedChars);
    frontServo.write(atoi(receivedChars));
    receivedChars[0] = '\0'; // Reset receivedChars after processing
  }
  else if (receivedChars[0] == '?') {

    if (receivedChars == "?init") {
      Serial.println("Running to init...");
      backServo.write(backServoInitPos);
    }

    removeChar(receivedChars,'?');
    Serial.print("Processed: ");
    Serial.println(receivedChars);
    backServo.write(atoi(receivedChars));
    receivedChars[0] = '\0'; // Reset receivedChars after processing
  }

  delay(500);
}
