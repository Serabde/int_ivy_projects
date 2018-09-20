// Arduino pin numbers
const int SW_pin = 2; // digital pin connected to switch output
const int X_pin = 0; // analog pin connected to X output
const int Y_pin = 1; // analog pin connected to Y output

const int RED = 3; //Red of RBG on 3
const int GREEN = 6; //Green of RGB on 6
const int BLUE = 5; //Blue of RBG on 5

int switchLightVal = 0;

void setup() {
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, HIGH);
  digitalWrite(BLUE, HIGH);
  Serial.begin(9600);
  analogWrite(RED, 0);
  analogWrite(BLUE, 0);
  analogWrite(GREEN, 0);
}

void loop() {
  switchLight(GREEN, SW_pin);
  stickLight(RED, Y_pin);
  stickLight(BLUE, X_pin);
}

void switchLight(int lightPin, int switchPin) {
  Serial.print("Switch:  ");
  Serial.print(digitalRead(switchPin));
  Serial.print("\n");



  if (digitalRead(switchPin) == LOW) {
    switchLightVal+=5;
  }

  if (switchLightVal >= 255) {
    switchLightVal = 0;
  }

  Serial.print("Switch Light Val = ");
  Serial.print(switchLightVal);
  Serial.print("\n");
  analogWrite(lightPin, switchLightVal);
}

void stickLight(int lightPin, int axisPin) {
  
  Serial.print("Axis on Pin ");
  Serial.print(axisPin);
  Serial.println(": ");
  int val = analogRead(axisPin);
  Serial.print(val);
  Serial.print("\n");
  int lightVal = map(val, 0, 1023, 0, 255);
  Serial.print("Light Val = ");
  Serial.print(val);
  Serial.print("\n\n");
  analogWrite(lightPin, lightVal);
}

