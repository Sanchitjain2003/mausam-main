#include <EnvironmentCalculations.h>
#include <BME280I2C.h>
#include <Wire.h>

#define SERIAL_BAUD 9600

// Assumed environmental values:
float referencePressure = 1018.6;  // hPa local QFF (official meteor-station reading)
float outdoorTemp = 4.7;           // °C  measured local outdoor temp.
float barometerAltitude = 1650.3;  // meters ... map readings + barometer position


BME280I2C::Settings settings(
   BME280::OSR_X1,
   BME280::OSR_X1,
   BME280::OSR_X1,
   BME280::Mode_Forced,
   BME280::StandbyTime_1000ms,
   BME280::Filter_16,
   BME280::SpiEnable_False,
   BME280I2C::I2CAddr_0x76
);

BME280I2C bme(settings);

//////////////////////////////////////////////////////////////////
void setup()
{
  Serial.begin(SERIAL_BAUD);

  while(!Serial) {} // Wait

  Wire.begin();

  while(!bme.begin())
  {
    Serial.println("Could not find BME280 sensor!");
    delay(1000);
  }

  /*switch(bme.chipModel())
  {
     case BME280::ChipModel_BME280:
       Serial.println("Found BME280 sensor! Success.");
       break;
     case BME280::ChipModel_BMP280:
       Serial.println("Found BMP280 sensor! No Humidity available.");
       break;
     default:
       Serial.println("Found UNKNOWN sensor! Error!");
  }*/
  // Serial.print("Assumed outdoor temperature: "); Serial.print(outdoorTemp);
  // Serial.print("°C\nAssumed reduced sea level Pressure: "); Serial.print(referencePressure);
  // Serial.print("hPa\nAssumed barometer altitude: "); Serial.print(barometerAltitude);
  // Serial.println("m\n***************************************");

}

//////////////////////////////////////////////////////////////////
void loop()
{
  BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
  BME280::PresUnit presUnit(BME280::PresUnit_hPa);
  EnvironmentCalculations::AltitudeUnit envAltUnit  =  EnvironmentCalculations::AltitudeUnit_Meters;
  EnvironmentCalculations::TempUnit     envTempUnit =  EnvironmentCalculations::TempUnit_Celsius;

  float temp(NAN), hum(NAN), pres(NAN);
  bme.read(pres, temp, hum, tempUnit, presUnit);
  float altitude = EnvironmentCalculations::Altitude(pres, envAltUnit, referencePressure, outdoorTemp, envTempUnit);

  Serial.print(temp);
  Serial.print(" ");
  Serial.print(hum);
  Serial.print(" ");
  Serial.print(pres);
  Serial.print(" ");
  Serial.print(altitude);
  Serial.print(" ");
  float dewPoint = EnvironmentCalculations::DewPoint(temp, hum, envTempUnit);
  float seaLevel = EnvironmentCalculations::EquivalentSeaLevelPressure(barometerAltitude, temp, pres, envAltUnit, envTempUnit);
  float absHum = EnvironmentCalculations::AbsoluteHumidity(temp, hum, envTempUnit);
  float heatIndex = EnvironmentCalculations::HeatIndex(temp, hum, envTempUnit);
  Serial.print(dewPoint);
  Serial.print(" ");
  Serial.print(seaLevel);
  Serial.print(" ");
  Serial.print(heatIndex);
  Serial.print(" ");
  Serial.print(absHum);
  Serial.print("\n");
  delay(2000);
}