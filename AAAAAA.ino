#include <VarSpeedServo.h>
#include "SoftwareSerial.h"

VarSpeedServo b1;

char str;

SoftwareSerial bluetooth(10, 11);

void setup() {
  b1.attach(8);
  b1.slowmove(90, 50);
  bluetooth.begin(9600);
  Serial.begin(9600);
  Serial1.begin(9600);
}
void loop() {

  for (int i = 30; i <= 70; i++) {
    if(i%5 == 0){
      String men = "@";
      men += i;
      men += "#";

      bluetooth.println(men);
    }
    
    b1.slowmove(i, 20);
    b1.wait();
  }

  for (int i = 70; i >= 0; i--) {

    if(i%5 == 0){
      String men = "@";
      men += i;
      men += "#";

      bluetooth.println(men);
    }

    b1.slowmove(i, 20);
    b1.wait();
  }

  for (int i = 0; i <= 30; i++) {
    if(i%5 == 0){
      String men = "@";
      men += i;
      men += "#";

      bluetooth.println(men);
    }
    
    b1.slowmove(i, 20);
    b1.wait();
  }

  /* b1.slowmove(90, 20);
    b1.wait();
    b1.slowmove(130, 20);
    b1.wait();
    b1.slowmove(90, 20);
    b1.wait();
    b1.slowmove(50, 20);
    b1.wait();
    /*char b = 'b';
    char a = Serial1.read();
    Serial.println(a);
    Serial1.println("b");*/
  /*i.slSerial1owmove(140, 200);
    i.wait();
    i.slowmove(0, 200);
    i.wait();
    i.slowmove(120, 200);
    i.wait();*/

  /*b2.slowmove(180, 100);
    b2.wait();
    b2.slowmove(0, 200);
    b2.wait();*/

  /* b3.slowmove(180, 150);
    b3.wait();
    b3.slowmove(0, 200);
    b3.wait();
    b3.slowmove(180, 150);
    b3.wait();
    b3.slowmove(0, 200);
    b3.wait();

    s1.slowmove(180, 150);
    s1.wait();
    s1.slowmove(0, 200);
    s1.wait();

    s2.slowmove(180, 150);
    s2.wait();
    s2.slowmove(0, 200);
    s2.wait();


    b3.slowmove(100, 200);
    b3.wait();
    b3.slowmove(0, 200);
    b3.wait();/

    /*if(Serial2.available() > 0){

     int incomingByte = Serial2.read();
     Serial.println(incomingByte);
     if (incomingByte == 1) {
       Serial2.println("@ok#");
       int up = millis();
     }
     else
    {
     Serial2.println("@naofoi#");
    }
    }
    delay (5000);
    Serial2.println("@vembb#");*/
}

void Moveode(){
  for (int i = 90; i <= 130; i++) {
    if(i%5 == 0){
      String men = "@";
      men += i;
      men += "#";

      bluetooth.println(men);
    }
    
    b1.slowmove(i, 20);
    b1.wait();
  }

  for (int i = 130; i >= 50; i--) {

    if(i%5 == 0){
      String men = "@";
      men += i;
      men += "#";

      bluetooth.println(men);
    }

    b1.slowmove(i, 20);
    b1.wait();
  }

  for (int i = 50; i <= 90; i++) {
    if(i%5 == 0){
      String men = "@";
      men += i;
      men += "#";

      bluetooth.println(men);
    }
    
    b1.slowmove(i, 20);
    b1.wait();
  }

}


void Moveocb(){
  for (int i = 30; i <= 70; i++) {
    if(i%5 == 0){
      String men = "@";
      men += i;
      men += "#";

      bluetooth.println(men);
    }
    
    b1.slowmove(i, 20);
    b1.wait();
  }

  for (int i = 70; i >= 0; i--) {

    if(i%5 == 0){
      String men = "@";
      men += i;
      men += "#";

      bluetooth.println(men);
    }

    b1.slowmove(i, 20);
    b1.wait();
  }

  for (int i = 0; i <= 30; i++) {
    if(i%5 == 0){
      String men = "@";
      men += i;
      men += "#";

      bluetooth.println(men);
    }
    
    b1.slowmove(i, 20);
    b1.wait();
  }
}
