const int lightSensorPin = 2;
const int motor1Pin1 = 3;
const int motor1Pin2 = 4;
const int motor1EnablePin = 5;
const int motor2Pin1 = 6;
const int motor2Pin2 = 7;
const int motor2EnablePin = 8;

void setup() {
  Serial.begin(9600);
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor1EnablePin, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(motor2EnablePin, OUTPUT);
  pinMode(lightSensorPin, INPUT);
}

void loop() {
  int lightSensorValue = digitalRead(lightSensorPin);

  if (lightSensorValue == HIGH) {
    digitalWrite(motor1Pin1, HIGH);
    digitalWrite(motor1Pin2, LOW);
    analogWrite(motor1EnablePin, 255);
    digitalWrite(motor2Pin1, HIGH);
    digitalWrite(motor2Pin2, LOW);
    analogWrite(motor2EnablePin, 255);
    delay(5000);
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, LOW);
    analogWrite(motor1EnablePin, 0);
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, LOW);
    analogWrite(motor2EnablePin, 0);
  }
}
