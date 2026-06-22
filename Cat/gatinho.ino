//============   LIBRARIES ============
#include <VarSpeedServo.h>
#include <SoftwareSerial.h>
=

// Create a servo object for the tail mechanism
VarSpeedServo rab;

// Function responsible for the tail movement animation
void rabinho() {
  rab.slowmove(30, 50);
  rab.wait();
  delay(5000);
  rab.slowmove(150, 50);
  rab.wait();
  delay(5000);
}

void setup() {

  // Attach the servo to pin 11
  rab.attach(11);

  // Set the tail to its initial neutral position
  rab.slowmove(90, 50);
}

void loop() {

  // Continuously execute the tail movement sequence
  rabinho();

}
