#include <Wire.h>
#include <Servo.h>
#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

const short CUP_SERVO_PIN = 9;
const short PEARLS_SERVO_PIN = 10;

Servo cupServo;
Servo pearlsServo;

Adafruit_DCMotor* teaPump = AFMS.getMotor(4);

const String CMD_DISPENSE_CUP = "DispenseCup";
const String CMD_DISPENSE_PEARLS = "DispensePearls";
const String CMD_DISPENSE_TEA = "DispenseTea";

const String DBG_READ_CUP = "ReadCup";
const String DBG_READ_PEARLS = "ReadPearls";
const String DBG_WRITE_CUP = "WriteCup";
const String DBG_WRITE_PEARLS = "WritePearls";

void dispenseCup() {
  Serial.println("Dispensing Cup");

  cupServo.write(0);
  delay(500);
  
  cupServo.write(120);
  delay(250);
  cupServo.write(100);
  delay(250);

  cupServo.write(120);
  delay(250);
  cupServo.write(100);
  delay(250);

  cupServo.write(120);
  delay(250);
  cupServo.write(100);
  delay(250);

  cupServo.write(0);
  delay(250);
  cupServo.write(40);
  delay(250);
  
  Serial.println("Cup Dispensed");
}

const short CLOSE_PEARLS = 40;
const short OPEN_PEARLS = 90;
const int HOLD_OPEN_PEARLS_DELAY = 5000;
const int HOLD_CLOSE_PEARLS_DELAY = 250;
const int NUM_PEARLS_SLICES = 5;

void dispensePearls() {
  Serial.println("Dispensing Pearls");

  for (int i = 0; i < NUM_PEARLS_SLICES; i++) {
    pearlsServo.write(OPEN_PEARLS);
    delay(HOLD_OPEN_PEARLS_DELAY);
    pearlsServo.write(CLOSE_PEARLS);
    delay(HOLD_CLOSE_PEARLS_DELAY);
  }

  delay(500);

  Serial.println("Pearls Dispensed");
}

const int TEA_DISPENSE_TIME = 8000;
void dispenseTea() {
  Serial.println("Dispensing Tea");

  teaPump->setSpeed(255);
  teaPump->run(FORWARD);
  delay(TEA_DISPENSE_TIME);
  teaPump->run(RELEASE);

  Serial.println("Tea Dispensed");
}

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps

  cupServo.attach(CUP_SERVO_PIN);
  pearlsServo.attach(PEARLS_SERVO_PIN);

  pearlsServo.write(CLOSE_PEARLS);

  AFMS.begin();  // create with the default frequency 1.6KHz
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
    } else if (cmd.equals(DBG_WRITE_CUP)) {
      Serial.print("Cup servo target: ");
      while (Serial.available() == 0) {}
      long target = Serial.parseInt();
      Serial.println(target);
      cupServo.write(target);
    } else if (cmd.equals(DBG_WRITE_PEARLS)) {
      Serial.print("Pearls servo target: ");
      while (Serial.available() == 0) {}
      long target = Serial.parseInt();
      Serial.println(target);
      pearlsServo.write(target);
    } else if (cmd.equals(DBG_READ_CUP)) {
      Serial.println("Cup servo at " + cupServo.read());
    } else if (cmd.equals(DBG_READ_PEARLS)) {
      Serial.println("Pearls servo at " + pearlsServo.read());
    } else {
      Serial.println("Unknown command " + cmd);
    }
  }
}
