#include <math.h>

int Analog_Input = A0;
int Digital_Input = 4;

// something wrong here...
double Thermistor(int RawADC){
  double Temp;
  Temp = log(((10240000/RawADC) - 10000)); 
  Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );
  Temp = Temp - 273.15;            // Convert Kelvin to Celcius
  //Temp = (Temp * 9.0)/ 5.0 + 32.0; // Convert Celcius to Fahrenheit
  return Temp;
}

void setup (){
  pinMode (Analog_Input, INPUT);
  pinMode (Digital_Input, INPUT);       
  Serial.begin (9600);
}

void loop (){
  int readVal = analogRead(Analog_Input);
  double temp =  Thermistor(readVal);

  Serial.print(temp);
  Serial.println(" C°");
  Serial.println ("----------------------------------------------------------------");
  delay (1000);
}
