#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <SoftwareSerial.h>
#include "MAX30100_PulseOximeter.h"
SoftwareSerial BTSerial(15,14);

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
  pox.begin();
  pox.setOnBeatDetectedCallback(onBeatDetected);

  pinMode(10, INPUT); // Setup for leads off detection LO +
  pinMode(11, INPUT); // Setup for leads off detection LO - 
}

void loop() {
  float BodyTemp =  mlx.readObjectTempC();
  
  BTSerial.print(BodyTemp);
  BTSerial.print("T");
  
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

   BTSerial.print(HeartRate);
   BTSerial.print("H");

   BTSerial.print(Sp02);
   BTSerial.print("S");

   delay (100); 

    
    // send the value of analog input 0:
    if((digitalRead(10) == 1)||(digitalRead(11) == 1))
    {
      BTSerial.print(0);
      BTSerial.print("E");
    }
    else
    {
      float voltage =  (analogRead(A0));
     // float voltage=5.0/1024.0*1000.0*v;
  
      BTSerial.print(voltage);      
      BTSerial.print("E");

  
    //Wait for a bit to keep serial data from saturating
      delay(150);
    }
}

// Callback (registered below) fired when a pulse is detected
void onBeatDetected()
{
    //Serial.println("Beat!");
}
