
void setup() {
  Serial.begin(9600);
  pinMode(12, INPUT);
  pinMode(13, INPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  digitalWrite(5,LOW); 
  digitalWrite(6,LOW); 

}

void loop() {

  if (digitalRead(12) == HIGH) {
    digitalWrite(6,HIGH);
    digitalWrite(3,LOW);  
    delay(50); 
    digitalWrite(3,HIGH); 
    delay(200);
    //digitalWrite(3,LOW);  
    //delay(200);
    digitalWrite(6,LOW);
  } 

  if (digitalRead(13) == HIGH) {
    digitalWrite(5,HIGH);
    digitalWrite(4,LOW); 
    delay(50);
    digitalWrite(4,HIGH); 
    delay(200);    
    //digitalWrite(4,LOW); 
    //delay(200);
    digitalWrite(5,LOW);  
  } 

  
}
