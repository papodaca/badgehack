#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define SW_SAO1 7
#define SW_SAO2 8
#define RGB_PIN 6

/*
  Define these functions ahead of time
*/
void maybeTurnOnSao();
uint32_t randomColor();
uint8_t randomTimes();
void pixelsOff();
void colorWipeSequence(uint8_t times);
void theaterChaseSequence(uint8_t times);
void colorWipe(uint32_t c, uint8_t wait);
void rainbow(uint8_t wait);
void rainbowCycle(uint8_t wait);
void theaterChase(uint32_t c, uint8_t wait);
void theaterChaseRainbow(uint8_t wait);
uint32_t Wheel(byte WheelPos);

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(31, RGB_PIN, NEO_GRB + NEO_KHZ800);

uint8_t maxx = 255;
uint8_t half = 255/2;
uint8_t zero = 0;

uint32_t colors[16] = {
  strip.Color(maxx, zero, zero),
  strip.Color(zero, maxx, zero),
  strip.Color(zero, zero, maxx),
  strip.Color(maxx, maxx, zero),
  strip.Color(maxx, zero, maxx),
  strip.Color(zero, maxx, maxx),
  strip.Color(maxx, zero, half),
  strip.Color(maxx, half, zero),
  strip.Color(half, maxx, zero),
  strip.Color(zero, maxx, half),
  strip.Color(half, zero, maxx),
  strip.Color(zero, half, maxx),
  strip.Color(maxx, maxx, half),
  strip.Color(maxx, half, maxx),
  strip.Color(half, maxx, maxx),
  strip.Color(maxx, maxx, maxx)
};

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {

  pinMode(SW_SAO1, OUTPUT);
  pinMode(SW_SAO2, OUTPUT);

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

/*

void sequence(void);
void sequence_reverse(void);
void sequence_flash_after(void);
void sequence_reverse_flash_after(void);
void flash_times(uint8_t times);
void flash_sequence_times(uint8_t times);
void flash_sequence(void);
void flash_hold_sequence(void);
void flash_all_three(void);

*/

void loop() {
  switch(random(0, 9)) {
    case 0:
    case 1:
      delay(random(15, 120) * 1000);
      break;
    case 2:
      maybeTurnOnSao();
      theaterChaseSequence(randomTimes());
      break;
    case 3:
      maybeTurnOnSao();
      colorWipe(randomColor(), 50);
      break;
    case 4:
      maybeTurnOnSao();
      theaterChase(randomColor(), 50);
      break;
    case 5:
      maybeTurnOnSao();
      rainbowCycle(20);
      break;
    case 6:
      maybeTurnOnSao();
      theaterChaseRainbow(50);
      break;
    case 7:
      maybeTurnOnSao();
      rainbow(20);
      break;
    case 8:
      maybeTurnOnSao();
      colorWipeSequence(randomTimes());
      break;
  }
  digitalWrite(SW_SAO1, LOW);
  digitalWrite(SW_SAO2, LOW);
  pixelsOff();
}

void maybeTurnOnSao() {
  if(random(0,3) == 1) {
    digitalWrite(SW_SAO2, HIGH);
  }
  if(random(0,3) == 1) {
    digitalWrite(SW_SAO1, HIGH);
  }
}

uint8_t randomTimes() {
  return random(5, 25);
}

uint32_t randomColor() {
  return colors[random(16)];
}

void pixelsOff() {
  for (uint8_t ii=0; ii < strip.numPixels(); ii++) {
    strip.setPixelColor(ii, strip.Color(zero, zero, zero));
  }
  strip.show();
}

void colorWipeSequence(uint8_t times) {
  for(uint8_t ii=times;ii>0;ii--) {
    colorWipe(randomColor(), 50);
  }
}

void theaterChaseSequence(uint8_t times) {
  for(uint8_t ii=times;ii>0;ii--) {
    theaterChase(randomColor(), 50);
  }
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
