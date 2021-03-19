#include "RTClib.h"
RTC_DS3231 rtc;
String nowhrstr, nowminstr, nowsecstr; 
int nowhr,nowmin, nowsec;
void setup() {
rtc1();  

}

void loop() {
  rtc2();

}

void rtc1(){
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    
  
  // Comment out below lines once you set the date & time.
    // Following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  
    // Following line sets the RTC with an explicit date & time
    // for example to set January 19 2021 at 12:56 you would call:
    // rtc.adjust(DateTime(2021, 1, 19, 12, 56, 0));
  }
}

void rtc2(){
    DateTime now = rtc.now();
    
    Serial.println("Current Date & Time: ");
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    
    nowhr=now.hour();
    nowmin=now.minute();
    nowsec=now.second();
    nowhrstr=String(nowhr);
    nowminstr=String(nowmin);
    nowsecstr=String(nowsec);
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    
    
    Serial.println("Unix Time: ");
    Serial.print("elapsed ");
    Serial.print(now.unixtime());
    Serial.print(" seconds/");
    Serial.print(now.unixtime() / 86400L);
    Serial.println(" days since 1/1/1970");
    
}
