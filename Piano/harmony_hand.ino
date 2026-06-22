 // ARDUINO UNO - HARMONY ROBOTIC HAND MODULE
// Responsible for harmonic accompaniment using a secondary robotic finger system

#include <VarSpeedServo.h>
#include <AccelStepper.h>

#define STEP_PIN 6
#define DIR_PIN 5

// Calibration offsets for finger alignment with keys
float dif2 = 3.70;
float dif1 = 7.15;

int angulo = 0;

// Serial command variables
int men;
int cont = 0;
bool chegou = false;

// Servo motors representing harmonic fingers
VarSpeedServo s11;
VarSpeedServo s12;
VarSpeedServo s13;

// Stepper motor controlling lateral movement along the keyboard
AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);

// Harmonic chord / note sequence
const char* cifra[] = {"FA#1", "D", "A", "FA#1", "FA#1", "D", "B", "D"};


// =========================
// FINGER ACTIONS (PRESS LOGIC)
// =========================

// Finger 1 (special behavior - simplified actuation)
void d1p(){
  s13.write(100, 200, true);
}

void d1b(){
  s13.write(40, 200, true);
}

// Finger 2 press/release actions
void d2p(){
  s12.write(90, 250, true);
  delay(10);
  s12.write(155, 250, true);
}

void d2b(){
  s12.write(15, 250, true);
  delay(10);
  s12.write(155, 250, true);
}

// Finger 3 press/release actions
void d3p(){
  s11.write(90, 250, true);
  delay(10);
  s11.write(155, 250, true);
}

void d3b(){
  s11.write(15, 250, true);
  delay(10);
  s11.write(155, 250, true);
}


// =========================
// SETUP (INITIALIZATION + HOMING)
// =========================

void setup() {

  delay(5000);

  Serial.begin(9600);

  // Limit switch for homing reference
  pinMode(7, INPUT_PULLUP);

  // Attach servos to hardware pins
  s11.attach(11);
  s12.attach(12);
  s13.attach(13);

  // Move all fingers to safe initial position
  s11.write(180, 50, true);
  s12.write(180, 50, true);
  s13.write(180, 50, true);

  // Configure stepper motor speed
  stepper.setMaxSpeed(20000);

  // =========================
  // HOMING PROCEDURE
  // =========================

  stepper.setSpeed(5000);

  // Move until limit switch is triggered (calibration reference)
  while (digitalRead(7) == HIGH) {
    stepper.runSpeed();
  }

  // Reset reference position
  stepper.setCurrentPosition(0);

  stepper.setAcceleration(20000);

  // Return fingers to neutral position after homing
  s11.write(180, 70, true);
  s12.write(180, 70, true);
  s13.write(180, 70, true);

  // Preload first position in sequence
  move(3, cifra[cont]);
}


// =========================
// POSITION MAPPING (KEYBOARD MODEL)
// =========================

// Convert physical distance into stepper steps
float passos(float dist){
  return -((3200 * dist)/16.00);
}

// Map musical note to physical keyboard position
float distancia(const char* tecla){

  // Main keyboard mapping (two-hand system support)
  if(tecla == "E1") return 30.70;
  if(tecla == "E2") return 44.00;

  // Secondary harmonic hand mapping
  if(tecla == "FA#1") return 6.70;
  if(tecla == "A") return 9.90;
  if(tecla == "B") return 12.10;
  if(tecla == "D") return 15.30;
  if(tecla == "E") return 17.60;

  return -1;
}


// Move harmonic hand to target note position
void move(int dedo, const char* tecla){

  if(dedo == 1){
    stepper.moveTo(passos(distancia(tecla) - dif1));

  } else if(dedo == 2){
    stepper.moveTo(passos(distancia(tecla) - dif2));

  } else if(dedo == 3){
    stepper.moveTo(passos(distancia(tecla)));
  }
}


// Execute note press depending on finger and key type
void toca(int dedo, const char* tecla){

  if(dedo == 1){
    // Special simplified control for finger 1
    d1p();

  } else if(dedo == 2){

    // White keys vs black key logic separation
    if(tecla == "A" or tecla == "B" or tecla == "D" or tecla == "E"){
      d2b();
    }
    if(tecla == "FA#1"){
      d2p();
    }

  } else if(dedo == 3){

    if(tecla == "A" or tecla == "B" or tecla == "D" or tecla == "E"){
      d3b();
    }
    if(tecla == "FA#1"){
      d3p();
    }
  }
}


// =========================
// CONTROL FLAGS
// =========================

bool envia = 0;


// =========================
// MAIN LOOP (COMMUNICATION + SEQUENCE EXECUTION)
// =========================

void loop() {

  // Continuous stepper execution (non-blocking movement)
  stepper.run();

  // Notify external system when movement is completed
  if(stepper.distanceToGo() == 0 && chegou == 0 && envia){
    Serial.println("2"); // signal: ready for next action
    chegou = true;
  }

  // =========================
  // SERIAL COMMAND HANDLING
  // =========================

  if(Serial.available() > 0){

    men = Serial.read();

    // Command '1': execute current note
    if(men == '1'){

      toca(3, cifra[cont]);

      // Advance sequence index
      if(cont < 7) {
        cont++;
      } else {
        cont = 0;
      }

      // Pre-position next note for smooth execution
      move(3, cifra[cont]);

      chegou = 0;
    }

    // Command '3': enable ready-to-send feedback
    if(men == '3'){
      envia = 1;
    }
  }
}
