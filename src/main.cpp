/*
  Titre      : Test
  Auteur     : Crepin Vardin Fouelefack
  Date       : 27/10/2022
  Description: description
  Version    : 0.0.1
*/

#include <Arduino.h>
#include "WIFIConnector_MKR1000.h"
#include "MQTTConnector.h"
 #include <Adafruit_I2CDevice.h>
 #include <Adafruit_Sensor.h>
#include <Adafruit_NeoPixel.h>

int LedPinR    = 2; 
int LedPinB    = 1;
int LedPinV    = 5;
#define PIN_LED 4   // Control signal, connect to DI of the LED
int NUM_LED    = 1;   // Number of LEDs in a strip


bool BouttonR ;
bool BouttonB ;
bool BouttonV ;

// Custom colour3: Green
#define RED_VAL_3       0
#define GREEN_VAL_3     255
#define BLUE_VAL_3      0

// Custom colour2: Red
#define RED_VAL_2       255
#define GREEN_VAL_2     0
#define BLUE_VAL_2      0

// Custom colour1: Blue
#define RED_VAL_1       0
#define GREEN_VAL_1     0
#define BLUE_VAL_1      255

Adafruit_NeoPixel RGB_Strip = Adafruit_NeoPixel(NUM_LED, PIN_LED, NEO_GRB + NEO_KHZ800);




// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint16_t wait) {
  for (uint16_t i = 0; i < RGB_Strip.numPixels(); i++) {
    RGB_Strip.setPixelColor(i, c);
    RGB_Strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if (WheelPos < 85) {
    return RGB_Strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    return RGB_Strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
    WheelPos -= 170;
    return RGB_Strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < RGB_Strip.numPixels(); i++) {
      RGB_Strip.setPixelColor(i, Wheel((i + j) & 255));
    }
    RGB_Strip.show();
    delay(wait);
  }
}

void setup() {

// Open serial communications and wait for port to open:
  //wifiConnect(); 
  //MQTTConnect(); 

  pinMode(LedPinR, INPUT);
  pinMode(LedPinB, INPUT);
  pinMode(LedPinV, INPUT);
  RGB_Strip.begin();
  RGB_Strip.show();
  RGB_Strip.setBrightness(50);    // Set brightness, 0-255 (darkest - brightest)
}


void loop() {
  
  //Ecout des messages de broker MQTT
  //ClientMQTT.loop();
   // Open serial communications and wait for port to open:
   // Serial.begin(9600);
  
  BouttonR = digitalRead(LedPinR);
  BouttonB = digitalRead(LedPinB);
  BouttonV = digitalRead(LedPinV);

  if (BoutR)
  {
    colorWipe(RGB_Strip.Color(RED_VAL_2, GREEN_VAL_2, BLUE_VAL_2), 1000);   // Custom colour2: Red
  }
  
  if (BoutB)
  {
    colorWipe(RGB_Strip.Color(RED_VAL_1, GREEN_VAL_1, BLUE_VAL_1), 1000);   // Custom colour1: Blue
  }
  
  if (BoutV)
  {
    colorWipe(RGB_Strip.Color(RED_VAL_3, GREEN_VAL_3, BLUE_VAL_3), 1000);   // Custom colour3: Green
  }
  
  //rainbow(20);  // Rainbow
  Serial.println("Couldn't find RTC");
  appendPayload("BouttonRouge", BouttonR);
  appendPayload("BouttonBleue", BouttonB);
  appendPayload("BouttonVert", BouttonV);
  //Envoie de la chaine
   sendPayload();
}