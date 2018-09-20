#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

int passcode[] = {9, 2, 6, 2};
int guess[] = {0, 0, 0, 0};


void setup() {
  Serial.begin(9600);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
}

void loop() {

  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  
  setGuess();

  Serial.println("The array is: ");

  for (int i = 0; i < 4; i++) {

    Serial.print(guess[i]);
  }

  check();

  delay(1000);
  

}

void setGuess() {
  int count = 0;

  while (count < 4) {

    char customKey = customKeypad.getKey();

    if (customKey) {
      int intCustom = customKey - '0'; //change char to integer
      guess[count] = intCustom;
      Serial.println(intCustom);
      count++;
    }
  }
}

void check(){
  
  bool correct = true;

  for(int i = 0; i < 4; i++){
    if(guess[i] != passcode[i]){
      correct = false;
    }
  }

  if(correct){
    digitalWrite(12,HIGH);
  } else digitalWrite(11,HIGH);
}

