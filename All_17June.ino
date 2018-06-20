#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <SoftwareSerial.h>
#include "MAX30100_PulseOximeter.h"
SoftwareSerial BTSerial(15,14);

String Frame = "";
//For Temp
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

//For Max
#define REPORTING_PERIOD_MS     1000
PulseOximeter pox;
uint32_t tsLastReport = 0;

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);
  mlx.begin();  
  
  pox.setOnBeatDetectedCallback(onBeatDetected);

  pinMode(10, INPUT); // Setup for leads off detection LO +
  pinMode(11, INPUT); // Setup for leads off detection LO - 
}

void loop() {
  float BodyTemp =  mlx.readObjectTempC();
  BTSerial.print("T");
  Serial.println ("T");
  //BTSerial.write(BodyTemp);
  BTSerial.print(30);
  Serial.println (30);
  delay (100);

  
  pox.update();
  // Asynchronously dump heart rate and oxidation levels to the serial
    // For both, a value of 0 means "invalid"
    float HeartRate;
    float Sp02;
    if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
        HeartRate = pox.getHeartRate();
        Sp02 = pox.getSpO2();
        tsLastReport = millis();
    }
   BTSerial.print("H");
   Serial.println ("H");
   //BTSerial.write(HeartRate);
   BTSerial.print(130);
   Serial.println (130);
   BTSerial.print("S");
   Serial.println ("S");
   //BTSerial.write(Sp02);
   BTSerial.print(1130);
   Serial.println (1130);
   delay (100); 

    
    // send the value of analog input 0:
    float voltage =  (analogRead(A0));
   // float voltage=5.0/1024.0*1000.0*v;
    BTSerial.print("E");
    Serial.println ("E");
    BTSerial.print(voltage);
    Serial.println (voltage);
  //Wait for a bit to keep serial data from saturating
  delay(150);
}

// Callback (registered below) fired when a pulse is detected
void onBeatDetected()
{
    //Serial.println("Beat!");
}
