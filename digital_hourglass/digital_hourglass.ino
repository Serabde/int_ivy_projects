int switchPin = 8;
int switchState = 0;
int lastSwitchState = 0;
int ledNum = 2;
  long previousTime = 0;

long intervalLedOn = 1000;
void setup() {
  for(int i = 2; i < 8; i++){
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
  pinMode(switchPin, INPUT);
   Serial.begin(9600);
}

void loop() {

 
  long currentTime = millis();


  if(currentTime - previousTime > intervalLedOn){ //if the time that has passed MINUS the last time we changed an LED is bigger than the specified time
    previousTime = currentTime;
    digitalWrite(ledNum, HIGH);
    ledNum++;
  }

  if(ledNum == 8){
    ledNum = 0;
  }

  switchState = digitalRead(switchPin);
  Serial.println(switchState);

  if(switchState != lastSwitchState){
    for(int i = 2; i < 8; i++){
      digitalWrite(i,LOW);
      ledNum = 0;
    }

    previousTime = currentTime;
  }
  
  lastSwitchState = switchState;

}
