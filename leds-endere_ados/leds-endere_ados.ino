#include <Adafruit_NeoPixel.h>

#define PINO 4
#define NUMERO_DE_LED 18

Adafruit_NeoPixel led(NUMERO_DE_LED, PINO, NEO_GRB + NEO_KHZ800);
#define DELAY 100

void setup() {
 Serial.begin(9600);
 led.begin();
}

void loop() {
  led.clear();
  for(int i=0; i<NUMERO_DE_LED; i++){
      led.setPixelColor(i,led.Color(0,255,255));
      led.show();
      delay(DELAY);
    }
   led.clear();
   for(int i=NUMERO_DE_LED; i>0; i--){
      led.setPixelColor(i,led.Color(0,255,255));
      led.show();
      delay(DELAY);
    }

}
