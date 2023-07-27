// https
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
// GPS
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
TinyGPSPlus gps;
SoftwareSerial SerialGPS(4, 5); // RX, TX
float latF, lonF;
String lat, lon;
// tele
#include "CTBot.h"
CTBot mybot;
String token = "yourtoken";
#define id 123123
// wifi
const char* ssid = "HUAWEI-2G";
const char* password = "kjhsd90";
// flame
#define flame D5

void setup() {
  Serial.begin(9600);

  pinMode(flame, INPUT);
  // Connect to GPS
  SerialGPS.begin(9600);

  // Connect to Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  // Connect to tele
  mybot.setTelegramToken(token);
  if(mybot.testConnection()){
    Serial.println("\nSuccess connected to telegram");  
  }else {
    Serial.println("\nFailed connected to telegram");  
  }
}

void sendLoc(String lat, String lon) {
   // wait for WiFi connection
  if ((WiFi.status() == WL_CONNECTED)) {
    std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
    // Ignore SSL certificate validation
    client->setInsecure();
    //create an HTTPClient instance
    HTTPClient https;
    Serial.println("Mengirim lokasi...");
    if (https.begin(*client, "https://api.telegram.org/bot" + token + "/sendlocation?chat_id=" + id + "&latitude=" + lat + "&longitude=" + lon)) {
      int httpCode = https.GET();
      if(httpCode > 0){
        Serial.println("Lokasi terikirim!");
      }else {
        Serial.println("Gagal mengirim lokasi!");  
      }
      https.end();
    }else {
      Serial.println("Koneksi dengan telegram gagal!");
    }
  }
}

void loop() {
  Serial.println();
  if(digitalRead(flame) == HIGH){
    if (gps.encode(SerialGPS.read())){
      if (gps.location.isValid()){
        latF = gps.location.lat();
        lat = String(latF , 6);
        lonF = gps.location.lng();
        lon = String(lonF , 6);
      }
    }
    mybot.sendMessage(id, "**KEBAKARAN!**\nLatitude: " + lat + " | Longitude: " + lon);
    sendLoc(lat, lon);

    Serial.println();
    Serial.println("Kebakaran was detected, waiting 2 min...");
    delay(120000);
  }else{
    Serial.println();
    Serial.println("No kebakaran");
    delay(1000);
  }
}