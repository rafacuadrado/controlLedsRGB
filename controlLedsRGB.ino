#include <Arduino.h>
#include <SPI.h>
#include <mcp2515.h>
#include <FastLED.h>

#define NUM_LEDS 15

#ifndef PIN_DATA
#define PIN_DATA 15
#endif

CRGB leds[NUM_LEDS];
MCP2515 mcp2515(9); // CS en pin 9
uint8_t brilloC02=0;
uint8_t brillo02=0;
uint8_t brilloFreon=0;
uint8_t brilloAlarms=0;
uint8_t brilloComms=0;
uint8_t brilloLED1=0;
uint8_t brilloLED2=0;
uint8_t brilloLED3=0;

struct MensajeLED {
    uint32_t identificador;
    uint8_t R;
    uint8_t G;
    uint8_t B;
    uint8_t brillo;
};

void setup() {
    Serial.begin(115200);
    
    FastLED.addLeds<WS2812B, PIN_DATA, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(255);
    FastLED.clear(true);        

    SPI.begin();

    mcp2515.reset();
    mcp2515.setBitrate(CAN_500KBPS, MCP_20MHZ);
    mcp2515.setNormalMode();
}

void loop() {
  struct can_frame frame;

  if (mcp2515.readMessage(&frame) == MCP2515::ERROR_OK && frame.can_dlc >= 4) {
    MensajeLED msg;
    msg.identificador = frame.can_id & CAN_SFF_MASK;
    msg.R = frame.data[0];
    msg.G = frame.data[1];
    msg.B = frame.data[2];

    if (msg.identificador==0){
      for (int i = 0; i < 2; ++i) {
        brilloC02 = frame.data[3];
        leds[i] = CRGB(msg.R, msg.G, msg.B);
        leds[i].nscale8(brilloC02);

      }
    }
    if (msg.identificador==1){
        brillo02 = frame.data[3];
        leds[2] = CRGB(msg.R, msg.G, msg.B);
        leds[2].nscale8(brillo02);

    }
    if (msg.identificador==2){
      for (int i = 3; i < 5; ++i) {
        brilloFreon = frame.data[3];
        leds[i] = CRGB(msg.R, msg.G, msg.B);
        leds[i].nscale8(brilloFreon);

      }            
    }
    else if (msg.identificador==3){
      for (int i = 5; i < 9; ++i) {
        brilloComms = frame.data[3];
        leds[i] = CRGB(msg.R, msg.G, msg.B);
        leds[i].nscale8(brilloComms);

      }
    }else if (msg.identificador==4){
      for (int i = 9; i < 12; ++i) {
        brilloAlarms = frame.data[3];
        leds[i] = CRGB(msg.R, msg.G, msg.B);
        leds[i].nscale8(brilloAlarms);

      }
    }
    else if (msg.identificador==5){
      brilloLED1 = frame.data[3];
      leds[12] = CRGB(msg.R, msg.G, msg.B);
      leds[12].nscale8(brilloLED1);
    
    }else if(msg.identificador==6){
      brilloLED2 = frame.data[3];
      leds[13] = CRGB(msg.R, msg.G, msg.B);
      leds[13].nscale8(brilloLED2);
    }else if(msg.identificador==7){
      brilloLED3 = frame.data[3];
      leds[14] = CRGB(msg.R, msg.G, msg.B);
      leds[14].nscale8(brilloLED3);
    }
    FastLED.show();
  }
  //FILTROS HARDWARE MCP 2515:
  //interrupciones mcp2515 configurar pin interrupcion hardware.
  //posibilidad de hacer un sistema de gesión del clor mas complejo y del brillo con variables de color 
  //y brillo para ca grupo de leds y así no que por ejemplo todos los leds no vayan con el mismo brillo
}