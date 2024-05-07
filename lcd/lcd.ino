#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // Initialize the LCD library with the numbers of the interface pins

String message = "1. To launch ball, pull back on the plunger at the bottom right-hand side of the machine. 2. Keep the ball in play with the two buttons on each side of the machine. 3. As the ball hits various targets, bumpers, and ramps you'll earn points. 4. Try to prevent the ball from falling through the bottom gap between the flippers. 5. The game is over when you lose all of your (3) balls. At this point, the machine will display your final score.";

void setup() {
  lcd.begin(16, 2); // Set up the LCD's number of columns and rows
}

void loop() {
  for (int i = 0; i < message.length() - 15; i++) { // Loop through the message
    lcd.clear(); // Clear the LCD
    lcd.setCursor(0, 0); // Set the cursor to the beginning of the first row
    lcd.print(message.substring(i, i + 16)); // Print the substring of the message from i to i+16 (16 characters)
    delay(250); // Delay for readability
  }
}
