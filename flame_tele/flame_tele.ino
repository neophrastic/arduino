#include "CTBot.h"

#define sensorPin D1

CTBot mybot;
String ssid  = "";
String pass = "";

String token = "";
int id = 12345; //  change this to your tele id
int flame_detected;

void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
  Serial.println("Connecting");

  mybot.wifiConnect(ssid, pass);
  mybot.setTelegramToken(token);

  if(mybot.testConnection()){
    Serial.println("success");
  }else {
    Serial.println("fail");
  }
}

void loop() {
 TBMessage msg;
 flame_detected = digitalRead(sensorPin);
 Serial.println(flame_detected);
 if(flame_detected == 1){
    mybot.sendMessage(id, "ADA API");
    Serial.println("flame detected");
 } else {
    Serial.println("no flame detected"); 
 }
 delay(10000);
}
