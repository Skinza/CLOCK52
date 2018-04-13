#include <FastLED.h> // leds
#include <RTClib.h> // rtc
#include <PinChangeInterrupt.h> // interrupt handler lib

#include <Wire.h> // rtc

// used constants
#define NUMLEDS 125
#define MATRIX_WIDTH 11
#define MATRIX_HEIGHT 11

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

CRGB leds[NUMLEDS+1];
RTC_DS3231 rtc;
uint8_t lastKnownSecond = 0;

volatile boolean BTResetEnabled = true; // needs 2b volatile because of interrupt usage
uint8_t brightness = 255; // start @ full brightness

void setup() {
  // enable serial (both usb & bluetooth)
  Serial.begin(57600); // BT always uses 57600
  // put your setup code here, to run once:
  FastLED.addLeds<WS2812B, PIN_LEDS, GRB>(leds, NUMLEDS);
  //enable BT reset
  pinMode(PIN_RST,OUTPUT);
  //pinMode(PIN_BTLED,INPUT_PULLUP);
  attachPCINT(digitalPinToPCINT(PIN_BTLED),btConnectHandler,FALLING);
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
}
void clearLeds() {
  for(uint8_t i=0; i<NUMLEDS;i++) { // type can be uint8_t, strip is max 125 leds
    //leds[i] = CRGB::Green;
    //leds[i] = CRGB(0,100,0);
    leds[i] = CRGB::Black;
  }
}
void loop() {
  DateTime now = rtc.now();
  // put your main code here, to run repeatedly:
 
  int seconde = now.second();
  int uur = now.hour();
  int minuut = now.minute();
  double hoekSeconde,hoekMinuut,hoekUur = 0;
  bool goUp=true;
  //leds[XY(10,11)].r=1;
  //while(true) {
    
    int sensor_licht = analogRead(PIN_LIGHT);
    //long sensor_digitemp = // todo
    // is getting rtc time sensor data required every loop?
    uint8_t currentSecond = now.second();
  
    // adjust brightness
    brightness = map(sensor_licht,0,1024,1,255);
    FastLED.setBrightness(brightness);
    if(currentSecond != lastKnownSecond) { 
      // print time on serial
    Serial.print(now.day());Serial.print(F("/"));
    Serial.print(now.month());Serial.print(F("/"));
    Serial.print(now.year());Serial.print(F(" "));
    Serial.print(now.hour());Serial.print(F(":"));
    Serial.print(now.minute());Serial.print(F(":"));
    Serial.println(now.second());
      clearLeds();
      
      //leds[XY(5,10)] = CRGB::Purple; //12
      leds[XY(7,9)] = CRGB::Purple; //1
      leds[XY(9,7)] = CRGB::Purple; //2
      //leds[XY(10,5)] = CRGB::Purple; //3
      leds[XY(9,3)] = CRGB::Purple; //4
      leds[XY(7,1)] = CRGB::Purple; //5
      //leds[XY(5,0)] = CRGB::Purple; // 6
      leds[XY(3,1)] = CRGB::Purple; // 7
      leds[XY(1,3)] = CRGB::Purple; // 8
      //leds[XY(0,5)] = CRGB::Purple; // 9
      leds[XY(1,7)] = CRGB::Purple; // 10
      leds[XY(3,9)] = CRGB::Purple; // 11
      
      /*hoekSeconde=(360-((seconde/60.0)*360))+90;
      if(hoekSeconde >360){hoekSeconde=hoekSeconde-360;}
      double radSeconde = (hoekSeconde*71)/4068.0;
      drawLine(round(5+6*cos(radSeconde)),round(5+6*sin(radSeconde)),5,5,CRGB::Green);*/

      double minuutFrac = minuut + (seconde/60.0);
      hoekMinuut=(360-((minuutFrac/60.0)*360))+90;
      if(hoekMinuut >360){hoekMinuut=hoekMinuut-360;}
      double radMinuut = (hoekMinuut*71)/4068.0;
      drawLine(round(5+5*cos(radMinuut)),round(5+5*sin(radMinuut)),5,5,CRGB::Blue);

      double uurFrac = uur + (minuut/60.0);
      hoekUur=(360-((uurFrac/12.0)*360))+90;
      if(hoekUur >360){hoekUur=hoekUur-360;}
      double radUur = (hoekUur*71)/4068.0;
      drawLine(round(5+3*cos(radUur)),round(5+3*sin(radUur)),5,5,CRGB::Red);

      leds[XY(5,5)] = CRGB::White;

     
      
      FastLED.show();
    }


    

   
    lastKnownSecond = currentSecond; 
    
  //}
}

void dummyPrintLed() {
  for(int y=0; y < MATRIX_HEIGHT; y++) {
    Serial.print("|");
    for(int x=0; x < MATRIX_WIDTH; x++) {
      Serial.print(leds[(y*MATRIX_WIDTH)+x].r); Serial.print("|");
    }
    Serial.println();
  }
  Serial.println("===============");
}

/*uint8_t XY (uint8_t x, uint8_t y) {
  // any out of bounds address maps to the first hidden pixel
  if ( (x >= MATRIX_WIDTH) || (y >= MATRIX_HEIGHT) ) {
    return (121);
  }

  const uint8_t XYTable[] = {
   110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120,
    99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109,
    88,  89,  90,  91,  92,  93,  94,  95,  96,  97,  98,
    77,  78,  79,  80,  81,  82,  83,  84,  85,  86,  87,
    66,  67,  68,  69,  70,  71,  72,  73,  74,  75,  76,
    55,  56,  57,  58,  59,  60,  61,  62,  63,  64,  65,
    44,  45,  46,  47,  48,  49,  50,  51,  52,  53,  54,
    33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,
    22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,
    11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,
     0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10
  };

  uint8_t i = (y * MATRIX_WIDTH) + x;
  uint8_t j = XYTable[i];
  return j;
}*/

void drawLine(int8_t x0,int8_t y0, int8_t x1, int8_t y1, CRGB val) {
  int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
  int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
  int err = (dx>dy ? dx : -dy)/2, e2;
  int pos;
  for(;;){
    pos = XY(x0,y0);
    if(pos <= 120) {
      leds[pos]=val;
    }
    if (x0==x1 && y0==y1) break;
    e2 = err;
    if (e2 >-dx) { err -= dy; x0 += sx; }
    if (e2 < dy) { err += dx; y0 += sy; }
  }
  
}

// we have the rows/cols hardcoded because clock does not change it dimensions on the fly. 
// So please fix this if you have a larger/smaller matrix
/*uint8_t XY(uint8_t x,uint8_t y) {
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
}*/


// Params for width and height
const uint8_t kMatrixWidth = 11;
const uint8_t kMatrixHeight = 11;

#define LAST_VISIBLE_LED 120
uint8_t XY (uint8_t x, uint8_t y) {
  // any out of bounds address maps to the first hidden pixel
  if ( (x >= kMatrixWidth) || (y >= kMatrixHeight) ) {
    return (LAST_VISIBLE_LED + 1);
  }

  const uint8_t XYTable[] = {
    10,   9,   8,   7,   6,   5,   4,   3,   2,   1,   0,
    11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,
    32,  31,  30,  29,  28,  27,  26,  25,  24,  23,  22,
    33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,
    54,  53,  52,  51,  50,  49,  48,  47,  46,  45,  44,
    55,  56,  57,  58,  59,  60,  61,  62,  63,  64,  65,
    76,  75,  74,  73,  72,  71,  70,  69,  68,  67,  66,
    77,  78,  79,  80,  81,  82,  83,  84,  85,  86,  87,
    98,  97,  96,  95,  94,  93,  92,  91,  90,  89,  88,
    99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109,
   120, 119, 118, 117, 116, 115, 114, 113, 112, 111, 110
  };

  uint8_t i = (y * kMatrixWidth) + x;
  uint8_t j = XYTable[i];
  return j;
}


void btConnectHandler() {
  Serial.print(F("Reset called"));
  if(BTResetEnabled) {
    digitalWrite(PIN_RST,HIGH);
  }
}

