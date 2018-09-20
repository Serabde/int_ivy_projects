// create an array of notes
// the numbers below correspond to
// the frequencies of middle C, D, E, and F

//CHANGED 1M resistor to a 100K

#include "pitches.h"

//int notes[] = {262, 294, 330, 349};
//int notes[] = {NOTE_C3, NOTE_C4, NOTE_C5, NOTE_C6};
int notes[] = {NOTE_B4, NOTE_A4, NOTE_G4, NOTE_E4};

void setup() {
  //start serial communication
  Serial.begin(9600);
}
void loop() {
  // create a local variable to hold the input on pin A0
  int keyVal = analogRead(A0);
  // send the value from A0 to the Serial Monitor
  Serial.println(keyVal);
  // play the note corresponding to each value on A0
  if (keyVal  > 1000) {
    // play the first frequency in the array on pin 8
    tone(8, notes[0],1000);
  }
  else if (keyVal >= 900 && keyVal <= 1000) {
    // play the second frequency in the array on pin 8
    tone(8, notes[1],1000);
  }
  else if (keyVal >= 450 && keyVal <= 600) {
    // play the third frequency in the array on pin 8
    tone(8, notes[2],1000);
  }
  else if (keyVal >= 5 && keyVal <= 200) {
    // play the fourth frequency in the array on pin 8
    tone(8, notes[3],1000);
  }
  else {
    // if the value is out of range, play no tone
    noTone(8);
  }
}
