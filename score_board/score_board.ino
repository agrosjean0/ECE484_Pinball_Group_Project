#include <Wire.h>
#include "tones.h"
/*
 * Author: Alecea Grosjean
 * Class: ECE 484 
 * Project: Final Pinball machine
 * Purpose: This code prints the results of the score to a seven segment display screen using 12C Communication
 
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

// The storage of the score value and pin that was triggered in the playfield arduino
int rxVal = 0;
int pinTrig = -1;
int prevTrig = 0; 
int ballCt = 0;

// Update code so that value changes
int value = 0000; 

// piezo set up
int piezoPin = A0;

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
    Wire.requestFrom(8, 2);    // request 1 byte from peripheral device #8
  
    while (Wire.available()) { // peripheral may send less than requested
      pinTrig = Wire.read(); // receive pin value
      rxVal = Wire.read(); // receive score value
    }
    // Serial.println(pinTrig);
    // Serial.println(prevTrig);
    value = rxVal;
        // Extracting individual digits
        int thousands = value / 1000;
        int hundreds = (value / 100) % 10;
        int tens = (value / 10) % 10;
        int ones = value % 10;

        // Serial.println(pinTrig);
    // Serial.println(prevTrig);
        
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

        // Print Score and if val increased good sound
    if (pinTrig != prevTrig) {
        if (pinTrig == 4 || pinTrig == 24 || pinTrig == 5 || pinTrig == 25 || pinTrig == 6 || pinTrig == 26) {
        tone(piezoPin,NOTE_E6,125);
              delay_2(130, thousands, hundreds, tens, ones);
              tone(piezoPin,NOTE_G6,125);
              delay_2(130, thousands, hundreds, tens, ones);
              tone(piezoPin,NOTE_E7,125);
              delay_2(130, thousands, hundreds, tens, ones);
              tone(piezoPin,NOTE_C7,125);
              delay_2(130, thousands, hundreds, tens, ones);
              tone(piezoPin,NOTE_D7,125);
              delay_2(130, thousands, hundreds, tens, ones);
              tone(piezoPin,NOTE_G7,125);
              delay_2(125, thousands, hundreds, tens, ones);
              noTone(piezoPin);
        } else if (pinTrig == 3 || pinTrig == 23) {
             tone(piezoPin,NOTE_D4);
             delay_2(250, thousands, hundreds, tens, ones);
             tone(piezoPin,NOTE_CS4);
             delay_2(250, thousands, hundreds, tens, ones);
             tone(piezoPin,NOTE_C4);
             delay_2(250, thousands, hundreds, tens, ones);
             tone(piezoPin,NOTE_B3);
             delay_2(500, thousands, hundreds, tens, ones);
             noTone(piezoPin);
             ballCt = ballCt + 1; 
        }
   }

  // Game over response here 
  if (ballCt == 3) {
    int rxVal = 0;
    int value = 0; 
    ballCt = 0; 
  }
  prevTrig = pinTrig; 
  //delay(1000);
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

void delay_2(int time, int thousands, int hundreds, int tens, int ones) {
  for (int i = 0; i < time; i=i+5) {
    delay(1); 
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
