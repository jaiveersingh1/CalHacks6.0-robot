#include <Wire.h>
#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

Adafruit_DCMotor* rbMotor = AFMS.getMotor(1);
Adafruit_DCMotor* lbMotor = AFMS.getMotor(4);

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps

  AFMS.begin();  // create with the default frequency 1.6KHz

  rbMotor->setSpeed(75);
  lbMotor->setSpeed(75);
  rbMotor->run(FORWARD);
  lbMotor->run(FORWARD);

  delay(1000);
  
  rbMotor->run(RELEASE);
  lbMotor->run(RELEASE);
}

void loop() {
}
