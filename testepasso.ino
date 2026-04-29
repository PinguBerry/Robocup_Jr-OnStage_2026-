#include <AccelStepper.h>

// Define stepper pins
#define STEP_PIN 3      // Step pin
#define DIR_PIN 2       // Direction pin

// Microstepping control pins
#define MS1_PIN 7
#define MS2_PIN 6

// Steps per revolution for the motor
const float stepsPerRevolution = 200;
// Microstepping multiplier (1, 2, 4, 8, 16, or 32)
int microstepSetting = 2;

// AccelStepper instance in driver mode
AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);

void setup() {
  // Set microstepping pins as outputs
  pinMode(MS1_PIN, OUTPUT);
  pinMode(MS2_PIN, OUTPUT);

  // Set microstepping mode (adjust as needed: HIGH or LOW)
  digitalWrite(MS1_PIN, HIGH);  // Set to LOW or HIGH for desired microstep setting
  digitalWrite(MS2_PIN, LOW);  // Set to LOW or HIGH for desired microstep setting

  // Set the desired RPM and the max RPM
  float desiredRPM = 120; // Set the desired speed in rpm (revolutions per minute)
  float MaxRPM = 300; // Set max speed in rpm (revolutions per minute)

  // Calculate and set the desired and max speed in steps per second
  float speedStepsPerSec = (microstepSetting * stepsPerRevolution*desiredRPM) / 60.0;
  float Max_Speed_StepsPerSec = microstepSetting * stepsPerRevolution * MaxRPM / 60; // Specify max speed in steps/sec (converted from RPM)


  stepper.setMaxSpeed(Max_Speed_StepsPerSec);
  stepper.setAcceleration(20);

  //stepper.setSpeed(speedStepsPerSec);
}

void loop() {
  // Run the motor at constant speed
  stepper.moveTo(400);
  stepper.run();
}
