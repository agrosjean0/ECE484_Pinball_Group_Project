#include <Wire.h>
/*
  Showing number 0-9 on a Common Anode 7-segment LED display
  Displays the numbers 0-9 on the display, with one second inbetween.
    A
   ---
F |   | B
  | G |
   ---
E |   | C
  |   |
   ---
    D
  This example code is in the public domain.
 */
 
// Pin 2-8 is connected  to the 7 segments of the display.

int pinA = 2;
int pinB = 3;
int pinC  = 4;
int pinD = 5;
int pinE = 6;
int pinF = 7;
int pinG = 8;
int D1 = 9;
int D2 = 10;
int D3 = 11;
int D4 = 12;

int rxVal = 0;

// Update code so that value changes
int value = 0000; 

// the setup routine  runs once when you press reset:
void setup() {   
  Serial.begin(9600);             
  // initialize  the digital pins as outputs.
  pinMode(pinA, OUTPUT);     
  pinMode(pinB,  OUTPUT);     
  pinMode(pinC, OUTPUT);     
  pinMode(pinD, OUTPUT);     
  pinMode(pinE, OUTPUT);     
  pinMode(pinF, OUTPUT);     
  pinMode(pinG,  OUTPUT);   
  pinMode(D1, OUTPUT);  
  pinMode(D2, OUTPUT);  
  pinMode(D3,  OUTPUT);  
  pinMode(D4, OUTPUT);  

  // I2C 
  Wire.begin(); // join i2c bus (address optional for master)
}

// the loop routine runs over  and over again forever:
void loop() {
  while (rxVal != 9999) {
    Wire.requestFrom(8, 1);    // request 6 bytes from peripheral device #8
  
    while (Wire.available()) { // peripheral may send less than requested
      rxVal = Wire.read(); // receive a byte as character
      Serial.println(rxVal);         // print the character
    }
    
    if(rxVal != 9999) {
      value = rxVal;
    }
    
    // Extracting individual digits
    int thousands = value / 1000;
    int hundreds = (value / 100) % 10;
    int tens = (value / 10) % 10;
    int ones = value % 10;
  
    // Go to first digit
    digitalWrite(D1, HIGH);
    digitalWrite(D2,  LOW);
    digitalWrite(D3, LOW);
    digitalWrite(D4, LOW); 
    value_select(thousands);
    delay(1);               // wait for  a second
  
    // Go to second digit
    digitalWrite(D1, LOW);
    digitalWrite(D2, HIGH);
    digitalWrite(D3,  LOW);
    digitalWrite(D4, LOW);
    value_select(hundreds);
    delay(1);               // wait for a second
  
    // Go to third digit
    digitalWrite(D1, LOW);
    digitalWrite(D2, LOW);
    digitalWrite(D3,  HIGH);
    digitalWrite(D4, LOW); 
    value_select(tens);
    delay(1);               // wait for a second
  
    // Go to fourth digit
    digitalWrite(D1, LOW);
    digitalWrite(D2, LOW);
    digitalWrite(D3, LOW);
    digitalWrite(D4, HIGH); 
    value_select(ones);
    delay(1);               // wait for a second
  }
}

void nothing() {
  digitalWrite(pinA, HIGH);   
  digitalWrite(pinB, HIGH);   
  digitalWrite(pinC, HIGH);   
  digitalWrite(pinD, HIGH);   
  digitalWrite(pinE, HIGH);   
  digitalWrite(pinF, HIGH);   
  digitalWrite(pinG, HIGH);
}

void zero() {
  digitalWrite(pinA, LOW);   
  digitalWrite(pinB, LOW);   
  digitalWrite(pinC, LOW);   
  digitalWrite(pinD, LOW);   
  digitalWrite(pinE, LOW);   
  digitalWrite(pinF, LOW);   
  digitalWrite(pinG, HIGH);
}

void one() {
  digitalWrite(pinA, HIGH);   
  digitalWrite(pinB, LOW);   
  digitalWrite(pinC, LOW);   
  digitalWrite(pinD, HIGH);   
  digitalWrite(pinE, HIGH);   
  digitalWrite(pinF, HIGH);   
  digitalWrite(pinG, HIGH);
}

void two() {
  digitalWrite(pinA, LOW);   
  digitalWrite(pinB, LOW);   
  digitalWrite(pinC, HIGH);   
  digitalWrite(pinD, LOW);   
  digitalWrite(pinE, LOW);   
  digitalWrite(pinF, HIGH);   
  digitalWrite(pinG, LOW);
}

void three () {
  digitalWrite(pinA, LOW);   
  digitalWrite(pinB, LOW);   
  digitalWrite(pinC, LOW);   
  digitalWrite(pinD, LOW);   
  digitalWrite(pinE, HIGH);   
  digitalWrite(pinF, HIGH);   
  digitalWrite(pinG, LOW);
}

void four() {
  digitalWrite(pinA, HIGH);   
  digitalWrite(pinB, LOW);   
  digitalWrite(pinC, LOW);   
  digitalWrite(pinD, HIGH);   
  digitalWrite(pinE, HIGH);   
  digitalWrite(pinF, LOW);   
  digitalWrite(pinG, LOW);     
}
void five() {
  digitalWrite(pinA, LOW);   
  digitalWrite(pinB, HIGH);   
  digitalWrite(pinC, LOW);   
  digitalWrite(pinD, LOW);   
  digitalWrite(pinE, HIGH);   
  digitalWrite(pinF, LOW);   
  digitalWrite(pinG, LOW);     
}
  
void six() {
  digitalWrite(pinA, LOW);   
  digitalWrite(pinB, HIGH);   
  digitalWrite(pinC, LOW);   
  digitalWrite(pinD, LOW);   
  digitalWrite(pinE,  LOW);   
  digitalWrite(pinF, LOW);   
  digitalWrite(pinG, LOW);     
}

void seven() {
  digitalWrite(pinA,  LOW);   
  digitalWrite(pinB, LOW);   
  digitalWrite(pinC, LOW);   
  digitalWrite(pinD,  HIGH);   
  digitalWrite(pinE, HIGH);   
  digitalWrite(pinF, HIGH);   
  digitalWrite(pinG, HIGH);     
}
  
void eight() {
  digitalWrite(pinA, LOW);   
  digitalWrite(pinB, LOW);   
  digitalWrite(pinC, LOW);   
  digitalWrite(pinD, LOW);   
  digitalWrite(pinE, LOW);   
  digitalWrite(pinF, LOW);   
  digitalWrite(pinG, LOW);     
}

void nine() {
  digitalWrite(pinA, LOW);   
  digitalWrite(pinB, LOW);   
  digitalWrite(pinC, LOW);   
  digitalWrite(pinD, HIGH);   
  digitalWrite(pinE, HIGH);   
  digitalWrite(pinF, LOW);   
  digitalWrite(pinG, LOW);     
}

void value_select(int value) {
  switch (value) {
    case 0: 
      zero();
      break;
    case 1:
      one();
      break;
    case 2:
      two();
      break;
    case 3:
      three();
      break;
    case 4:
      four();
      break;
    case 5:
      five();
      break;
    case 6:
      six();
      break;
    case 7:
      seven();
      break;
    case 8:
      eight();
      break;
    case 9:
      nine();
      break;
    default:
      nothing();
      break;
  }
}
