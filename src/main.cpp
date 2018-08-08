#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define LED_B 2
#define LED_Z 3
#define LED_K 4
#define LED_H 5
#define LED_S 6
#define LED_SAO1 7
#define LED_SAO2 8
#define RGB_PIN 9

/*
  Define these functions ahead of time
*/
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

void sequence(void);
void sequence_reverse(void);
void sequence_flash_after(void);
void sequence_reverse_flash_after(void);
void flash(uint8_t pin);
void flash_all(void);
void flash_times(uint8_t times);
void flash_sequence_times(uint8_t times);
void flash_sequence(void);
void flash_hold_sequence(void);
void flash_all_three(void);
void off(void);

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

void sequence(void) {
  digitalWrite(LED_B, HIGH);
  delay(250);
  digitalWrite(LED_Z, HIGH);
  delay(250);
  digitalWrite(LED_K, HIGH);
  delay(250);
  digitalWrite(LED_H, HIGH);
  delay(250);
  digitalWrite(LED_S, HIGH);
  delay(250);
  digitalWrite(LED_SAO1, HIGH);
  digitalWrite(LED_SAO2, HIGH);
  delay(250);
  off();
}

void sequence_reverse(void) {
  digitalWrite(LED_S, HIGH);
  delay(250);
  digitalWrite(LED_H, HIGH);
  delay(250);
  digitalWrite(LED_K, HIGH);
  delay(250);
  digitalWrite(LED_Z, HIGH);
  delay(250);
  digitalWrite(LED_B, HIGH);
  delay(250);
  digitalWrite(LED_SAO1, HIGH);
  digitalWrite(LED_SAO2, HIGH);
  delay(250);
  off();
}

void sequence_flash_after(void) {
  sequence();
  delay(250);
  flash_all();
  delay(250);
  flash_all();
}

void sequence_reverse_flash_after(void) {
  sequence_reverse();
  delay(250);
  flash_all();
  delay(250);
  flash_all();
}

void flash_all_three(void) {
  flash_times(3);
}

void flash_hold_sequence(void) {
  flash(LED_B);
  delay(250);
  flash(LED_Z);
  delay(250);
  flash(LED_K);
  delay(250);
  flash(LED_H);
  delay(250);
  flash(LED_S);
  delay(250);
  flash(LED_SAO1);
  delay(250);
  flash(LED_SAO2);
  delay(250);
  off();
}

void flash_sequence(void) {
  flash(LED_B);
  flash(LED_Z);
  flash(LED_K);
  flash(LED_H);
  flash(LED_S);
  flash(LED_SAO1);
  flash(LED_SAO2);
}

void flash_sequence_times(uint8_t times) {
  for(uint8_t ii=times;ii>=0;ii--) {
    flash_sequence();
  }
}

void flash_times(uint8_t times) {
  for(uint8_t ii=times;ii>=0;ii--) {
    flash_all();
    delay(100);
  }
}

void flash(uint8_t pin) {
  digitalWrite(pin, HIGH);
  delay(250);
  digitalWrite(pin, LOW);
}

void flash_all(void) {
  digitalWrite(LED_S, HIGH);
  digitalWrite(LED_H, HIGH);
  digitalWrite(LED_K, HIGH);
  digitalWrite(LED_Z, HIGH);
  digitalWrite(LED_B, HIGH);
  digitalWrite(LED_SAO1, HIGH);
  digitalWrite(LED_SAO2, HIGH);
  delay(250);
  digitalWrite(LED_S, LOW);
  digitalWrite(LED_H, LOW);
  digitalWrite(LED_K, LOW);
  digitalWrite(LED_Z, LOW);
  digitalWrite(LED_B, LOW);
  digitalWrite(LED_SAO1, LOW);
  digitalWrite(LED_SAO2, LOW);
}

void off(void) {
  digitalWrite(LED_B, LOW);
  digitalWrite(LED_Z, LOW);
  digitalWrite(LED_K, LOW);
  digitalWrite(LED_H, LOW);
  digitalWrite(LED_S, LOW);
  digitalWrite(LED_SAO1, LOW);
  digitalWrite(LED_SAO2, LOW);
}

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {

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
  switch(random(0, 16)) {
    case 0:
    case 1:
      delay(random(15, 120) * 1000);
      break;
    case 2:
      theaterChaseSequence(randomTimes());
      break;
    case 3:
      colorWipe(randomColor(), 50);
      break;
    case 4:
      theaterChase(randomColor(), 50);
      break;
    case 5:
       rainbowCycle(20);
      break;
    case 6:
      theaterChaseRainbow(50);
      break;
    case 7:
      rainbow(20);
      break;
    case 8:
      colorWipeSequence(randomTimes());
      break;
    case 9:
      sequence();
      break;
    case 10:
      sequence_reverse();
      break;
    case 11:
      sequence_flash_after();
      break;
    case 12:
      sequence_reverse_flash_after();
      break;
    case 13:
      flash_sequence();
      break;
    case 14:
      flash_hold_sequence();
      break;
    case 15:
      flash_all_three();
      break;
    case 16:
      flash_sequence_times(randomTimes());
      break;
    case 17:
      flash_times(randomTimes());
      break;
  }
  pixelsOff();
  off();
}

uint8_t randomTimes() {
  return random(5, 25);
}

uint32_t randomColor() {
  return colors[random(16)];
}

void pixelsOff() {
  for (uint16_t ii=0; ii < strip.numPixels(); ii++) {
    strip.setPixelColor(ii, strip.Color(maxx, zero, zero));
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
