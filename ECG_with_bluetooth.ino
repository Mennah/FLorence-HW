#include <Wire.h>
#include <SoftwareSerial.h>
SoftwareSerial BTSerial(15,14);


// initialize the serial port
// and declare inputs and outputs
void setup() {
  pinMode(10, INPUT); // Setup for leads off detection LO +
  pinMode(11, INPUT); // Setup for leads off detection LO - }
  Serial.begin(9600);
  BTSerial.begin(9600);
}

// read from the analog input connected to the LDR
// and print the value to the serial port.
// the delay is only to avoid sending so much data
// as to make it unreadable.
void loop() 
{
  /*if((digitalRead(10) == 1)||(digitalRead(11) == 1))
  {
  BTSerial.write('!');
  BTSerial.println();
  }
  else
  {*/
    // send the value of analog input 0:
    float voltage = analogRead(A0);
    float voltage=5.0/1024.0*1000.0*v;
    BTSerial.write(voltage);
    Serial.println(voltage));
  //}
  //Wait for a bit to keep serial data from saturating
  delay(50);
}




