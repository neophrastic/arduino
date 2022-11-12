#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

// An IR detector/demodulator is connected to GPIO pin 5 (D1 on a NodeMCU board).
// Note: GPIO 16 won't work on the ESP8266 as it does not have interrupts.
const uint16_t kRecvPin = 5; // pin D1
unsigned long key_value = 0;
const int lamp = 0; // pin D3
IRrecv irrecv(kRecvPin);

decode_results results;

void setup() {
  Serial.begin(115200);
  irrecv.enableIRIn();  // Start the receiver
  while (!Serial)  // Wait for the serial connection to be establised.
    delay(50);
  Serial.println();
  Serial.print("IRrecvDemo is now running and waiting for IR message on Pin ");
  Serial.println(kRecvPin);
  pinMode(lamp, OUTPUT);
}

void loop() {
  if (irrecv.decode(&results)) {
    // print() & println() can't handle printing long longs. (uint64_t)
    serialPrintUint64(results.value, HEX);
    Serial.println("");

    switch(results.value){
          case 0x2FD48B7:
            if (digitalRead(lamp) == 0){
              digitalWrite(lamp, HIGH);  
             }else{
            digitalWrite(lamp, LOW);  
              }
          break ;
        }
        
    irrecv.resume();  // Receive the next value
  }
}
