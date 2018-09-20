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
const int CS = 9;
const int CLK = 10;


//Pins for Joystick
const int switchPin = 2;
const int xPin = A0;
const int yPin = A1;

LedControl lc = LedControl(DIN,CLK,CS,1); //The 1 indicates how many MAX modules are connected

int delayTime = 500; //Time between blinking of LED
int rowDisp = 0;
int colDisp = 0;

void setup() {
  lc.shutdown(0, false); //Wake up display
  lc.setIntensity(0,8); //Set brightness
  lc.clearDisplay(0); //Clear the display

  lc.setLed(0,0,0, true);

  Serial.begin(9600);

  pinMode(switchPin, INPUT);
  digitalWrite(switchPin, HIGH);
}

void loop() {
  
  int dir = transDir();

  switch(dir) {
    case 1: rowDisp--;
      break;
    case 2: colDisp--;
      break;
    case 3: rowDisp++;
      break;
    case 4: colDisp++;
      break;
  }

  if(rowDisp < 0) {
    rowDisp = 0;
  } else if(rowDisp > 7) {
    rowDisp = 7;
  }

  if(colDisp < 0) {
    colDisp = 0;
  } else if(colDisp > 7) {
    colDisp = 7;
  }

  Serial.println("Col: ");
  Serial.print(colDisp);
  Serial.println();

  Serial.println("Row: ");
  Serial.print(rowDisp);
  Serial.println();
  ledLight(colDisp, rowDisp);

  if (digitalRead(switchPin) == LOW) {
    lc.setLed(0,colDisp,rowDisp,false);
  }
  
  delay(100);

}

void ledLight(int col, int row) {
  lc.setLed(0,col,row,true);
}

int transDir() {
  int xVal = analogRead(xPin);
  int yVal = analogRead(yPin);

  //printVals(xVal, yVal);

  if(yVal < 100) { // When joystick is UP, return 1
    Serial.println("UP");
    return 1;
  }

  if(xVal > 800) { // When joystick is RIGHT, return 2
    Serial.println("RIGHT");
    return 2;
  }

  if(yVal > 800) { // When joystick is DOWN, return 3
    Serial.println("DOWN");
    return 3;
  }

  if(xVal < 100) { // When joystick is LEFT, return 4
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

