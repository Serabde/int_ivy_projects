int thermo = A5;
int green = 2;
int white = 6;
int red = 9;

int baseline;

void setup() {
  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(white, OUTPUT);

  Serial.begin(9600); //Initalizes the serial monitor

  delay(1000);
  baseline = analogRead(thermo);
  digitalWrite(white, HIGH);
  
}

void loop() {
  int thermoRead = analogRead(thermo);
  Serial.println("Sensor Value: ");
  Serial.println(thermoRead);

  if(thermoRead < baseline * 0.95){ //If current read is LESS THAN baseline
    digitalWrite(green,HIGH);
    digitalWrite(red,LOW);
    digitalWrite(white,LOW);
  }

  if(thermoRead > baseline * 1.05){
    digitalWrite(green,LOW);
    digitalWrite(red,HIGH);
    digitalWrite(white,LOW);
  }

  if(thermo < baseline * 1.05 && thermo > baseline * 0.95){
    digitalWrite(green,LOW);
    digitalWrite(red,LOW);
    digitalWrite(white,LOW);
  }
  
  delay(150);

  

}
