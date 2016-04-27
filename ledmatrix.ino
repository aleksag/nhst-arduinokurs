// based on an orginal sketch by Arduino forum member "danigom"
// http://forum.arduino.cc/index.php?action=profile;u=188950

#include <avr/pgmspace.h>
#include "LedControl.h"
#include <math.h>
#include "DallasTemperature.h"
#include <OneWire.h>
#define TEMP_SENS_PIN 2 //Onewiresensor is connected to pin 2

LedControl display=LedControl(12,11,10,1);
OneWire oneWire(TEMP_SENS_PIN);
DallasTemperature sensors(&oneWire);
const uint64_t IMAGES[] = {
  0x0000001d1515151d,
  0x0000000505050505,
  0x0000001d051d111d,
  0x0000001d111d111d,
  0x00000011111d1515,
  0x0000001d111d051d,
  0x0000001d151d051d,
  0x000000111111111d,
  0x0000001d151d151d,
  0x00000011111d151d,
  0x0000007751575477,
  0x0000001711171417,
  0x0000007711774477,
  0x0000007741774477,
  0x0000004741775457,
  0x0000007741771477,
  0x0000007751771477,
  0x0000004741474477,
  0x0000007751775477,
  0x0000004741775477,
  0x0000007754575477,
  0x0000001714171417,
  0x0000007714774477,
  0x0000007744774477,
  0x0000004744775457,
  0x0000007744771477,
  0x0000007754771477,
  0x0000004744474477,
  0x0000007754775477,
  0x0000004744775477,
  0x003c428124242400
};
const int IMAGES_LEN = sizeof(IMAGES)/8;
void displayImage(uint64_t image) {
  for (int i = 0; i < 8; i++) {
    byte row = (image >> i * 8) & 0xFF;
    for (int j = 0; j < 8; j++) {
      display.setLed(0, i, j, bitRead(row, j));
    }
  }
}


void setup() {
  display.clearDisplay(0);
  display.shutdown(0, false);
  display.setIntensity(0, 15);
  Serial.begin(9600);
  sensors.begin();
  displayImage(IMAGES[30]);
  delay(3000);
}


int i = 0;

void loop() {

  sensors.requestTemperatures();
  float temperature = sensors.getTempCByIndex(0);
  int rounded = round(temperature);
  Serial.println(temperature);
  Serial.println(rounded);
  displayImage(IMAGES[rounded-10]);
  delay(500);
}

