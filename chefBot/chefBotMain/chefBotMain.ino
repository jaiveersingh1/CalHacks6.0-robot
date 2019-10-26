#include <Wire.h>
#include <Servo.h>
#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Servo pearlServo;
Servo cupServo;
Adafruit_DCMotor* pumpMotor = AFMS.getMotor(4);

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps

  pearlServo.attach(9);
  cupServo.attach(10);

  AFMS.begin();  // create with the default frequency 1.6KHz

  pearlServo.write(90);
}

void loop() {
  if (Serial.available() > 0) {
    String nextCommand = Serial.readString();

    if (nextCommand.equals("open")) {
      Serial.print("opening\n");
      pearlServo.write(180);
    } else if (nextCommand.equals("close")) {
      Serial.print("closing\n");
      pearlServo.write(0);
    } else {
      String output = "unknown command " + nextCommand;
      Serial.print(output);
    }
  }
}
