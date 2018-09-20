

// include the library code:
#include <LiquidCrystal.h>

int buttonPin = 4;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
//String myWord = "HASHIM";

char wordArray[] = "HASHIM";
int numOfLet = sizeof(wordArray);
int count = 0;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  pinMode(buttonPin, INPUT_PULLUP); //circuit is HIGH until pushed
  Serial.begin(9600);

}

void loop() {

  while (count < numOfLet-1) {
    if (digitalRead(buttonPin) == LOW) {
      lcd.setCursor(count, 0);
      lcd.print(wordArray[count]);
      count++;
      delay(250);
    }
  }

  lcd.setCursor(0,1);
  lcd.print("You've lost!");


  delay(500);
}

