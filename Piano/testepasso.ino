#include <VarSpeedServo.h>
#include <AccelStepper.h>

#define STEP_PIN 3
#define DIR_PIN 4

VarSpeedServo s8; // cria o objeto servo
int angulo = 0; // declara origem do angulo como 0°
VarSpeedServo s9;
VarSpeedServo s10;

AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);

void d1p(){
  s8.write(40, 250, true);
  s8.write(180, 250, true);
}

void d1b(){
  s8.write(0, 150, true);
  s8.write(180, 150, true);
}

void d2p(){
  s9.write(40, 70, true);
  s9.write(180, 70, true);
}
void d2b(){
  s9.write(0, 200, true);
  s9.write(180, 200, true);
}

void d3p(){
  s10.write(40, 250, true);
  s10.write(180, 250, true);
}

void d3b(){
  s10.write(10, 70, true);
  s10.write(180, 70, true);
}




void setup() {
  Serial.begin(9600);
  pinMode(6, INPUT_PULLUP);
  // put your setup code here, to run once:
  s8.attach(8); //declara pino digital utilizado
  s9.attach(9);
  s10.attach(10);

  stepper.setMaxSpeed(5000);

  //----------- HOMING --------------

  stepper.setSpeed(-4000);

  while (digitalRead(6) == HIGH) {//low é apertado
    stepper.runSpeed();
  }

  stepper.setCurrentPosition(0);

  stepper.setAcceleration(1200);//4000  // 

  s8.write(180, 70, true);
  s9.write(180, 70, true);
  s10.write(180, 70, true);

}

float passos(float dist){
  return (6400 * dist)/16.15;
}

void loop() {
  // put your main code here, to run repeatedly:
  //stepper.runToNewPosition(3962.84); //do meio anda 13,63cm
  stepper.runToNewPosition(passos(25.14));
  //d1b();

}
