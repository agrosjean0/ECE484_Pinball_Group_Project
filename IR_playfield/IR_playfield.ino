#include <Wire.h>

const int IR_game_over = 3; //**************************************
const int IR_left_hole = 4;
const int IR_right_hole = 5;
const int IR_field_path = 6;

const int updateDelay = 50; // min time between IR triggers

int score = 0;
int life = 3;

long counts_over[3] = {0, 0, 0};  //**************************************
long counts_left[3] = {0, 0, 0};
long counts_right[3] = {0, 0, 0};
long counts_field[3] = {0, 0, 0};

int last_pin = 0;

void CountHits(const int pin, long counts[]);

void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event

 pinMode(IR_game_over, INPUT);  //**************************************
 pinMode(IR_left_hole, INPUT);
 pinMode(IR_right_hole, INPUT);
 pinMode(IR_field_path, INPUT);
 
 
 Serial.begin(9600);
}

void loop() {
  
  // Ir goes high, incs onCount. update score 50ms after IR goes low, update if IR was on.
  CountHits(IR_game_over, counts_over); //**************************************
  CountHits(IR_left_hole, counts_left);
  CountHits(IR_right_hole, counts_right);
  CountHits(IR_field_path, counts_field);

  //Serial.println(last_pin);
  //Serial.println(score);
  if (life == 0) {
    life = 3;
    score = 0;
  }
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  Wire.write((uint8_t) last_pin); // respond with message as expected by master
  Wire.write((uint8_t) score);
}

// counts[0] is units of time IR has been on, [1] is previous IR on time, [2] is the last time the ir was on. 
void CountHits(const int pin, long counts[3]) {
  long onCount = counts[0];
  long lastOnCount = counts[1];
  long lastHigh = counts[2];
  if (digitalRead(pin) == 0) {
    onCount++;
    lastHigh = millis();
  }
  else if (millis() > lastHigh + updateDelay && onCount != lastOnCount) { 
    lastOnCount = onCount;
    score++;
    if (pin == IR_game_over) { //****************** game over pins
      life--;
    }
    if (pin == IR_left_hole) { // double points for difficulty
      score++; 
    }
    if (pin == last_pin) { // alternate send between pin and pin+20 to distinguish repeat sensor triggers
      last_pin = pin + 20;
    } else {
      last_pin = pin;
    }
  }
  counts[0] = onCount;
  counts[1] = lastOnCount;
  counts[2] = lastHigh;
}

