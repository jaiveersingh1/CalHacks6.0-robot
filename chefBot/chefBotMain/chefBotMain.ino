#include <Wire.h>
#include <Servo.h>
#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Servo pearlServo;
Servo cupServo;
Adafruit_DCMotor* teaPump = AFMS.getMotor(4);

const String CMD_DISPENSE_CUP = "DispenseCup";
const String CMD_DISPENSE_PEARLS = "DispensePearls";
const String CMD_DISPENSE_TEA = "DispenseTea";

void dispenseCup() {
  Serial.println("Dispensing Cup");

  cupServo.write(180);
  delay(500);
  cupServo.write(0);
  delay(500);

  Serial.println("Cup Dispensed");
}

void dispensePearls() {
  Serial.println("Dispensing Pearls");

  pearlServo.write(180);
  delay(500);
  pearlServo.write(0);
  delay(500);

  Serial.println("Pearls Dispensed");
}

void dispenseTea() {
  Serial.println("Dispensing Tea");

  teaPump->setSpeed(255);
  teaPump->run(FORWARD);
  delay(500);
  teaPump->run(RELEASE);

  Serial.println("Tea Dispensed");
}

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps

  pearlServo.attach(9);
  cupServo.attach(10);

  AFMS.begin();  // create with the default frequency 1.6KHz

  pearlServo.write(90);
}

void loop() {
  if (Serial.available() > 0) {
    String cmd = Serial.readString();

    if (cmd.equals(CMD_DISPENSE_CUP)) {
      dispenseCup();
    } else if (cmd.equals(CMD_DISPENSE_PEARLS)) {
      dispensePearls();
    } else if (cmd.equals(CMD_DISPENSE_TEA)) {
      dispenseTea();
    } else {
      Serial.println("Unknown command " + cmd);
    }
  }
}
