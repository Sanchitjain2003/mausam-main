//#include <MySensors.h>  
#include <SPI.h>
#define CHILD_ID_DUST 0
#define DUST_SENSOR_ANALOG_PIN 0

int ledPower = 12;
const int numreadings = 60;

unsigned long SLEEP_TIME = 10*1000; // Sleep time between reads (in milliseconds)
//VARIABLES
int val = 0;// variable to store the value coming from the sensor
float valDUST = 0.0;
float lastDUST =0.0;
int samplingTime = 280;
int deltaTime = 40;
int sleepTime = 9680;
float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;


void setup(){
 //gw.begin();
 pinMode(ledPower,OUTPUT);
 Serial.begin(9600);
 // Send the sketch version information to the gateway and Controller
 //gw.sendSketchInfo("Dust Sensor", "1.1");
 // Register all sensors to gateway (they will be created as child devices)
 //gw.present(CHILD_ID_DUST, S_DUST);  
}

void loop(){
float cumsum = 0;
float temp = 0;
float temp1 = 0;
float cum_density = 0;
     for (int sample = 0; sample < numreadings; sample ++){ // loop reading dust sensor
       digitalWrite(ledPower,LOW); // power on the LED
       delayMicroseconds(samplingTime);
       uint16_t voMeasured = analogRead(DUST_SENSOR_ANALOG_PIN);// Get DUST value
       delayMicroseconds(deltaTime);
        digitalWrite(ledPower,HIGH); // turn the LED off
       // 0 - 5V mapped to 0 - 1023 integer values
       // recover voltage
       temp = voMeasured * (5.0 / 1024.0);
       cumsum = cumsum + temp;// cumulative sum over 60 seconds
       delay(1000);
       Serial.print("reading sample: ");
       Serial.println(sample);
       Serial.print("Raw Signal Value (0-1023): ");
       Serial.println(voMeasured);    
       Serial.print(" - cumulative: ");
       Serial.println(cumsum);
}
// linear eqaution taken from http://www.howmuchsnow.com/arduino/airquality/
// Chris Nafis (c) 2012
dustDensity = (0.17 * cumsum - 0.1)* (1000/60);
       
Serial.print(" - Dust Density: ");
Serial.println(dustDensity); // unit: ug/m3
Serial.println("#########################################");

//  if (ceil(dustDensity) != lastDUST) {
//      gw.send(dustMsg.set((int)ceil(dustDensity)));
//      lastDUST = ceil(dustDensity);
//  }
//gw.send(dustMsg.set((int)ceil(dustDensity)));
delay(SLEEP_TIME);
}
