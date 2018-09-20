//This program assumes that the TOP of the MAX module is the side with connecting wires,
//and the FIRST column is on the RIGHT most side.

//Also, LEFT on the Joystick is towards the wire connections

#include "LedControl.h"

/*
NOTE: HAD TO CHANGE PINS -->
  PIN 11 --> DIN
  PIN 10 --> CLK
  PIN 9 --> CS
 */

// Pins for the MAX module
const int DIN = 11;
const int CLK = 10;
const int CS = 9;

//Pins for Joystick
const int switchPin = 2;
const int xPin = A0;
const int yPin = A1;

//Pins for Button, LED
const int pushButton = 4; // Pullup pushbutton on 4
const int indicLed = 7; // LED on 7

LedControl lc = LedControl(DIN, CLK, CS, 1); //The 1 indicates how many MAX modules are connected

int delayTime = 500; //Time between blinking of LED
int rowDisp = 0;
int colDisp = 0;

//int colArr[] = { -1, -1, -1, -1, -1, -1, -1, -1};
//int rowArr[] = { -1, -1, -1, -1, -1, -1, -1, -1};

bool maxArray[8][8] = {

  { 0, 0, 0, 0, 0, 0, 0, 0},

  { 0, 0, 0, 0, 0, 0, 0, 0},

  { 0, 0, 0, 0, 0, 0, 0, 0},

  { 0, 0, 0, 0, 0, 0, 0, 0},

  { 0, 0, 0, 0, 0, 0, 0, 0},

  { 0, 0, 0, 0, 0, 0, 0, 0},

  { 0, 0, 0, 0, 0, 0, 0, 0},

  { 0, 0, 0, 0, 0, 0, 0, 0},

};


// int counter = 0;

void setup() {
  lc.shutdown(0, false); //Wake up display
  lc.setIntensity(0, 8); //Set brightness
  lc.clearDisplay(0); //Clear the display

  lc.setLed(0, 0, 0, true);

  Serial.begin(9600);

  pinMode(switchPin, INPUT);
  digitalWrite(switchPin, HIGH);

  pinMode(pushButton, INPUT_PULLUP);
  pinMode(indicLed, OUTPUT);
  digitalWrite(indicLed, LOW);
}

void loop() {

  int dir = transDir();

  switch (dir) {
    case 1: rowDisp--; // UP
      break;
    case 2: colDisp--; // RIGHT
      break;
    case 3: rowDisp++; // DOWN
      break;
    case 4: colDisp++; // LEFT
      break;
  }

  if (rowDisp < 0) {
    rowDisp = 0;
  } else if (rowDisp > 7) {
    rowDisp = 7;
  }

  if (colDisp < 0) {
    colDisp = 0;
  } else if (colDisp > 7) {
    colDisp = 7;
  }

  //  bool eraser = buttonPressed();
  //
  //  if (eraser == true) { // If the switch is pressed, the current light will go off
  //    ledOff(colDisp, rowDisp);
  //  } else ledLight(colDisp, rowDisp); // if the switch isnt pressed, the current light will illuminate

  switch (dir) { // Will turn off previous light
    case 1: ledOff(colDisp, rowDisp + 1); // UP - turn off row+1
      break;
    case 2: ledOff(colDisp + 1, rowDisp); // RIGHT - turn off col+1
      break;
    case 3: ledOff(colDisp, rowDisp - 1); // DOWN - turn off row-1
      break;
    case 4: ledOff(colDisp - 1, rowDisp); // LEFT - turn off col-1
      break;
  }


    // Adds the location of current position to arrays
    if (digitalRead(switchPin) == LOW) {
      maxArray[colDisp][rowDisp] = 1;
    }


  // Lights LEDs whose positions have been indicated
  for (int i = 0; i < 8; i++) { //cols
    for (int j = 0; j < 8; j++) { //rows
      if (maxArray[i][j]==1) {

        //ledLight(7 - j, i);
        ledLight(i,j);
      }
    }
  }


  bool eraser = buttonPressed();

  if (eraser == true) { // If the switch is pressed, the current light will go off
    ledOff(colDisp, rowDisp);
    maxArray[colDisp][rowDisp] = 0;
  } else ledLight(colDisp, rowDisp); // if the switch isnt pressed, the current light will illuminate

  delay(100);

}

void ledLight(int col, int row) { // turns LED on
  lc.setLed(0, col, row, true);
}

void ledOff(int col, int row) { // turns LED off
  lc.setLed(0, col, row, false);
}

bool buttonPressed() {
  if (digitalRead(pushButton) == LOW) {
    digitalWrite(indicLed, HIGH);
    return true;
  } else {
    digitalWrite(indicLed, LOW);
    return false;
  }

}

int transDir() { // translates analog movement of joystick into 4 directions
  int xVal = analogRead(xPin);
  int yVal = analogRead(yPin);

  //printVals(xVal, yVal);

  if (yVal < 100) { // When joystick is UP, return 1
    Serial.println("UP");
    return 1;
  }

  if (xVal > 800) { // When joystick is RIGHT, return 2
    Serial.println("RIGHT");
    return 2;
  }

  if (yVal > 800) { // When joystick is DOWN, return 3
    Serial.println("DOWN");
    return 3;
  }

  if (xVal < 100) { // When joystick is LEFT, return 4
    Serial.println("LEFT");
    return 4;
  }

}

void printVals(int xVal, int yVal) {
  Serial.print("X-axis: ");
  Serial.print(xVal);
  Serial.print("\n");

  Serial.print("Y-axis: ");
  Serial.print(yVal);
  Serial.print("\n");

  Serial.println("____");

  delay(500);
}

