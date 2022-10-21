int pin = 4;

void setup(){
    pinMode(pin, OUTPUT);
    Serial.begin(9600);
}

void loop(){
    digitalWrite(pin, LOW);  
    Serial.print("off");
    delay(1000);
    digitalWrite(pin, HIGH);  
    Serial.print("on");
    delay(1000);
}
