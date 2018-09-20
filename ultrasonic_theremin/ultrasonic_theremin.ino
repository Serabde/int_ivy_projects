#include <NewPing.h>
#include <NewTone.h>

int trig = 7;
int echo = 6;
int maxDist = 200;
int light = 13;
int speaker = 9;

NewPing sonar(trig, echo, maxDist);

void setup() {
  Serial.begin(9600);
  pinMode(light,OUTPUT);
  pinMode(speaker,OUTPUT);
}

void loop() {
  int timeTaken = sonar.ping();
  int distance = timeTaken / US_ROUNDTRIP_IN;
  Serial.println(distance);

  //int delayTime = map(distance, 0, 60, 5, 250);
  int frequency = map(distance, 0, 60, 540, 1050);

  if(distance < 60){
    NewTone(speaker, frequency);
    /*digitalWrite(light, HIGH);
    delay(delayTime);
    digitalWrite(light, LOW);
    delay(delayTime);*/
  }
  
  delay(75);
}
