#define sensorPin D2    //Deklarasi sensor terhubung pada pin D5
#define led  D6       //Deklarasi LED merah terhubung pada pin A1
#define analogsensor A0
  
int bacasensor = 0;      // nilai awal sensor 0 
  
void setup() {
  pinMode(led, OUTPUT);    
  pinMode(sensorPin, INPUT); 
  pinMode(analogsensor, INPUT);
  Serial.begin(115200);
}
  
void loop() {
  bacasensor = digitalRead(sensorPin); 
  Serial.println(analogRead(analogsensor));
  if (bacasensor == LOW) {         
    Serial.print("Digital value: ");  
    Serial.println(bacasensor);
    Serial.println("no flame detected"); 
    digitalWrite(led,LOW);
    delay(1000);
  } else {
    Serial.print("Digital value: "); 
    Serial.println(bacasensor);
    digitalWrite(led, HIGH);
    Serial.println("flame detected"); 
    delay(1000);
  }
}
