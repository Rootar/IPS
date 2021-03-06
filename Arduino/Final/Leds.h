#include <PololuLedStrip.h>


PololuLedStrip<LED_PIN> leds;
rgb_color colors[LED_COLORS] = {
  {100, 0, 0},  //RED
  {100, 50, 0}, //ORANGE
  {100, 100, 0},//YELLOW
  {50, 100, 0}, //LIGHT GREEN
  {0, 100, 0},  //GREEN
  {0, 100, 50}, //GREEN / BLUE
  {0, 100, 100},//LIGHT LIGHT BLUE
  {0, 50, 100}, //LIGHT BLUE
  {0, 0, 100},  //BLUE
  {50, 0, 100}, //PURPLE
  {100, 0, 100},//PINK
  {100, 0, 50}, //PINKERERERERERER
  {0, 0, 0},    //NONE
  {255, 255, 255}//WHITE
};
rgb_color colorArray[LED_COUNT];


//=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0
void Leds(){
  for (uint8_t i = 0; i < LED_COUNT; i++)
  {
    colorArray[i] = colors[12];
  }

  leds.write(colorArray, LED_COUNT);
}

//=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0
void SetLedColor(int color) {
  for (uint8_t i = 0; i < LED_COUNT - 1; i++)
  {
    colorArray[i] = colors[color];
  }

  leds.write(colorArray, LED_COUNT - 1);
}


//=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0
void Blink() {
  rgb_color temp = colorArray[0];

  for(int i = 0; i < 5; i++){
    SetLedColor(12);
    delay(500);
    SetLedColor(13);
    delay(500);
  }
  
  for (uint8_t i = 0; i < LED_COUNT - 1; i++)
  {
    colorArray[i] = temp;
  }
}


//=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0
void Shot(){
  colorArray[LED_COUNT - 1] = colors[0];
  leds.write(colorArray, LED_COUNT);
  delay(100);
  colorArray[LED_COUNT - 1] = colors[12];
  leds.write(colorArray, LED_COUNT);  
}


