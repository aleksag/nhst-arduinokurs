#include <OneWire.h>
#include "DallasTemperature.h"
#include "LedControl.h"
LedControl lc=LedControl(12,11,10,1); 
// pin 12 of arduino is connected to the led matrix DIN
// pin 11 of arduino is connected to the CLK pin
// pin 10 is connected to CS pin

#define TEMP_SENS_PIN 2 //Onewiresensor is connected to pin 2
OneWire oneWire(TEMP_SENS_PIN);

DallasTemperature sensors(&oneWire);

void setup()
{
  // the zero refers to the MAX7219 number, it is zero for 1 chip
  lc.shutdown(0,false);// turn off power saving, enables display
  lc.setIntensity(0,15);// sets brightness (0~15 possible values)
  lc.clearDisplay(0);// clear screen
  
  
  Serial.begin(9600);
  Serial.println("Setup!");
  // Start up the library
  sensors.begin();
}
void loop()
{
  for (int row=0; row<8; row++)
  {
    for (int col=0; col<8; col++)
    {
      lc.setLed(0,col,row,true); // turns on LED at col, row
      delay(25);
    }
  }

  for (int row=0; row<8; row++)
  {
    for (int col=0; col<8; col++)
    {
      lc.setLed(0,col,row,false); // turns off LED at col, row
      delay(25);
    }
  }
}
