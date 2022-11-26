#include <Arduino.h>

// IR Library
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

// LCD and I2C
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// alamat lcd
LiquidCrystal_I2C lcd(0x27,16,2);

// GPIO 16 gabisa karna ga ada interrupts
const uint16_t kRecvPin = 13; // pin D7
unsigned long key_value = 0;
IRrecv irrecv(kRecvPin);
 
decode_results results;

void setup() {
  Serial.begin(115200);
  irrecv.enableIRIn();  // Start the receiver
  while (!Serial)  // Wait for the serial connection to be establised.
    delay(50);
  Serial.println();
  
  pinMode(D0, OUTPUT); // built in
  pinMode(D4, OUTPUT); // built in
  pinMode(D3, OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("HEX Value :");
}

void loop() {
  if (irrecv.decode(&results)) {
    lcd.setCursor(0, 1);
    lcd.print(results.value, HEX);
    
    switch(results.value){
          case 0x4F58807F:
            if (digitalRead(D4) == 0){
              digitalWrite(D4, HIGH);  
            }else{
              digitalWrite(D4, LOW);  
            }
            break;
          case 0x4F5800FF:
            if (digitalRead(D0) == 0){
              digitalWrite(D0, HIGH);  
            }else{
              digitalWrite(D0, LOW);  
            }
            break;
          case 0x4F5840BF:
            if (digitalRead(D3) == 0){
              digitalWrite(D3, HIGH);  
            }else{
              digitalWrite(D3, LOW);  
            }
            break ;
    }
    irrecv.resume();  //next value
  }
}
