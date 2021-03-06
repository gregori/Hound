#include "trekking.h"
#include "trekkingmath.h"
#include "sonarlist.h"
#include "encoderlist.h"
#include "timer.h"
#include "position.h"
#include "trekkingpins.h"
#include "PIDControler.h"
#include "XLMaxSonarEZ.h"
#include "LinkedList.h"
#include "log.h"
#include "robot.h"

#include "sensor.h"
#include "ultrasonic.h"
#include "simpleencoder.h"
#include "lightsensor.h"
#include "RoboClaw.h"
#include "BMSerial.h"


#include <Wire.h>
#include "I2Cdev.h"
#include "MPU9150Lib.h"
#include "CalLib.h"
#include <dmpKey.h>
#include <dmpmap.h>
#include <inv_mpu.h>
#include <inv_mpu_dmp_motion_driver.h>
#include <EEPROM.h>

float max_linear_vel = 2.0;
float max_angular_vel = 2.0;

DuoDriver* driver = new DuoDriver(TX_MOTOR_PIN, RX_MOTOR_PIN, ROBOCLAW_TIMEOUT, ROBOCLAW_ADDRESS);
Trekking trekking(max_linear_vel, max_angular_vel, driver);
Position *cone_1 = new Position(40, 0, 0);
Position *cone_2 = new Position(0, 0, 0);
Position *cone_3 = new Position(0, 0, 0);
BMSerial terminal(0, 1);
RoboClaw roboclaw(10, 11, 10000);

void setup() {
  pinMode(ALERT_LED, OUTPUT);
  // pinMode(SIRENE_PIN, OUTPUT);
  digitalWrite(ALERT_LED, HIGH); //states that there is a problem.
  //If the arduino could start the
  //wire i2c communication, the trekking will put it to low
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(57600);

  Wire.begin();
  trekking.addTarget(cone_1);
  trekking.addTarget(cone_2);
  trekking.addTarget(cone_3);
  trekking.start();

  driver->roboclaw.begin(38400);
}

void loop() {
  trekking.update();
}
