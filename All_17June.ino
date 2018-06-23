/*
Arduino-MAX30100 oximetry / heart rate integrated sensor library
Copyright (C) 2016  OXullo Intersecans <x@brainrapers.org>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <SoftwareSerial.h>
#include "MAX30100_PulseOximeter.h"
SoftwareSerial BTSerial(19,18);
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

#define REPORTING_PERIOD_MS     1000

// PulseOximeter is the higher level interface to the sensor
// it offers:
//  * beat detection reporting
//  * heart rate calculation
//  * SpO2 (oxidation level) calculation
PulseOximeter pox;

uint32_t tsLastReport = 0;

// Callback (registered below) fired when a pulse is detected
void onBeatDetected()
{
    Serial.println("Beat!");
}

void setup()
{
    Serial.begin(9600);
    BTSerial.begin(9600);
    Serial.print("Initializing pulse oximeter..");

    // Initialize the PulseOximeter instance
    // Failures are generally due to an improper I2C wiring, missing power supply
    // or wrong target chip
    if (!pox.begin()) {
        Serial.println("FAILED");
        for(;;);
    } else {
        Serial.println("SUCCESS");
    }
    mlx.begin(); 

    // The default current for the IR LED is 50mA and it could be changed
    //   by uncommenting the following line. Check MAX30100_Registers.h for all the
    //   available options.
    // pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);

    // Register a callback for the beat detection
    pox.setOnBeatDetectedCallback(onBeatDetected);
}

void loop()
{
    // Make sure to call update as fast as possible
    pox.update();

    // Asynchronously dump heart rate and oxidation levels to the serial
    // For both, a value of 0 means "invalid"
    if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
      //  Serial.print("Heart rate:");
        BTSerial.print(pox.getHeartRate());
        BTSerial.print("H");
        BTSerial.print(pox.getSpO2());
        BTSerial.println("S");
        Serial.print(pox.getHeartRate());
        Serial.print("H");
        Serial.print(pox.getSpO2());
        Serial.println("S");
        BTSerial.print( mlx.readObjectTempC());
  //Serial.println (30);
  
       BTSerial.print("T");
      /*   if((digitalRead(10) == 1)||(digitalRead(11) == 1))
    {
      BTSerial.print(0);
      //Serial.println(0);
      //Serial.println("E");
      BTSerial.print("E");
    }
    else
    {*/
      float voltage =  (analogRead(A0));
     // float voltage=5.0/1024.0*1000.0*v;
  
      BTSerial.print(voltage);
      //Serial.println (voltage);
      
      BTSerial.print("E");
      //}
        tsLastReport = millis();
    }
}
