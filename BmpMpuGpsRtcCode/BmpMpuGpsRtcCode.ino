
#include<Wire.h>
#include<Adafruit_BMP280.h>
#include<stdlib.h>
#include<string.h>
#include <Adafruit_GPS.h>
#include <Adafruit_GPS.h>
#include "RTClib.h"

Adafruit_BMP280 bmp;  //I2C
SoftwareSerial mySerial(3, 2);    //And finally attach our Serial object pins to our GPS module
Adafruit_GPS GPS(&mySerial);
RTC_DS3231 rtc;
float altitude, temp;
long gyroX, gyroY, gyroZ;
float rotX, rotY, rotZ;
float rpmX,rpmY,rpmZ;
int packet_count=0;
String altstr;
String tempstr;
String packstr;
float latitude1, longitude1, latitude2, longitude2;
String lat1str, long1str, lat2str, long2str;
float nowhr, nowmin, nowsec;
String nowhrstr, nowminstr, nowsecstr; 
String x1;
String x2;
String x3;
String finalprint;
String a("0000");
String d(":"); 
String b(",");
String c("S1");
void setup() {
  Serial.begin(115200);
  Wire.begin();//RPM Measurement
  bmp1();
  setupMPU();
  gps2();
  rtc1();
 
}

void loop() {
    packet_count=packet_count+1;
    packstr=String(packet_count);
    finalprint += a + b + nowhrstr + d + nowminstr + d + nowsecstr + b + packstr + b + c + b + altstr + b + tempstr + b + x1 + x2 + x3 + lat1str + long1str + lat2str + long2str;
    Serial.println(finalprint);
    delay(115200);
    BMPMeasurement();
    recordGyroRegisters();//RPM Measurement
    RPMMeasurement();
    gps1();
    rtc2();
}

void bmp1(){
  if (!bmp.begin(0x76)) {
    while (1);
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}              
void setupMPU(){
  Wire.beginTransmission(0b1101000); //This is the I2C address of the MPU (b1101000/b1101001 for AC0 low/high datasheet sec. 9.2)
  Wire.write(0x6B); //Accessing the register 6B - Power Management (Sec. 4.28)
  Wire.write(0b00000000); //Setting SLEEP register to 0. (Required; see Note on p. 9)
  Wire.endTransmission();  
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x1B); //Accessing the register 1B - Gyroscope Configuration (Sec. 4.4)
  Wire.write(0x00000000); //Setting the gyro to full scale +/- 250deg./s
  Wire.endTransmission();
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x1C); //Accessing the register 1C - Acccelerometer Configuration (Sec. 4.5)
  Wire.write(0b00000000); //Setting the accel to +/- 2g
  Wire.endTransmission();
}
void recordGyroRegisters() {
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x43); //Starting register for Gyro Readings
  Wire.endTransmission();
  Wire.requestFrom(0b1101000,6); //Request Gyro Registers (43 - 48)
  while(Wire.available() < 6);
  gyroX = Wire.read()<<8|Wire.read(); //Store first two bytes into accelX
  gyroY = Wire.read()<<8|Wire.read(); //Store middle two bytes into accelY
  gyroZ = Wire.read()<<8|Wire.read(); //Store last two bytes into accelZ
  processGyroData();
}

void processGyroData() {
  rotX = gyroX / 131.0;
  rpmX=rotX/6;
  rotY = gyroY / 131.0;
  rpmY=rotY/6;
  rotZ = gyroZ / 131.0;
  rpmZ=rotZ/6;
}
void RPMMeasurement() {
  x1=String(rpmX);
  x2=String(rpmY);
  x3=String(rpmZ);
}
void BMPMeasurement()
{
    temp=bmp.readTemperature();
    tempstr=String(temp);
    altitude=bmp.readAltitude(1013.25);
    altstr=String(altitude);
   
}

void gps2(){
  //These lines configure the GPS Module
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA); //Sets output to only RMC and GGA sentences
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); //Sets the output to 1/second. If you want you can go higher/lower
  GPS.sendCommand(PGCMD_ANTENNA); //Can report if antenna is connected or not
}

void gps1(){
  //Now we will start our GPS module, parse (break into parts) the Last NMEA sentence 
  GPS.parse(GPS.lastNMEA()); //This is going to parse the last NMEA sentence the Arduino has received, breaking it down into its constituent parts.
  GPS.newNMEAreceived(); //This will return a boolean TRUE/FALSE depending on the case.
    if (GPS.fix) {
       latitude1=GPS.latitude;
       longitude1=GPS.longitude;
       latitude2=GPS.latitudeDegrees;
       longitude2=GPS.longitudeDegrees;
       lat1str=String(latitude1);
       long1str=String(longitude1);
       lat2str=String(latitude2);
       long2str=String(longitude2);
      
      
      /*
      Serial.print(GPS.latitude, 4); 
      Serial.print(GPS.lat);
      Serial.print(", ");
      Serial.print(GPS.longitude, 4); 
      Serial.println(GPS.lon);
      Serial.print("Location (in degrees, works with Google Maps): ");
      Serial.print(GPS.latitudeDegrees, 4);
      Serial.print(", ");
      Serial.println(GPS.longitudeDegrees, 4);
      Serial.print("Speed (knots): "); 
      Serial.println(GPS.speed);
      Serial.print("Angle: "); 
      Serial.println(GPS.angle);
      Serial.print("Altitude: "); 
      Serial.println(GPS.altitude);
      Serial.print("Satellites: "); 
      Serial.println((int)GPS.satellites);
      */
    }
}

void rtc1(){
  if (! rtc.begin()) {
    
    while (1);
  }

  if (rtc.lostPower()) {
    
  
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
    
    /*Serial.println("Current Date & Time: ");
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    */
    nowhr=now.hour();
    nowmin=now.minute();
    nowsec=now.second();
    nowhrstr=String(nowhr);
    nowminstr=String(nowmin);
    nowsecstr=String(nowsec);
    /*Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println(); */
    
    /*
    Serial.println("Unix Time: ");
    Serial.print("elapsed ");
    Serial.print(now.unixtime());
    Serial.print(" seconds/");
    Serial.print(now.unixtime() / 86400L);
    Serial.println(" days since 1/1/1970");

    */
    
     //calculate a date which is 7 days & 30 seconds into the future
    /*DateTime future (now + TimeSpan(7,0,0,30));
    
    Serial.println("Future Date & Time (Now + 7days & 30s): ");
    Serial.print(future.year(), DEC);
    Serial.print('/');
    Serial.print(future.month(), DEC);
    Serial.print('/');
    Serial.print(future.day(), DEC);
    Serial.print(' ');
    Serial.print(future.hour(), DEC);
    Serial.print(':');
    Serial.print(future.minute(), DEC);
    Serial.print(':');
    Serial.print(future.second(), DEC);
    Serial.println();
    
    Serial.println();
    delay(1000);
    */
}
