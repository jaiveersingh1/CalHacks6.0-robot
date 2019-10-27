#include <Wire.h>

const short LEFT_MOTOR_PIN = 6;
const short RIGHT_MOTOR_PIN = 5;

const String CMD_FORWARD = "forward";
const String CMD_RIGHT_TURN = "right";
const String CMD_LEFT_TURN = "left";

const String ACK_FORWARD = "doneForward";
const String ACK_RIGHT_TURN = "doneRight";
const String ACK_LEFT_TURN = "doneLeft";

const double LEFT_MOTOR_SCALE = 1.0;
const double RIGHT_MOTOR_SCALE = 0.80;

void drive(int leftPower, int rightPower) {
  analogWrite(LEFT_MOTOR_PIN, (int) min(max(leftPower * LEFT_MOTOR_SCALE, 0), 255));
  analogWrite(RIGHT_MOTOR_PIN, (int) min(max(rightPower * RIGHT_MOTOR_SCALE, 0), 255));
}

void forward(int duration = 500, bool coast = false) {
  drive(127, 127);

  delay(duration);

  if (coast) {
    for (int i = 127; i > 0; i -= 20) {
      drive(i, i);
      delay(50);
    }
  }
  drive(0, 0);
  Serial.println(ACK_FORWARD);
}

void rightTurn(int duration = 500) {
  drive(127, 0);

  delay(duration);

  drive(0, 0);
  Serial.println(ACK_RIGHT_TURN);
}

void leftTurn(int duration = 500) {
  drive(0, 127);

  delay(duration);

  drive(0, 0);
  Serial.println(ACK_LEFT_TURN);
}

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps

  pinMode(LEFT_MOTOR_PIN, OUTPUT);
  pinMode(RIGHT_MOTOR_PIN, OUTPUT);


}

void loop() {
  while (true) {
    if (Serial.available() > 0) {
      String request = Serial.readString();
      int cmdIndex = request.indexOf(',');
      if (cmdIndex == -1) {
        Serial.println("Malformed request " + request);
        continue;
      }

      String cmd = request.substring(0, cmdIndex);

      if (cmd.equals(CMD_FORWARD)) {
        int distIndex = request.indexOf(',', cmdIndex);
        int coastIndex = request.indexOf(',', distIndex);
        if (distIndex == -1 || coastIndex == -1) {
          Serial.println("Malformed forward command " + request);
          continue;
        }
        int distance = request.substring(cmdIndex, distIndex).toInt();
        bool coast = request.substring(distIndex, coastIndex).equals("true");
        forward(distance, coast);
      } else if (cmd.equals(CMD_RIGHT_TURN)) {
        int distIndex = request.indexOf(',', cmdIndex);
        if (distIndex == -1) {
          Serial.println("Malformed right turn command " + request);
          continue;
        }
        int distance = request.substring(cmdIndex, distIndex).toInt();
        rightTurn(distance);
      } else if (cmd.equals(CMD_LEFT_TURN)) {
        int distIndex = request.indexOf(',', cmdIndex);
        if (distIndex == -1) {
          Serial.println("Malformed left turn command " + request);
          continue;
        }
        int distance = request.substring(cmdIndex, distIndex).toInt();
        leftTurn(distance);
      } else {
        Serial.println("Unknown command " + cmd);
      }
    }
  }
}
