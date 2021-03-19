const int buzzer=11;
float alt=0;
void setup() {
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  buzzerON();

}


void buzzerON(){
  if (alt<5){
    Serial.println("Turning buzzer ON for recovery");
    tone(buzzer, 1000);
    delay(500);
  }
  else{
    tone(buzzer, 0);
  }
}
