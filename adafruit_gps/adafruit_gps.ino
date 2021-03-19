#include <Adafruit_GPS.h>
SoftwareSerial mySerial(3, 2);    //And finally attach our Serial object pins to our GPS module
Adafruit_GPS GPS(&mySerial);

float latitude1, longitude1, latitude2, longitude2;
String lat1str, long1str, lat2str, long2str;

void  setup(){
  setupGPS();
}

void loop(){
  dataGPS();
}

void setupGPS(){
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA); //Sets output to only RMC and GGA sentences
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); //Sets the output to 1/second. If you want you can go higher/lower
  GPS.sendCommand(PGCMD_ANTENNA); //Can report if antenna is connected or not
}

void dataGPS(){
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
     
    }
}
