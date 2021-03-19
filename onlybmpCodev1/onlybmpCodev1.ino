#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp; // I2C Interface

float alt;

void setup() {
  Serial.begin(9600);
  setupBMP();
}

void loop() {
BMPmeasurement();
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
    delay(2000);
}
  
