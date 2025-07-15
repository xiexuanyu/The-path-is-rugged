#include <Arduino.h>
#include <FastLED.h>/*用于显示LED灯的库*/
#include <iostream>
using namespace std;
const int LEDS1 = 1; /*设置LED灯数量*/
const int PIN = 48;  /*设置LED灯的引脚为48号*/
CRGB leds[LEDS1];    /*可以理解为数组，方便在下列代码中表示*/
void setup()
{
 
 FastLED.addLeds<WS2812, PIN, GRB>(leds, LEDS1); /*初始化灯带，引脚为48号*/
 
}
void loop()
{

 leds[0]=CRGB::Green;
 FastLED.show();
 delay(250);
 leds[0]=CRGB::Red;
 FastLED.show();
 delay(250);
 leds[0]=CRGB::Blue;
 FastLED.show();
 delay(250);
 leds[0]=CRGB::Orange;
 FastLED.show();
 delay(250);
 leds[0]=CRGB::Purple;
 FastLED.show();
 delay(250);
 leds[0]=CRGB::Yellow;
 FastLED.show();
 delay(250);
 leds[0]=CRGB::White;
 FastLED.show();
 delay(250);
 
};
int main()
{
 setup();
 for (int i = 0;; i++)
 {
  loop();
 }
}
