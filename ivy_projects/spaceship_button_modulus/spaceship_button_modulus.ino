//initializing the pins

int green = 8;
int red1 = 10;
int red2 = 7;

int button = 9;
int count = 2;

//Use only for blinkWithOutDelay
unsigned long prevTime = 0;
bool ledState = true;
int interval = 500;

void setup() {
  Serial.begin(9600);
  
  pinMode(green,OUTPUT);
  pinMode(red1,OUTPUT);
  pinMode(red2,OUTPUT);
  pinMode(button,INPUT_PULLUP);

}

void loop() {

  if(digitalRead(button) == LOW){
    count++;
    Serial.println(count);
  } 
  
  
  if(count % 2 == 1){
    digitalWrite(green,LOW);
    blinkLight();
  } else {
    digitalWrite(green,HIGH);
  }

  //delay(100);

  

}
void blinkLight(){

  unsigned long currTime = millis();
  if(currTime - prevTime >= interval){
    ledState = !ledState;
    prevTime = currTime;
  }
  digitalWrite(red1,ledState);
  digitalWrite(red2,!ledState);
}
