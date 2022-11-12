#include <IRremote.h>

const int RECV_PIN = 7; // pin D7
const int lamp = 3; // pin D3
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup(){
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);
}

void loop(){
  if (irrecv.decode(&results)){
    Serial.println(results.value, HEX);
    switch(results.value){
      case 0x2FD48B7:
        if (digitalRead(lamp) == 0){
          digitalWrite(lamp, HIGH);  
        }else{
          digitalWrite(lamp, LOW);  
        }
        break ;
    }
    irrecv.resume();
  }
} 
