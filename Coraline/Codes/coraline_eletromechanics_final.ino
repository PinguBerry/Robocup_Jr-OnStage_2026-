//============   LIBRARIES ============
#include <VarSpeedServo.h>
#include "SoftwareSerial.h"


//============ SERVO OBJECTS ==============
//Arms
VarSpeedServo servodb1;
VarSpeedServo servodb2;
VarSpeedServo servodb3;
VarSpeedServo servoeb1;
VarSpeedServo servoeb2;
VarSpeedServo servoeb3;

//Eyes
VarSpeedServo pdc;
VarSpeedServo pdb;
VarSpeedServo pec;
VarSpeedServo peb;
VarSpeedServo ode;
VarSpeedServo ocb;

//Mouth and neck
VarSpeedServo mouth;
VarSpeedServo neck;


//============ AUXILIARY VARIABLES ==============

unsigned long int tempo = 0;
int randomolho;
int ato;
bool ok[10];
int r = 0;
int oopa = 0;

int contx = 0;
int conty = 0;
bool okk = 0;

bool vai = 1;
bool tutu = true;

//--------------------------------> ARMS REACTIONS <-------------------------------------------

//Shock reaction
void choque_braco_right() {
  servodb1.write(90, 50, false);
  servodb2.write(0, 50, false);
  servodb3.write(120, 50, false);
}

void choque_braco_left() {
  servoeb1.write(90, 50, false);
  servoeb2.write(180, 50, false);
  servoeb3.write(70, 50, false);
}

//Normal position for both arms
void bracos_normais(){
  servoeb1.write(180, 20, false);
  servoeb2.write(90, 20, false);
  servoeb3.write(90, 20, false);
  servodb1.write(0, 20, false);
  servodb2.write(90, 20, false);
  servodb3.write(90, 20, true);
}

//Waving reaction (right arm only)
void tchauzinho_braco_right() {  
  servodb1.write(90, 50, false);
  servodb2.write(0, 50, false);
  servodb3tchauzinho();
}

void servodb3tchauzinho() {  
  servodb3.slowmove(40, 50);
  servodb3.wait();
  servodb3.slowmove(140, 50);
  servodb3.wait();
}

//Waving reaction (left arm remains still)
void tchauzinho_braco_left() {
  servoeb1.write(180, 50, false);
  servoeb2.write(90, 50, false);
  servoeb3.write(90, 50, false); 
}

//Waving reaction (both arms together)
void tchautchaus2() {  
  servodb3.write(40, 50, false);
  servoeb3.write(40, 50, true);
  servodb3.write(140, 50, false);
  servoeb3.write(140, 50, true);
}

//Alternative waving reaction using both arms together
void tchaus2() {  
  servodb1.write(90, 50, false);
  servodb2.write(0, 50, false);
  servoeb1.write(90, 50, false);
  servoeb2.write(180, 50, false);
  tchautchaus2();  //motor db3
}

//Reaction while walking
void servodb2andar() {  
  servodb2.slowmove(40, 20);
  servodb2.wait();
  servodb2.slowmove(120, 20);
  servodb2.wait();
}

void andar_braco_right() {
  servodb1.write(0, 50, false);
  servodb2andar();
  servodb3.write(90, 50, false);
}

void servoeb2andar() {
  servoeb2.slowmove(40, 20);
  servoeb2.wait();
  servoeb2.slowmove(120, 20);
  servoeb2.wait();
}

void andar_braco_left() {
  servoeb1.write(180, 50, false);
  servoeb2andar();
  servoeb3.write(90, 50, false);
}


//Greeting reaction
void estender_a_mao_braco_right() {
  servodb1.write(90, 20, false);
  servodb2.write(60, 20, false);
  servodb3.write(90, 20, false);
}

void estender_a_mao_braco_left() {
  servoeb1.write(180, 20, false);
  servoeb2.write(90, 20, false);
  servoeb3.write(90, 20, false);
}

//Reaction to protect itself from rain
void se_proteger_da_chuva_braco_right() {
  servodb1.write(180, 50, false);
  servodb2.write(90, 50, false);
  servodb3.write(120, 50, false);
}

void se_proteger_da_chuva_braco_left() {
  servoeb1.write(0, 50, false);
  servoeb2.write(95, 50, false);
  servoeb3.write(60, 50, false);
}

//Doubt reaction
void duvida_braco_right() {  
  servodb1.write(0, 50, false);
  servodb2.write(0, 50, false);
  servodb3.write(0, 50, false);
}

void duvida_braco_left() {
  servoeb1.write(180, 50, false);
  servoeb2.write(180, 50, false);
  servoeb3.write(180, 50, false);
}

//Denial reaction
void nao_braco_right() {  
  servodb1.write(90, 50, false);
  servodb2.write(80, 50, false);
  servodb3.write(90, 50, false);
}

void nao_braco_left() {
  servoeb1.write(90);
  servoeb2.write(90);
  servoeb3.write(90);
}

//--------------------------------> EYES REACTIONS <-------------------------------------------

//Shock reaction
void choque() {
  pdc.slowmove(130, 80);
  pdb.slowmove(30, 80);

  pec.slowmove(0, 80);
  peb.slowmove(100, 80);

  ode.slowmove(90, 0);
  ocb.slowmove(30, 80);
}

//Reaction to protect itself from the rain
void chuva() {
  pdc.slowmove(50, 80);
  pdb.slowmove(130, 80);

  pec.slowmove(100, 80);
  peb.slowmove(20, 80);

  ode.slowmove(90, 0);
  ocb.slowmove(30, 80);
}

//Normal reaction
void normal() {
  pdc.slowmove(75, 80);
  pdb.slowmove(105, 80);

  pec.slowmove(75, 80);
  peb.slowmove(50, 80);

  ode.slowmove(90, 0);
  ocb.slowmove(30, 80);
}

//Reaction in which Coraline scans the environment from right to left. Also sends the angles to Unity
void olharx() {
  //MOVES FROM RIGHT TO LEFT

  for (int i = 90; i <= 130; i++) {
    if (i % 10 == 0) {
      String men = "x";
      men += i;
      men += "#";
      Serial3.println(men);//  <-- Sends the angle in a padronized message (example: "x90#")

      ode.write(i, 20, true);
    }
  }

  for (int i = 130; i >= 30; i--) {
    if (i % 10 == 0) {
      String men = "x";
      men += i;
      men += "#";
      Serial3.println(men);

      ode.write(i, 20, true);
    }
  }

  for (int i = 30; i <= 90; i++) {
    if (i % 10 == 0) {
      String men = "x";
      men += i;
      men += "#";
      Serial3.println(men);

      ode.write(i, 20, true);
    }
  }
}

//Reaction in which Coraline scans the environment from top to bottom. Also sends the angles to Unity
void olhary() {
  //MOVES FROM TOP TO BOTTOM
  for (int i = 30; i <= 60; i++) {
    if (i % 10 == 0) {
      String men = "y";
      men += i;
      men += "#";
      Serial3.println(men);//  <-- Sends the angle in a padronized message (example: "x30#")

      ocb.write(i, 20, true);
    }

  }

  for (int i = 60; i >= 0; i--) {
    if (i % 10 == 0) {
      String men = "y";
      men += i;
      men += "#";
      Serial3.println(men);

      ocb.write(i, 20, true);
    }
  }

  for (int i = 0; i <= 30; i++) {
    if (i % 10 == 0) {
      String men = "y";
      men += i;
      men += "#";
      Serial3.println(men);

      ocb.write(i, 20, true);
    }
  }
}

//Random blinking reaction
void pisca() {
  ocb.slowmove(30, 80);
  ode.slowmove(90, 80);

  if (millis() - tempo >= randomolho) {  //Open eyes
    pdc.slowmove(0, 80);
    pdb.slowmove(180, 80);


    pec.slowmove(150, 100);
    peb.slowmove(0, 80);
  }

  if (millis() - tempo >= (randomolho + 700)) {  //Close eyes

    pdc.slowmove(110, 80);
    pdb.slowmove(70, 80);

    pec.slowmove(0, 80);
    peb.slowmove(100, 80);


    tempo = millis();
  }

  //Serial.println(randomolho); -- Debug
}

//--------------------------------> NECK REACTIONS <-------------------------------------------

//Head-shaking reaction (denial)
void pescoconao() {
  neck.slowmove(0, 50);
  neck.wait();
  neck.slowmove(180, 50);
  neck.wait();
}

//Normal reaction
void pescoconormal() {
  neck.slowmove(90, 50);
  neck.wait();
}

//--------------------------------> MOUTH REACTIONS <-------------------------------------------

//Speaking reaction
void falar() {
  mouth.slowmove(73, 20);
  mouth.wait();
  mouth.slowmove(85, 20);
  mouth.wait();
}

//Normal reaction
void bocanormal(){
  mouth.write(73);
}

//--------------------------------> SETUP <-------------------------------------------

void setup() {

  //Attach all servos to their respective pins.

  //Right Arm
  servodb1.attach(10);  
  servodb2.attach(9);   
  servodb3.attach(8);

  //Left Arm
  servoeb1.attach(7);   
  servoeb2.attach(6);   
  servoeb3.attach(4);

  //Left Eye
  peb.attach(22);  
  pec.attach(23);

  //Up - bottom Eye
  ocb.attach(24);
  //Right - left Eye
  ode.attach(25);

  //Right Eye
  pdb.attach(26);
  pdc.attach(27);  

  //Mouth and Neck
  mouth.attach(30);
  neck.attach(31);

  //Initializes the serial communications
  
  Serial3.begin(9600);// Bluetooth communication
  Serial2.begin(115200);// Raspberry 5 communication
  Serial.begin(115200);// Raspberry 4 communication

  //Sends all the servos to the initial position
  servoeb1.write(180);
  servoeb2.write(90);
  servoeb3.write(90);
  servodb1.write(0);
  servodb2.write(90);
  servodb3.write(90);

  normal();
  pescoconormal();
  mouth.write(85);//fechada
  randomSeed(analogRead(A1));
  randomolho = random(1500, 3000);
}

//--------------------------------> LOOP <-------------------------------------------
void loop() {

  //Checks if it's time to react
  if (r != 0) {

    if (r == 1) {// ------ * - * - REACTION 1 - * - * -------
      se_proteger_da_chuva_braco_right();
      se_proteger_da_chuva_braco_left();
      chuva();

      //If the movement has ended, exit this reaction
      if (!servodb1.isMoving() && !servodb2.isMoving() && !servodb3.isMoving() && !servoeb1.isMoving() && !servoeb2.isMoving() && !servoeb3.isMoving()) {
        r = 0;
      }

    } else if (r == 2) {// ------ * - * - REACTION 2 - * - * -------

      if(tutu){
        tempo = millis();
        tutu = false;
      }

      while(millis() - tempo <= 6000) {
        falar();
      }
      
      estender_a_mao_braco_right();
      estender_a_mao_braco_left();
      normal();

      if (!servodb1.isMoving() && !servodb2.isMoving() && !servodb3.isMoving() && !servoeb1.isMoving() && !servoeb2.isMoving() && !servoeb3.isMoving() && !mouth.isMoving()) {
        r = 0;
        tempo = 0;
        tutu = 1;
      }

    } else if (r == 3) {  // ------ * - * - REACTION 3 - * - * -------
      duvida_braco_right();
      duvida_braco_left();
      normal();

      if (!servodb1.isMoving() && !servodb2.isMoving() && !servodb3.isMoving() && !servoeb1.isMoving() && !servoeb2.isMoving() && !servoeb3.isMoving()) {
        r = 0;
      }

    } else if (r == 4) {  // ------ * - * - REACTION 4 - * - * -------
      choque_braco_right();
      choque_braco_left();
      normal();

      if (!servodb1.isMoving() && !servodb2.isMoving() && !servodb3.isMoving() && !servoeb1.isMoving() && !servoeb2.isMoving() && !servoeb3.isMoving()) {
        r = 0;
      }

    } else if (r == 5) {  // ------ * - * - REACTION 5 - * - * -------
      pdc.slowmove(75, 80);
      pdb.slowmove(105, 80);

      pec.slowmove(75, 80);
      peb.slowmove(50, 80);

      for (int i = 0; i < 3; i++) {
        olhary();
      }

      for (int i = 0; i < 3; i++) {
        olharx();
      }

      if (!servodb1.isMoving() && !servodb2.isMoving() && !servodb3.isMoving() && !servoeb1.isMoving() && !servoeb2.isMoving() && !servoeb3.isMoving() && !ocb.isMoving()) {
        r = 0;
      }

    } else if (r == 6) { // ------ * - * - REACTION 6 - * - * -------
      nao_braco_right();
      nao_braco_left();

      for(int i = 0; i < 4; i++) pescoconao();

      pescoconormal();
      choque();

      if (!servodb1.isMoving() && !servodb2.isMoving() && !servodb3.isMoving() && !servoeb1.isMoving() && !servoeb2.isMoving() && !servoeb3.isMoving() && !ocb.isMoving()) {
        r = 0;
      }
      
    }  else if (r == 7) {  // ------ * - * - REACTION 7 - * - * -------

      if(tutu){
        tempo = 0;
        tutu = false;
      }

      while(millis() - tempo <= 4000) {
        falar();
      }

      for(int i=0; i < 7; i++){
        tchaus2();
      }
      
      if (!servodb1.isMoving() && !servodb2.isMoving() && !servodb3.isMoving() && !servoeb1.isMoving() && !servoeb2.isMoving() && !servoeb3.isMoving()) {
        r = 0;
        tempo = 0;
        tutu = false;
      }
      

    } else if (r == 8) {  // ------ * - * - REACTION 8 - * - * -------

      char a = '2';
      Serial2.println(a);

      for (int i = 0; i < 10; i++) {
        tchauzinho_braco_right();
        tchauzinho_braco_left();
        pisca();
      }

      if (!servodb1.isMoving() && !servodb2.isMoving() && !servodb3.isMoving() && !servoeb1.isMoving() && !servoeb2.isMoving() && !servoeb3.isMoving()) {
        r = 0;
        tempo = millis();
        tutu = false;
      }

    } 


  } else if (r == 0) {  //If there is no reaction to do at the moment, open Serial3(Unity).

    if (Serial3.available() > 0) {
      pisca();
      ato = Serial3.read();

      //Ensures that each reaction is executed only once
      if (ato == '1' && ok[1] == 0) {  
        r = 1;
        ok[1] = 1;

      } else if (ato == '2' && ok[2] == 0) {  
        r = 2;                             
        ok[2] = 1;

      } else if (ato == '3' && ok[3] == 0) {  
        r = 3;                            
        ok[3] = 1;

      } else if (ato == '4' && ok[4] == 0) {  
        r = 4;                             
        ok[4] = 1;

      } else if (ato == '5' && ok[5] == 0) {  
        r = 5;                             
        ok[5] = 1;

      } else if (ato == '6' && ok[6] == 0) {  
        r = 6;                            
        ok[6] = 1;

      } else if (ato == '7' && ok[7] == 0) {  
        r = 7;                            
        ok[7] = 1;

      } else if (ato == '8' && ok[8] == 0) { 
        r = 8;                             
        ok[8] = 1;
      }
    }

    // Checks if Coraline has detected a object in the Raspberry 4
    if (Serial.available() > 0) {
      char opa = Serial.read();

      if (opa == '8' && ok[6] == 0) {//Gift
        r = 6;
        ok[6] = 1;
      }

      if (opa == '9' && ok[8] == 0) {//Mouse ball
        r = 8;
        ok[8] = 1;
      }
    }
    
  }
}
