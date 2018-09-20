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
const int xPin = 0;
const int yPin = 1;

//Pins for Button, LED
const int pushButton = 4;
const int indicLed = 7;

LedControl lc = LedControl(DIN, CLK, CS, 1); //The 1 indicates how many MAX modules are connected

int delayTime = 500; //Time between blinking of LED
int rowDisp = 0;
int colDisp = 0;

void setup() {
  lc.shutdown(0, false); //Wake up display
  lc.setIntensity(0, 8); //Set brightness
  lc.clearDisplay(0); //Clear the display

  lc.setLed(0, 0, 0, true);

  Serial.begin(9600);

  pinMode(switchPin, INPUT);
  digitalWrite(switchPin, HIGH);

  pinMode(pushButton,INPUT_PULLUP);
  pinMode(indicLed, OUTPUT);
  digitalWrite(indicLed, LOW);
}

void loop() {

  int dir = transDir();

  switch (dir) {
    case 1: rowDisp--;
      break;
    case 2: colDisp--;
      break;
    case 3: rowDisp++;
      break;
    case 4: colDisp++;
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

  //ledLight(colDisp, rowDisp);

  bool eraser = buttonPressed();
  
  if (eraser == true) { // If the switch is pressed, the current light will go off
    ledOff(colDisp, rowDisp);
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
  if(digitalRead(pushButton) == LOW) {
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

