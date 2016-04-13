#include <FastLED.h> // leds
#include <Wire.h> // rtc
#include <RTClib.h> // rtc
#include <OneWire.h> // digitale temp sensor oneWire interface
#include <DallasTemperature.h> // digitale temp sensor
#include <PinChangeInt.h> // interrupt handler lib
#include <CapacitiveSensor.h> // cap sensor lib
// used constants
#define NUMLEDS 125
#define NUMSPOTSMAX 153
#define NUMSPOTS 20
//pin constants
#define PIN_CAP_RECHTS_SND 12
#define PIN_CAP_RECHTS_RCV 11
#define PIN_CAP_LINKS_SND 10
#define PIN_CAP_LINKS_RCV 9
#define PIN_CAP_ONDER_SND 8
#define PIN_CAP_ONDER_RCV 7
#define PIN_LEDS 5
#define PIN_RST 4
#define PIN_TMP_DIGI 6
#define PIN_BTLED A0
#define PIN_LIGHT A2
#define PIN_TMP_ANALOG A1
#define PIN_SCL A4
#define PIN_SDA A5

CRGB leds[NUMLEDS];
// bright spots
uint8_t spots[NUMSPOTS];


void setup() {
   // enable serial (both usb & bluetooth)
  Serial.begin(57600); // BT always uses 57600
  
  //enable BT reset
  pinMode(PIN_RST,OUTPUT);
  attachPinChangeInterrupt(PIN_BTLED,btConnectHandler,FALLING);
  
  randomSeed(analogRead(PIN_LIGHT));
  random16_add_entropy( random() );
  
  // start fastled
  FastLED.addLeds<WS2812B,PIN_LEDS,GRB>(leds,NUMLEDS);
  
  // fill random spots by default (11*11+3) 3 regels om van het beeld weg te faden
  for(uint8_t i=0;i<NUMSPOTS;i++) {
    spots[i] = random8(NUMSPOTSMAX/2,NUMSPOTSMAX);
  }
}

void loop() {
  //Serial.println("-----");
  FastLED.clear();
  
  
  
  
  
  for(uint8_t r=0;r<121;r++) { leds[r] = CRGB(0,0,0); }
  
  for(uint8_t i=0;i<NUMSPOTS;i++) {
    //Serial.print(F("spots["));Serial.print(i);Serial.print(F("] = ")); Serial.println(spots[i]);
    // spot is volledig out of range als hij lager dan 11 wordt, alles hoger dan 11 een regeln aar beneden
    //Serial.print(F("X = "));Serial.print(getX(spots[i],NUMSPOTSMAX));Serial.print(F(" | Y = ")); Serial.println(getY(spots[i],NUMSPOTSMAX));
    //Serial.print(F("teruggezet: ")); Serial.println(XY(getX(spots[i],NUMSPOTSMAX),getY(spots[i],NUMSPOTSMAX),NUMSPOTSMAX));
    //Serial.println(F("<=>"));
    if(spots[i] >= 11) {
      spots[i] = XY(getX(spots[i],NUMSPOTSMAX),getY(spots[i],NUMSPOTSMAX)+1,NUMSPOTSMAX);
      // spot is geshift... teken de spots (indien in tekenveld). tekenveld is van NUMSPOTSMAX <--> 33
      // helder
      if(spots[i] >= 33 && spots[i] < NUMSPOTSMAX) {
        leds[spots[i]-33] = CRGB(255,255,255);
      }
      // blauw
      uint8_t follow1 = XY(getX(spots[i],NUMSPOTSMAX),getY(spots[i],NUMSPOTSMAX)-1,NUMSPOTSMAX);
      if(follow1 >= 33 && follow1 < NUMSPOTSMAX) {
        leds[follow1-33] = CRGB(0,100,0);
      }
      uint8_t follow2 = XY(getX(spots[i],NUMSPOTSMAX),getY(spots[i],NUMSPOTSMAX)-2,NUMSPOTSMAX);
      if(follow2 >= 33 && follow2 < NUMSPOTSMAX) {
        leds[follow2-33] = CRGB(0,30,0);
      }
    // spot zit op de onderste rij, dus niet meer in beeld, genereer nieuw random spot punt
    } else { spots[i] = random8(NUMSPOTSMAX/2,NUMSPOTSMAX); }
   
    /*if(spots[i] < ) { // check if spot is withing display
      leds[spots[i]] = CRGB::White;
    }*/
  }
  /*leds[XY(0,0)] = CRGB::Red;
  leds[XY(3,9)] = CRGB::Yellow;
  leds[XY(10,0)] = CRGB::Blue;*/
  FastLED.delay(90);
  
}

// we have the rows/cols hardcoded because clock does not change it dimensions on the fly. 
// So please fix this if you have a larger/smaller matrix
uint8_t XY(uint8_t x,uint8_t y, uint8_t upperleft) {
    uint8_t i;
  if( y & 0x01) {
    // Odd rows run backwards
    uint8_t reverseX = (11 - 1) - x;
    i = (y * 11) + reverseX;
  } else {
    // Even rows run forwards
    i = (y * 11) + x;
  }
  // led 0 is lower right corner
  // led 120 is upper left corner
  // 0,0 is upper left corner, zo we need to substract i from de number of leds (indexed 0)
  // calc: rows*cols - 1 = 11*11 - 1 = 121 - 1 = 120 
  return upperleft-i;
}
// default = 121 leds (upperleft is 120, 0 based)
uint8_t XY(uint8_t x,uint8_t y) {
  return XY(x,y,120);
}

uint8_t getY(uint8_t ledPosition, uint8_t upperleft) {
  return (upperleft/11)-(ledPosition/11);
}

uint8_t getX(uint8_t ledPosition, uint8_t upperleft) {
  uint8_t y = getY(ledPosition,upperleft);
  if(y & 0x01) {
    return (ledPosition%11);
  } else {
    return 10-(ledPosition%11);
  }
}


void btConnectHandler() {
  if(true) {
    digitalWrite(PIN_RST,HIGH);
  }
}
