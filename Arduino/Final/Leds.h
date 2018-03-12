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

void setLedColor(int color) {
  for (uint8_t i = 0; i < LED_COUNT; i++)
  {
    colorArray[i] = colors[color];
  }

  leds.write(colorArray, LED_COUNT);
}

void blink() {
  rgb_color temp = colorArray[0];

  for(int i = 0; i < 5; i++){
    setLedColor(12);
    delay(500);
    setLedColor(13);
    delay(500);
  }
  
  for (uint8_t i = 0; i < LED_COUNT; i++)
  {
    colorArray[i] = temp;
  }
}

