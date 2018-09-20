#include "IRremote.h"

//Pins
int photoPin = A0;
int recPin = 4;

//IR Stuff
IRrecv ir(recPin); //Create the IR receiver
decode_results results;

int baseline = 0;
int ledState;
int buttonCount = 2;

void setup() {
  //LEDs
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);

  Serial.begin(9600);
  ir.enableIRIn();

  delay(200); //delay for a sec
  baseline = analogRead(photoPin); //Take a baseline reading of the light in the room

}

void loop() {

  int irCode = checkIR();

  if (irCode == 1) {
    buttonCount++;
  }
  int photoRead = analogRead(photoPin); //Read the value of the photopin

  Serial.println(buttonCount);

  bool dark = photoRead < baseline * 0.8;

  if (buttonCount % 2 == 0 && dark) {
    ledOn();
  } else if (buttonCount % 2 == 0 && !dark) {
    off();
  } else if (buttonCount % 2 == 1 && dark) {
    off();
} else if (buttonCount % 2 == 1 && !dark) {
    ledOn();
  }

  delay(200);

}

int checkIR() {
  if (ir.decode(&results)) { // have we received an IR signal?
    Serial.println("Found");
    int pressed = translateIR();
    ir.resume(); // receive the next value
    return pressed;
  }
}

void ledOn() {
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  delay(200);
  digitalWrite(3, HIGH);
  digitalWrite(2, LOW);
  delay(200);
  ledState = 1;
}

void off() {
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  ledState = 0;
}

int translateIR() { // returns number of button pressed, WORKS FOR NUMBERS ONLY

  switch (results.value) {

    case 0xFF30CF:
      Serial.println(" 1");
      return 1;
      break;//changed
    case 0xFF18E7:
      Serial.println(" 2");
      return 2;
      break;//changed
    case 0xFF7A85:
      Serial.println(" 3");
      return 3;
      break;//changed
    case 0xFF10EF:
      Serial.println(" 4");
      return 4;
      break;//changed
    case 0xFF38C7:
      Serial.println(" 5");
      return 5;
      break;//cahnged
    case 0xFF5AA5:
      Serial.println(" 6");
      return 6;
      break;//changed
    case 0xFF42BD:
      Serial.println(" 7");
      return 7;
      break;//changed
    case 0xFF4AB5:
      Serial.println(" 8");
      return 8;
      break;//changed
    case 0xFF52AD:
      Serial.println(" 9");
      return 9;
      break;//changed
    case 0xFF6897:
      Serial.println(" 0");
      return 0;
      break; //changed
    case 0xFFFFFFFF:
      Serial.println(" REPEAT");
      return -1; //Error code
      break;

    default:
      Serial.println(results.value);

  }// End Case

  delay(500); // Do not get immediate repeat


} //END translateIR

