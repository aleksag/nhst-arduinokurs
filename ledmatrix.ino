// based on an orginal sketch by Arduino forum member "danigom"
// http://forum.arduino.cc/index.php?action=profile;u=188950

#include <avr/pgmspace.h>
#include "LedControl.h"
#include "DallasTemperature.h"
#include <OneWire.h>
#define TEMP_SENS_PIN 2 //Onewiresensor is connected to pin 2

LedControl lc=LedControl(12,11,10,1);
OneWire oneWire(TEMP_SENS_PIN);
DallasTemperature sensors(&oneWire);


void setup(){
    lc.shutdown(0,false);       //The MAX72XX is in power-saving mode on startup
    lc.setIntensity(0,15);       // Set the brightness to default value
    lc.clearDisplay(0);         // and clear the display
    Serial.begin(9600);
    sensors.begin();
}

static char outstr[15];

void loop(){
  sensors.requestTemperatures();
  float temperature = sensors.getTempCByIndex(0);
  Serial.println("temperature:");
  Serial.print(temperature);
  dtostrf(temperature,4, 2, outstr);
  Serial.println("Digits:");
  Serial.println(outstr[0]-'0');
  Serial.println(outstr[1]-'0');
  Serial.println(outstr[3]-'0');
  Serial.println(outstr[4]-'0');

  displayNumber(outstr[0]-'0');
  delay(500);
  displayNumber(outstr[1]-'0');
  delay(500);
  displayNumber(12);
  delay(500);
  displayNumber(outstr[3]-'0');
  delay(500);
  displayNumber(outstr[4]-'0');
  delay(500);
}


unsigned char texts[]  = {      //Numeric Font Matrix (Arranged as 7x font data + 1x kerning data)
    B01110000,	//0
    B10001000,
    B10011000,
    B10101000,
    B11001000,
    B10001000,
    B01110000,


    B01000000,	//1
    B11000000,
    B01000000,
    B01000000,
    B01000000,
    B01000000,
    B11100000,
   

    B01110000,	//2
    B10001000,
    B00001000,
    B00010000,
    B00100000,
    B01000000,
    B11111000,


    B11111000,	//3
    B00010000,
    B00100000,
    B00010000,
    B00001000,
    B10001000,
    B01110000,
  

    B00010000,	//4
    B00110000,
    B01010000,
    B10010000,
    B11111000,
    B00010000,
    B00010000,
 

    B11111000,	//5
    B10000000,
    B11110000,
    B00001000,
    B00001000,
    B10001000,
    B01110000,
   

    B00110000,	//6
    B01000000,
    B10000000,
    B11110000,
    B10001000,
    B10001000,
    B01110000,
  

    B11111000,	//7
    B10001000,
    B00001000,
    B00010000,
    B00100000,
    B00100000,
    B00100000,

    B01110000,	//8
    B10001000,
    B10001000,
    B01110000,
    B10001000,
    B10001000,
    B01110000,

    B01110000,	//9
    B10001000,
    B10001000,
    B01111000,
    B00001000,
    B00010000,
    B01100000,



    B01110000,	//C
    B10001000,
    B10000000,
    B10000000,
    B10000000,
    B10001000,
    B01110000,


    B01100000,	// (Char 0x7F)
    B10010000,
    B10010000,
    B01100000,
    B00000000,
    B00000000,
    B00000000,

    B00000000,  //.
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00011000,
    B00011000,
};

int offset = 1;
int debug = 0;
void displayNumber(int number){
  int rowstart = number*7;
  for(int row = rowstart;row < rowstart+7;row++){
    unsigned char rowbits = texts[row];
    //Serial.println(rowbits,BIN);
    for (int col = 0; col < 8; col++){
      if(bitRead(rowbits, col) == 1){
        lc.setLed(0,row-rowstart,8-col+offset,true);
        if(debug){
          Serial.print("Turning on led row:");
          Serial.print(row-rowstart);
          Serial.print(",Col");
          Serial.print(8-col+offset);
          Serial.println("");
        }
      }else{
        lc.setLed(0,row-rowstart,8-col+offset,false);
        if(debug){
          Serial.print("Turning OFF led row:");
          Serial.print(row-rowstart);
          Serial.print(",Col");
          Serial.print(8-col+offset);
          Serial.println("");
        }
      }
    }
    
  }
}

