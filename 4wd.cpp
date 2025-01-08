
#include <NewPing.h>

#define ENA 5
#define IN1 4
#define IN2 3
#define ENB 6
#define IN3 7
#define IN4 8

#define TRACK_LEFT A0
#define TRACK_RIGHT A1
#define TRACK_MIDDLE_LEFT A2
#define TRACK_MIDDLE_RIGHT A3

#define TRIG_PIN 9
#define ECHO_PIN 10

#define MAX_DISTANCE 200 
#define MOTOR_SPEED 150 

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
 
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
 
  pinMode(TRACK_LEFT, INPUT);
  pinMode(TRACK_RIGHT, INPUT);
  pinMode(TRACK_MIDDLE_LEFT, INPUT);
  pinMode(TRACK_MIDDLE_RIGHT, INPUT);

  Serial.begin(115200);
}

void loop() {
  int distance = sonar.ping_cm();
  Serial.print("Distance: ");
  Serial.println(distance);


  if (distance > 0 && distance < 20) {
    avoidObstacle();
  } else {
    followLine();
  }
}

void followLine() {
 
  bool left = digitalRead(TRACK_LEFT);
  bool middleLeft = digitalRead(TRACK_MIDDLE_LEFT);
  bool middleRight = digitalRead(TRACK_MIDDLE_RIGHT);
  bool right = digitalRead(TRACK_RIGHT);

 
  if (!middleLeft && !middleRight) {
    moveForward();
  } else if (!left) {
    turnLeft();
  } else if (!right) {
    turnRight();
  } else {
    stopMotors();
  }
}

void avoidObstacle() {
  stopMotors();
  delay(500);
  moveBackward();
  delay(500);
  turnRight();
  delay(500);
}

void moveForward() {
  analogWrite(ENA, MOTOR_SPEED);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  analogWrite(ENB, MOTOR_SPEED);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void moveBackward() {
  analogWrite(ENA, MOTOR_SPEED);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  analogWrite(ENB, MOTOR_SPEED);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnLeft() {
  analogWrite(ENA, MOTOR_SPEED);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  analogWrite(ENB, MOTOR_SPEED);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnRight() {
  analogWrite(ENA, MOTOR_SPEED);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  analogWrite(ENB, MOTOR_SPEED);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
