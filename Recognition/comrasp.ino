void setup() {
  Serial.begin(9600);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

}

void loop() {
  if(Serial.available() >0 ){
    int data = Serial.read() - '0';
    if(data == 1){
      digitalWrite(8, HIGH);
      delay(200);
      digitalWrite(8, LOW);
    }
    if(data == 2){
      digitalWrite(9, HIGH);
      delay(200);
      digitalWrite(9, LOW);
    }
    if(data == 3){
      digitalWrite(10, HIGH);
      delay(200);
      digitalWrite(10, LOW);
      
    }
  }
  //Serial.println("oi gigi");
  //delay(1000);

}
