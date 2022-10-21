#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>               
#include <TimeLib.h>                 
#include <LiquidCrystal_I2C.h> 
LiquidCrystal_I2C lcd(0x27, 16, 2);

char* ssid = "testingwifi";  //wifi ssid
char* password = "pass5678";   //wifi password
const long utcOffsetInSeconds = (8 * 60 * 60);  // set offset (GMT * 60 * 60)
WiFiUDP ntpUDP;

NTPClient timeClient(ntpUDP, "id.pool.ntp.org", utcOffsetInSeconds);

char Time[ ] = "Jam: 00:00:00";
char Date[ ] = "Tgl: 00/00/2000";
byte last_second, second_, minute_, hour_, day_, month_;
int year_;

void setup() {
    // Initialize 16x2 LCD Display
    Serial.begin(115200);
    lcd.init();
    lcd.backlight();

    lcd.clear();
    // column, row
    lcd.setCursor (0,0);
    lcd.print("Hello");
    lcd.setCursor (0,1);
    lcd.print(":)");
    delay(4000);
    lcd.clear();
    lcd.setCursor (0,0);
    lcd.print("Searching WiFi..");
    delay(2000);
    lcd.setCursor (0,1);
    lcd.print("Connected!");
    delay(1000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(Time);
    lcd.setCursor(0, 1);
    lcd.print(Date);

    // connecting to wifi
    WiFi.begin(ssid, password);
    Serial.print("Connecting.");

    while ( WiFi.status() != WL_CONNECTED ) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("connected");
    timeClient.begin();
}
 

void loop() {
    timeClient.update();
    unsigned long unix_epoch = timeClient.getEpochTime();    // Get Unix epoch from the NTP server

    second_ = second(unix_epoch);
    if (last_second != second_) {
        minute_ = minute(unix_epoch);
        hour_   = hour(unix_epoch);
        day_    = day(unix_epoch);
        month_  = month(unix_epoch);
        year_   = year(unix_epoch);

        Time[12] = second_ % 10 + 48;
        Time[11] = second_ / 10 + 48;
        Time[9]  = minute_ % 10 + 48;
        Time[8]  = minute_ / 10 + 48;
        Time[6]  = hour_   % 10 + 48;
        Time[5]  = hour_   / 10 + 48;

        Date[5]  = day_   / 10 + 48;
        Date[6]  = day_   % 10 + 48;
        Date[8]  = month_  / 10 + 48;
        Date[9]  = month_  % 10 + 48;
        Date[13] = (year_   / 10) % 10 + 48;
        Date[14] = year_   % 10 % 10 + 48;

        Serial.println(Time);
        Serial.println(Date);

        lcd.setCursor(0, 0);
        lcd.print(Time);
        lcd.setCursor(0, 1);
        lcd.print(Date);
        last_second = second_;
    }
    delay(25);
}
