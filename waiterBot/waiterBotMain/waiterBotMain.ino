#include <Wire.h>

const short LEFT_MOTOR_PIN = 6;
const short RIGHT_MOTOR_PIN = 5;

const String CMD_FORWARD = "forward";
const String CMD_RIGHT_TURN = "right";
const String CMD_LEFT_TURN = "left";

const double LEFT_MOTOR_SCALE = 1.0;
const double RIGHT_MOTOR_SCALE = 0.80;

void drive(int leftPower, int rightPower) {
  analogWrite(LEFT_MOTOR_PIN, (int) min(max(leftPower * LEFT_MOTOR_SCALE, 0), 255));
  analogWrite(RIGHT_MOTOR_PIN, (int) min(max(rightPower * RIGHT_MOTOR_SCALE, 0), 255));
}

void forward(int duration = 500) {
  drive(127, 127);

  delay(duration);

  drive(0, 0);
  Serial.println("Moved forward");
}

void rightTurn(int duration = 500) {
  drive(127, 0);

  delay(duration);

  drive(0, 0);
  Serial.println("Turned right");
}

void leftTurn(int duration = 500) {
  drive(0, 127);

  delay(duration);

  drive(0, 0);
  Serial.println("Turned left");
}

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps

  pinMode(LEFT_MOTOR_PIN, OUTPUT);
  pinMode(RIGHT_MOTOR_PIN, OUTPUT);

  
}

void loop() {
  if (Serial.available() > 0) {
    String cmd = Serial.readString();

    if (cmd.equals(CMD_FORWARD)) {
      forward();
    } else if (cmd.equals(CMD_RIGHT_TURN)) {
      rightTurn();
    } else if (cmd.equals(CMD_LEFT_TURN)) {
      leftTurn();
    } else {
      Serial.println("Unknown command " + cmd);
    }
  }
}
