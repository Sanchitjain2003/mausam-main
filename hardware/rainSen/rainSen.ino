int rainpin = 0;
int led = 5;
int ledB = 3;
int soilpin = 1;

void setup (){
    Serial.begin(9600);
    pinMode(rainpin, INPUT);
    pinMode(led, OUTPUT);
    pinMode(soilpin, INPUT);
    pinMode(ledB, OUTPUT);
}

void loop() {
    int rain = analogRead(rainpin);
    int rainIntensity = map(rain, 0, 1023, 0, 255);
    int soil = analogRead(rainpin);
    int soilIntensity = map(rain, 0, 1023, 0, 255);
    Serial.println(rain);
    analogWrite(led, rainIntensity);
    Serial.println(rainIntensity);
    Serial.println("Soil sensor val:" + String(soil));
    analogWrite(ledB, 255);
    Serial.println(soilIntensity);
    delay(3000);
}



// Soil Moisture Sensor needs to be debugged & recalibrated.
