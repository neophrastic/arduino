// https://randomnerdtutorials.com/esp8266-nodemcu-hc-sr04-ultrasonic-arduino/
//Distance Measurement using Ultrasonic Sensor

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
#define trigPin 12 //Sensor Echo pin connected to Arduino pin 13
#define echoPin 14 //Sensor Trip pin connected to Arduino pin 12

void setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(D4, OUTPUT);
  
  lcd.init();
  lcd.backlight();
  lcd.clear();
  
  lcd.setCursor(0,0);  //Set LCD cursor to upper left corner, column 0, row 0
  lcd.print("Jarak :");  //Print Message on First Row
}

void loop()
{
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;

  lcd.setCursor(0,1);  //Set cursor to first column of second row
  lcd.print("                "); //Print blanks to clear the row
  lcd.setCursor(0,1);   //Set Cursor again to first column of second row
  lcd.print(distance); //Print measured distance
  lcd.print(" cm");  //Print your units.
  
  if(distance < 10){
    digitalWrite(D4, HIGH);
    delay(100);
    digitalWrite(D4, LOW);
    delay(100);
   } else if(distance < 20){
    digitalWrite(D4, HIGH);
    delay(500);
    digitalWrite(D4, LOW);
    delay(500);
   }  
    
    else{
      digitalWrite(D4, LOW);
      }
  delay(250); //pause to let things settle
}
