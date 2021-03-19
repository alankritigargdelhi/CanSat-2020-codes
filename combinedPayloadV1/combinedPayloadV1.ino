
#include<Wire.h>
#include<Adafruit_BMP280.h>
#include<stdlib.h>
#include<string.h>
#include "RTClib.h"

Adafruit_BMP280 bmp;  //I2C
RTC_DS3231 rtc;
float alt,pressure, temp;
int packet_count=0;
String altstr,tempstr,pressurestr;
String packstr;
float nowhr, nowmin, nowsec;
String nowhrstr, nowminstr, nowsecstr;
long unixtime1; 
String finalprint;
const int buzzer=11;
String a("3394");
String d(":"); 
String b(",");
String c("S1"); //denotes science payload 1
void setup() {
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
  setupBMP();
  rtc1();
}

void loop() {
    packet_count=packet_count+1;
    packstr=String(packet_count);
    finalprint += a + b + nowhrstr + d + nowminstr + d + nowsecstr + b + packstr + b + c + b + altstr + b + tempstr;
    Serial.println(finalprint);
    delay(115200);
    BMPmeasurement();
    rtc2();
    buzzerON();
}

void setupBMP(){
    Serial.println(F("BMP280 calibration"));

  if (!bmp.begin()) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1);
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

 delay(500);
}
                 
void BMPmeasurement(){
    Serial.print(F("Temperature = "));
    Serial.print(bmp.readTemperature(),1);
    Serial.println(" *C");

    Serial.print(F("Pressure = "));
    Serial.print(bmp.readPressure(),1); //displaying the Pressure in Pa, you can change the unit
    Serial.println(" Pa");

    Serial.print(F("Approx altitude = "));
    Serial.print(bmp.readAltitude(1019.66),1); //The "1019.66" is the pressure(hPa) at sea level
    Serial.println(" m");                    
    alt=bmp.readAltitude(1019.66),1;
    Serial.println();
    alt=bmp.readAltitude(1019.66),1;
    pressure=bmp.readPressure(),1;  //comment out everything related to pressure later bcz pressure not needed in telemtry KEPT HERE ONLY FOR TESTING
    temp=bmp.readTemperature(),1;
    altstr=String(alt);
    tempstr=String(temp);
    pressurestr=String(pressure); 
    delay(2000);
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
    unixtime1=now.unixtime();
    Serial.print(" seconds/");
    //Serial.print(now.unixtime() / 86400L);
    //Serial.println(" days since 1/1/1970"); 
    
}

void buzzerON(){
  if (alt<5){
    Serial.println("Turning buzzer ON for recovery");
    tone(buzzer, 1000);
    delay(500);
  }
  else{
    tone(buzzer, 0);
  }
}
