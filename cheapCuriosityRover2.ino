// Project for the cheap curiosity rover

#define FORWARD 'F'
#define BACKWARD 'B'
#define START 'A'
#define PAUSE 'P'

const int ultraSonicTrig2 = A1;
const int ultraSonicEcho2 = A0;
const int ultraSonicVcc = 4;
const int ultraSonicTrig = 3;
const int ultraSonicEcho = 2;
const int buzzPin = 5;
const int redLEDpin1 = A5;
const int redLEDpin2 = 6;
const int greenLEDpin = 7;
const int blueLEDpin = 12;
const int motor1Pin1 = 8;
const int motor1Pin2 = 9;
const int motor2Pin1 = 10;
const int motor2Pin2 = 11;
const int motorOnOffPin = 13;
const int ldrPin = A3;

int duration;
int distance;
int distance2;
int duration2;
int ldrVal;

void setup() {
  pinMode(ldrPin, INPUT); // Read voltage through LDR
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(motorOnOffPin, OUTPUT);
  pinMode(ultraSonicTrig, OUTPUT);
  pinMode(ultraSonicEcho, INPUT);
  pinMode(ultraSonicTrig2, OUTPUT);
  pinMode(ultraSonicEcho2, INPUT);
  pinMode(buzzPin, OUTPUT);
  pinMode(redLEDpin1, OUTPUT);
  pinMode(redLEDpin2, OUTPUT);
  pinMode(greenLEDpin, OUTPUT);
  pinMode(blueLEDpin, OUTPUT);
  pinMode(ultraSonicVcc,OUTPUT);
  digitalWrite(ultraSonicVcc,HIGH);
  Serial.begin(9600);
}

void loop() {
  ldrVal = analogRead(ldrPin);
  Serial.println(ldrVal);
  distance = measureDistance(ultraSonicTrig, ultraSonicEcho);
  distance2 = measureDistance(ultraSonicTrig2, ultraSonicEcho2);
  Serial.println(distance);
  Serial.println(distance2);
  while (Serial.available() == 0) { }
  
  char command = Serial.read();
  
  switch (command) {
    case START:
      startRover();
      break;
    case PAUSE:
      pauseRover();
      break;
    case FORWARD:
      moveForward();
      break;
    case BACKWARD:
      moveBackward();
      break;
    default:
      break;
  }
}

int measureDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(20);
  digitalWrite(trigPin, LOW);
  int duration = pulseIn(echoPin, HIGH);
  return 0.017 * duration;

}

void startRover() {
  digitalWrite(motorOnOffPin, HIGH);
  controlLEDsAndBuzzer();
  stopMotors();
}

void pauseRover() {
  digitalWrite(motorOnOffPin, LOW);
  digitalWrite(buzzPin, LOW);
  digitalWrite(redLEDpin1, LOW);
  digitalWrite(redLEDpin2, LOW);
  digitalWrite(greenLEDpin, LOW);
  digitalWrite(blueLEDpin, LOW);
  stopMotors();
}

void moveForward() {
  digitalWrite(motorOnOffPin,HIGH);
  if (distance <= 40 && ldrVal < 2) {
    stopMotors();
    activateBuzzerAndLEDs();
  } else if (distance >= 40 && ldrVal > 2) {
    moveMotorsForward();
    deactivateBuzzerAndLEDs();
  } else if (distance <= 40 && ldrVal > 2) {
    stopMotors();
    activateBuzzerAndDeactivateLEDs();
  } else if (distance >= 40 && ldrVal < 2) {
    moveMotorsForward();
    deactivateBuzzerAndActivateLEDs();
  }
}

void moveBackward() {
  digitalWrite(motorOnOffPin,HIGH);
  if (distance2 <= 40 && ldrVal < 2) {
    stopMotors();
    activateBuzzerAndLEDs();
  } else if (distance2 >= 40 && ldrVal > 2) {
    moveMotorsBackward();
    deactivateBuzzerAndLEDs();
  } else if (distance2 <= 40 && ldrVal > 2) {
    stopMotors();
    activateBuzzerAndDeactivateLEDs();
  } else if (distance2 >= 40 && ldrVal < 2) {
    moveMotorsBackward();
    deactivateBuzzerAndActivateLEDs();
  }
}

void stopMotors() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
}

void moveMotorsForward() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
}

void moveMotorsBackward() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
}

void activateBuzzerAndLEDs() {
  digitalWrite(buzzPin, HIGH);
  digitalWrite(redLEDpin1, LOW);
  digitalWrite(redLEDpin2, LOW);
  digitalWrite(greenLEDpin, HIGH);
  digitalWrite(blueLEDpin, HIGH);
}

void deactivateBuzzerAndLEDs() {
  digitalWrite(buzzPin, LOW);
  digitalWrite(redLEDpin1, LOW);
  digitalWrite(redLEDpin2, LOW);
  digitalWrite(greenLEDpin, LOW);
  digitalWrite(blueLEDpin, LOW);
}
void deactivateBuzzerAndActivateLEDs() {
  digitalWrite(buzzPin, LOW);
  digitalWrite(redLEDpin1, LOW);
  digitalWrite(redLEDpin2, LOW);
  digitalWrite(greenLEDpin, HIGH);
  digitalWrite(blueLEDpin, HIGH);
}
void activateBuzzerAndDeactivateLEDs() {
  digitalWrite(buzzPin, HIGH);
  digitalWrite(redLEDpin1, LOW);
  digitalWrite(redLEDpin2, LOW);
  digitalWrite(greenLEDpin, LOW);
  digitalWrite(blueLEDpin, LOW);
}
void controlLEDsAndBuzzer() {
  if (ldrVal < 2 && distance <= 40) {
    activateBuzzerAndLEDs();
  } else if (ldrVal > 2 && distance > 40) {
    deactivateBuzzerAndLEDs();
  } else if (ldrVal < 2 && distance > 40) {
    deactivateBuzzerAndActivateLEDs();
  } else if (ldrVal > 2 && distance <= 40) {
    activateBuzzerAndDeactivateLEDs();
  }
}
