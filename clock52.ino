#include <FastLED.h> // leds
#include <Wire.h> // rtc
#include <RTClib.h> // rtc
#include <OneWire.h> // digitale temp sensor oneWire interface
#include <DallasTemperature.h> // digitale temp sensor
#include <PinChangeInt.h> // interrupt handler lib
#include <CapacitiveSensor.h> // cap sensor lib
// used constants
#define NUMLEDS 125

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

// clock52 sprites
const uint8_t hetis[] = { 11, 11, 55, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
const uint8_t minuutvijf[] = { 11, 11, 128, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
const uint8_t minuuttien[] = { 11, 11, 0, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
const uint8_t voor1[] = { 11, 11, 0, 0, 60, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
const uint8_t over1[] = { 11, 11, 0, 0, 192, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
const uint8_t kwart[] = { 11, 11, 0, 0, 0, 240, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
const uint8_t half[] = { 11, 11, 0, 0, 0, 0, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
const uint8_t bas[] = { 11, 11, 0, 0, 0, 0, 224, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
const uint8_t over2[] = { 11, 11, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
const uint8_t voor2[] = { 11, 11, 0, 0, 0, 0, 0, 240, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
const uint8_t een[] = { 11, 11, 0, 0, 0, 0, 0, 0, 56, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
const uint8_t twee[] = { 11, 11, 0, 0, 0, 0, 0, 0, 128, 7, 0, 0, 0, 0, 0, 0, 0, 0 };
const uint8_t bir[] = { 11, 11, 0, 0, 0, 0, 0, 0, 0, 56, 0, 0, 0, 0, 0, 0, 0, 0 };
const uint8_t drie[] = { 11, 11, 0, 0, 0, 0, 0, 0, 0, 192, 3, 0, 0, 0, 0, 0, 0, 0 };
const uint8_t vier[] = { 11, 11, 0, 0, 0, 0, 0, 0, 0, 0, 60, 0, 0, 0, 0, 0, 0, 0 };
const uint8_t vijf[] = { 11, 11, 0, 0, 0, 0, 0, 0, 0, 0, 192, 3, 0, 0, 0, 0, 0, 0 };
const uint8_t zes[] = { 11, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 28, 0, 0, 0, 0, 0, 0 };
const uint8_t zeven[] = { 11, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 224, 3, 0, 0, 0, 0, 0 };
const uint8_t negen[] = { 11, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 248, 0, 0, 0, 0, 0 };
const uint8_t acht[] = { 11, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0 };
const uint8_t tien[] = { 11, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 240, 0, 0, 0, 0 };
const uint8_t elf[] = { 11, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0 };
const uint8_t twaalf[] = { 11, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 248, 1, 0, 0 };
const uint8_t uur[] = { 11, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 56, 0, 0 };

const uint8_t cijfers[][9] = {
  { 5, 11, 46, 198, 24, 99, 140, 49, 58 }, // 0
  { 5, 11, 196, 20, 66, 8, 33, 132, 124 }, // 1
  { 5, 11, 46, 66, 132, 8, 17, 34, 124 }, // 2
  { 5, 11, 46, 66, 8, 29, 132, 48, 58 }, // 3
  { 5, 11, 32, 198, 24, 61, 132, 16, 2 }, // 4
  { 5, 11, 46, 132, 16, 28, 132, 16, 58 }, // 5
  { 5, 11, 46, 134, 16, 94, 140, 49, 58 }, // 6
  { 5, 11, 46, 66, 136, 16, 33, 66, 4 }, // 7
  { 5, 11, 46, 198, 24, 127, 140, 49, 58 }, // 8
  { 5, 11, 46, 198, 24, 61, 132, 48, 58 } //9
};

//global variables
CRGB leds[NUMLEDS];
uint8_t lastKnownSecond = 0;
RTC_DS1307 rtc;
volatile boolean BTResetEnabled = true; // needs 2b volatile because of interrupt usage
CRGB color = CRGB::White;
uint8_t state = 0;
uint8_t brightness = 255; // start @ full brightness
CapacitiveSensor sensor_onder = CapacitiveSensor(PIN_CAP_ONDER_SND,PIN_CAP_ONDER_RCV);
CapacitiveSensor sensor_links = CapacitiveSensor(PIN_CAP_LINKS_SND,PIN_CAP_LINKS_RCV);
CapacitiveSensor sensor_rechts = CapacitiveSensor(PIN_CAP_RECHTS_SND,PIN_CAP_RECHTS_RCV);

OneWire oneWireBus(PIN_TMP_DIGI);
DallasTemperature sensor_tmp_digi(&oneWireBus);

void setup() {
  // enable serial (both usb & bluetooth)
  Serial.begin(57600); // BT always uses 57600
  
  //enable BT reset
  pinMode(PIN_RST,OUTPUT);
  attachPinChangeInterrupt(PIN_BTLED,btConnectHandler,FALLING);
  
  // start fastled
  FastLED.addLeds<WS2812B,PIN_LEDS,GRB>(leds,NUMLEDS);
  FastLED.setBrightness(brightness);
  // clear the leds by default
  clearLeds();
  //FastLED.clear();
  FastLED.show();
  
   // begin RTC
   Wire.begin();
   rtc.begin();
   // if RTC is not running, set it to compile date. 
   if (! rtc.isrunning()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
   }
   // begin onewire sensors (digi temp)
   sensor_tmp_digi.begin();   
   Serial.println(" SETUP DONE");
}

void clearLeds() {
  for(uint8_t i=0; i<NUMLEDS;i++) { // type can be uint8_t, strip is max 125 leds
    //leds[i] = CRGB::Green;
    //leds[i] = CRGB(0,100,0);
    leds[i] = CRGB::Black;
  }
}

void loop() {
  // get available sensor data
  long sensor_onder_value = sensor_onder.capacitiveSensor(30);
  long sensor_links_value = sensor_links.capacitiveSensor(30);
  long sensor_rechts_value = sensor_rechts.capacitiveSensor(30);
  int sensor_licht = analogRead(PIN_LIGHT);
  //long sensor_digitemp = // todo
  // is getting rtc time sensor data required every loop?
  DateTime now = rtc.now();
  uint8_t currentSecond = now.second();
  
  // adjust brightness
  brightness = map(sensor_licht,0,1024,1,255);
  FastLED.setBrightness(brightness);
  if(currentSecond != lastKnownSecond) {
    // second changed, update time
    
    // get temp digi (due to timing required we do not run this every loop!
    sensor_tmp_digi.requestTemperatures();
    //float tmp_digi_value = sensor_tmp_digi.getTempCByIndex(0);
    
    // print time on serial
    Serial.print(now.day());Serial.print(F("/"));
    Serial.print(now.month());Serial.print(F("/"));
    Serial.print(now.year());Serial.print(F(" "));
    Serial.print(now.hour());Serial.print(F(":"));
    Serial.print(now.minute());Serial.print(F(":"));
    Serial.println(now.second());
    Serial.print(F("sensor onder = ")); Serial.println(sensor_onder_value);
    Serial.print(F("sensor links = ")); Serial.println(sensor_links_value);
    Serial.print(F("sensor rechts = ")); Serial.println(sensor_rechts_value);
    Serial.print(F("licht = ")); Serial.println(sensor_licht);
    Serial.print(F("brightness = ")); Serial.println(brightness);
    Serial.print(F("sensor digi tmp = ")); Serial.print(sensor_tmp_digi.getTempCByIndex(0)); Serial.println(F(" C"));
    
  }
  //if(sensor_onder_value < 1500) {
    showDefaultClock(now);
  //} else  {
  //  showSeconds(now);
  //}    
  lastKnownSecond = currentSecond; 
}

void showSeconds(DateTime now) {
  clearLeds();
  //FastLED.clear();
  uint8_t tiental = (now.second()-(now.second()%10))/10;
  sprite_ledPrint(leds,cijfers[tiental],0,0,CRGB::Yellow);
  sprite_ledPrint(leds,cijfers[now.second()-(10*tiental)],6,0,CRGB::HotPink);
 FastLED.show(); 
}

void showDefaultClock(DateTime now) {
  // clear the drawing board ;)
    clearLeds();
    //FastLED.clear();
    // print "het is" by default
    sprite_ledPrint(leds,hetis,0,0,color);
    
    
    uint8_t hour2print = now.hour();
    // if minute is greater then 20, we show the upcoming hour
    if(now.minute() >=20) { hour2print = hour2print+1; }
    // show the correct hour
    switch(hour2print) {
      case 0: case 12: case 24: sprite_ledPrint(leds,twaalf,0,0,color); break;
      case 1: case 13: sprite_ledPrint(leds,een,0,0,color); break;
      case 2: case 14: sprite_ledPrint(leds,twee,0,0,color); break;
      case 3: case 15: sprite_ledPrint(leds,drie,0,0,color); break;
      case 4: case 16: sprite_ledPrint(leds,vier,0,0,color); break;
      case 5: case 17: sprite_ledPrint(leds,vijf,0,0,color); break;
      case 6: case 18: sprite_ledPrint(leds,zes,0,0,color); break;
      case 7: case 19: sprite_ledPrint(leds,zeven,0,0,color); break;
      case 8: case 20: sprite_ledPrint(leds,acht,0,0,color); break;
      case 9: case 21: sprite_ledPrint(leds,negen,0,0,color); break;
      case 10: case 22: sprite_ledPrint(leds,tien,0,0,color); break;
      case 11: case 23: sprite_ledPrint(leds,elf,0,0,color); break;
    }
    
    // show the per 5 minute word
    if(now.minute() < 5) {
      sprite_ledPrint(leds,uur,0,0,color);
    } else if(now.minute() < 10) {
      sprite_ledPrint(leds,minuutvijf,0,0,color);
      sprite_ledPrint(leds,over2,0,0,color);
    } else if(now.minute() < 15) {
      sprite_ledPrint(leds,minuuttien,0,0,color);
      sprite_ledPrint(leds,over2,0,0,color);
    } else if(now.minute() < 20) {
      sprite_ledPrint(leds,kwart,0,0,color);
      sprite_ledPrint(leds,over2,0,0,color);
    } else if(now.minute() < 25) {
      sprite_ledPrint(leds,minuuttien,0,0,color);
      sprite_ledPrint(leds,voor1,0,0,color);
      sprite_ledPrint(leds,half,0,0,color);
    } else if(now.minute() < 30) {
      sprite_ledPrint(leds,minuutvijf,0,0,color);
      sprite_ledPrint(leds,voor1,0,0,color);
      sprite_ledPrint(leds,half,0,0,color);
    } else if(now.minute() < 35) {
      sprite_ledPrint(leds,half,0,0,color);
    } else if(now.minute() < 40) {
      sprite_ledPrint(leds,minuutvijf,0,0,color);
      sprite_ledPrint(leds,over1,0,0,color);
      sprite_ledPrint(leds,half,0,0,color);
    } else if(now.minute() < 45) {
      sprite_ledPrint(leds,minuuttien,0,0,color);
      sprite_ledPrint(leds,over1,0,0,color);
      sprite_ledPrint(leds,half,0,0,color);
    } else if(now.minute() < 50) {
      sprite_ledPrint(leds,kwart,0,0,color);
      sprite_ledPrint(leds,voor2,0,0,color);
    } else if(now.minute() < 55) {
      sprite_ledPrint(leds,minuuttien,0,0,color);
      sprite_ledPrint(leds,voor2,0,0,color);
    } else {
      sprite_ledPrint(leds,minuutvijf,0,0,color);
      sprite_ledPrint(leds,voor2,0,0,color);
    }
    
    // zet minuut hoekpunten
    uint8_t modMinuut = now.minute()%5;
    if(modMinuut >=4) { leds[124] = color; }
    if(modMinuut >=3) { leds[123] = color; }
    if(modMinuut >=2) { leds[122] = color; }
    if(modMinuut >=1) { leds[121] = color; }
    
    /*if(now.second()%2) {
        sprite_ledPrint(leds,bir,0,0,CRGB::Yellow);
    } else {
      sprite_ledPrint(leds,bas,0,0,CRGB::Green);
    }*/
    
    // zet datum
    // zet most significant (10/20/30)
    uint8_t dagSign = floor(now.day()/10);
    uint8_t dagEnkel = now.day()%10;
    
    switch(dagSign) {
      case 1: leds[17] = CRGB::Red; break;
      case 2: leds[18] = CRGB::Red; break;
      case 3: leds[10] = CRGB::Red; break;
    }
    // fix substraction 10 - 0 = wrong led, we shou
    if(dagEnkel ==0) {
      leds[0] = CRGB::Red;
    } else {
      leds[10-dagEnkel] = CRGB::Red;
    }
    
    FastLED.show();
}

void sprite_ledPrint(CRGB *leds, const uint8_t *sprite,uint8_t offsetX,uint8_t offsetY, CRGB color) {
  sprite_ledPrint(leds,sprite,offsetX,offsetY,color,true);
}
void sprite_ledPrint(CRGB *leds, const uint8_t *sprite,uint8_t offsetX,uint8_t offsetY, CRGB color,bool transparent) {
  //Serial.println("print call");
  for(uint8_t x=0;x<sprite[0];x++) {
    for(uint8_t y=0;y<sprite[1];y++) {
      if(sprite_getXY(x,y,sprite)) {
        uint8_t pos = XY(x+offsetX,y+offsetY);
        if(transparent) {
          leds[pos] = leds[pos] + color;
        } else {
          leds[pos] = color;
        }
      } else {
        uint8_t pos = XY(x+offsetX,y+offsetY);
        if(!transparent) {
          leds[pos] = CRGB::Black;
        }
      }
    }
  }
}

// get boolean for given x/y position from sprite pointer
boolean sprite_getXY(uint8_t x, uint8_t y,const uint8_t *sprite) {
    uint16_t pixelOffset = ((y*sprite[0])+x);
    uint16_t byteOffset = pixelOffset/8;
    uint8_t bitOffset = pixelOffset - (byteOffset*8);
    return bitRead(sprite[2 + byteOffset],bitOffset);
}

// we have the rows/cols hardcoded because clock does not change it dimensions on the fly. 
// So please fix this if you have a larger/smaller matrix
uint8_t XY(uint8_t x,uint8_t y) {
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
  return 120-i;
}


void btConnectHandler() {
  if(BTResetEnabled) {
    digitalWrite(PIN_RST,HIGH);
  }
}
