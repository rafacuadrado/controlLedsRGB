#include <Arduino.h>
#include <SPI.h>
#include <mcp2515.h>
#include <FastLED.h>

#define NUM_LEDS 15

#ifndef PIN_DATA
#define PIN_DATA 15
#endif

#define CLOCK_PIN 13
float colorInicial = 0;
CRGB leds[NUM_LEDS];
struct mensaje{
  int identificador;
  int R;
  int G;
  int B;
  int brillo;
};
MCP2515 mcp2515(9);  // CS en pin 9

void setup()
{
    FastLED.addLeds<WS2812B, PIN_DATA, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(255);
    Serial.begin(115200);
    SPI.begin();

    mcp2515.reset();
    mcp2515.setBitrate(CAN_500KBPS, MCP_20MHZ);
    mcp2515.setNormalMode();
}

void loop() {
  /*struct can_frame frame;
  struct mensaje msg;
  if (mcp2515.readMessage(&frame) == MCP2515::ERROR_OK) {
    msg.identificador = frame.can_id;
    msg.R = frame.data[0];
    msg.G = frame.data[1];
    msg.B = frame.data[2];
    msg.brillo = frame.data[3];


    if(msg.identificador==0){
      for (int i = 0; i < NUM_LEDS&&(i!=12||i!=13||i!=14); ++i) {
        leds[i] = CRGB(msg.R, msg.G, msg.B);
      }
      FastLED.setBrightness(msg.brillo);
      FastLED.show();
    }else if(msg.identificador==1){
        leds[12] = CRGB(msg.R, msg.G, msg.B);
      FastLED.setBrightness(msg.brillo);
      FastLED.show();
    }else if(msg.identificador==2){
        leds[13] = CRGB(msg.R, msg.G, msg.B);
      FastLED.setBrightness(msg.brillo);
      FastLED.show();
    }else if(msg.identificador==3){
        leds[14] = CRGB(msg.R, msg.G, msg.B);
      FastLED.setBrightness(msg.brillo);
      FastLED.show();
    }

  }
  /*for (int i = 0; i < NUM_LEDS; ++i) {
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
  */
  //fill_rainbow(leds, NUM_LEDS, colorInicial, 15);
  //colorInicial+=0.25;
  for (int i = 0; i < NUM_LEDS; ++i) {

  leds[i]=CRGB::Green;
  }
  FastLED.show();
}