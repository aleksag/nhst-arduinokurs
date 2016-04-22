// based on an orginal sketch by Arduino forum member "danigom"
// http://forum.arduino.cc/index.php?action=profile;u=188950

#include <avr/pgmspace.h>
#include "LedControl.h"
#include <OneWire.h>

const int numDevices = 1;      // number of MAX7219s used
const long scrollDelay = 75;   // adjust scrolling speed

unsigned long bufferLong [14] = {0}; 

LedControl lc=LedControl(12,11,10,numDevices);

void setup(){
    for (int x=0; x<numDevices; x++){
        lc.shutdown(x,false);       //The MAX72XX is in power-saving mode on startup
        lc.setIntensity(x,15);       // Set the brightness to default value
        lc.clearDisplay(x);         // and clear the display
    }
    Serial.begin(9600);
}

void loop(){
  displayNumber(2);
  delay(500);
  displayNumber(3);
  delay(500);
  displayNumber(11);
  delay(500);
  displayNumber(10);
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

