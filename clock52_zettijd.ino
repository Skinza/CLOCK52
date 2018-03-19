
#include <Wire.h> // rtc
#include <RTClib.h> // rtc
#include <PinChangeInterrupt.h> // interrupt handler lib

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
#define PIN_SCL A5
#define PIN_SDA A4

#define USE_DS3231


#ifdef USE_DS3231 
RTC_DS3231 rtc;
#else
RTC_DS1307 rtc;
#endif
volatile boolean BTResetEnabled = true; // needs 2b volatile because of interrupt usage
void setup() {
  Serial.begin(57600); // BT always uses 57600
  
  //enable BT reset
  pinMode(PIN_RST,OUTPUT);
  //pinMode(PIN_BTLED,INPUT_PULLUP);
  attachPCINT(digitalPinToPCINT(PIN_BTLED),btConnectHandler,FALLING);
  
   // begin RTC
   Wire.begin();
   rtc.begin();
   rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}


void loop() {
}

void btConnectHandler() {
  Serial.print(F("Reset called"));
  if(BTResetEnabled) {
    digitalWrite(PIN_RST,HIGH);
  }
}
