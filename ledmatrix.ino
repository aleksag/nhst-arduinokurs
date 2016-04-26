#include <OneWire.h>
#include "DallasTemperature.h"

#define TEMP_SENS_PIN 2 //Onewiresensor is connected to pin 2
OneWire oneWire(TEMP_SENS_PIN);

DallasTemperature sensors(&oneWire);

void setup()
{
  sensors.begin();
}
void loop()
{
  sensors.requestTemperatures();
  float temperatureCelsius = sensors.getTempCByIndex(0);
}
