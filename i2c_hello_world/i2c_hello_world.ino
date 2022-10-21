 #include <Wire.h>  // I2C protocol  
 #include <LiquidCrystal_I2C.h>
 LiquidCrystal_I2C lcd(0x27,16,2);
void setup(){  
    lcd.init();
    lcd.backlight();
    lcd.print("Hello");  
    lcd.setCursor(2,1);  
    lcd.print("World!");  
}  
void loop(){
}  