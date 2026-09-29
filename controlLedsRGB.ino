#include <Arduino.h>
#include <FastLED.h>

#define NUM_LEDS 15

#ifndef PIN_DATA
#define PIN_DATA 15
#endif  

#define CLOCK_PIN 13

CRGB leds[NUM_LEDS];

void setup() {
    Serial.begin(115200); 
}

void loop() {
  for (int i = 0; i < NUM_LEDS; ++i) {
    if(i==12){
      leds[i] = CRGB::Red;  
    }
    if(i==13){
      leds[i] = CRGB::Green;  
    }
    if(i==14){
      leds[i] = CRGB::Blue;  
    }
    if(i==0||i==1||i==2){
      leds[i]=CRGB::Blue;
    
    }if(i==5||i==6||i==7||i==8||i==9||i==10||i==11){
      leds[i]=CRGB::White;
    }
    
    if(i==3||i==4){
      leds[i]=CRGB::Yellow;
    }
  }
  
  FastLED.show();
  delay(500);
}

