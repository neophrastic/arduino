const int ledpin=13; // ledpin and soundpin are not changed throughout the process
const int soundpin=A2;
const int threshold=500; // sets threshold value for sound sensor

void setup() {
    Serial.begin(9600);
    pinMode(ledpin,OUTPUT);
    pinMode(soundpin,INPUT);
}
void loop() {
    int soundsens=analogRead(soundpin); // reads analog data from sound sensor
    Serial.println(soundsens);
    if (soundsens>=threshold && digitalRead(ledpin)==0) {
        digitalWrite(ledpin,HIGH); //turns led on
    }
    else if(soundsens>=threshold && digitalRead(ledpin)==1){
        digitalWrite(ledpin,LOW);
    }
}
