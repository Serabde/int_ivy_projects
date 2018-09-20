#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns

int red = 14; //incorrect
int green = 15; //disarmed
int blue = 16; //armed

// connect to the ST_CP of 74HC595 (pin 12,latch pin)
int latchPin = 10;
// connect to the SH_CP of 74HC595 (pin 11, clock pin)
int clockPin = 12;
// connect to the DS of 74HC595 (pin 14)
int dataPin = 11;

//define the symbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

int randomNumArr[4];
const int sizeArr = sizeof(randomNumArr);
int guess[sizeArr];

byte seven_seg_digits[11] = { B11111100,  // = 0
                              B01100000,  // = 1
                              B11011010,  // = 2
                              B11110010,  // = 3
                              B01100110,  // = 4
                              B10110110,  // = 5
                              B10111110,  // = 6
                              B11100000,  // = 7
                              B11111110,  // = 8
                              B11100110,   // = 9
                              B00000000
                             };


//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

bool armed = true; //Will tell us if alarm is armed

void setup() {
  Serial.begin(9600);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);

  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  randomSeed(analogRead(A4)*analogRead(A5));

}

void loop() {


    makeRandomNums();
    setGuess();
    check(); //CHECK whether the guess matches the passcode
}

void check() {
  bool correct = true;

  for (int i = 0; i < sizeArr; i++) { //Go through passcode array and COMPARE to guess array
    if (guess[i] != randomNumArr[i]) { //If a point in the passcode DOES NOT match the same point in the guess
      correct = false;
    }
  }

  //Take action based on whether they were right or wrong
  if (correct == true) {
    digitalWrite(green, HIGH);
    armed = false;
    digitalWrite(blue, LOW);
    delay(500);
  } else {
    digitalWrite(red, HIGH);
    delay(500);
  }
}

void setGuess() { // This will accept the guess from the user
  int count = 0; //Number of times a button has been pushed

  //Enter a guess
  while (count < sizeArr) {
    char customKey = customKeypad.getKey();

    if (customKey) { //If we press a button
      int num = customKey - '0'; //convert the character to an int
      guess[count] = num;
      Serial.println(num);
      count++;
    }
  }
}

// display a number on the digital segment display
void sevenSegWrite(int digit) { //write things to the seven segment display
  // set the latchPin to low potential, before sending data
  digitalWrite(latchPin, LOW);
     
  // the original data (bit pattern)
  shiftOut(dataPin, clockPin, LSBFIRST, seven_seg_digits[digit]);  
 
  // set the latchPin to high potential, after sending data
  digitalWrite(latchPin, HIGH);
}

void makeRandomNums(){ //create the random string of numbers
  
  Serial.println("Random nums are: ");
  for(int i = 0; i < 4; i++){
    int randNum = random(10);
    sevenSegWrite(randNum);
    Serial.println(randNum);
    delay(500);
    randomNumArr[i] = randNum;
    sevenSegWrite(10);
    delay(150);
  }
  sevenSegWrite(10);
}

