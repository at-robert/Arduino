/* This example shows how to use continuous mode to take
range measurements with the VL6180X. It is based on
vl53l0x_ContinuousRanging_Example.c from the VL53L0X API.

The range readings are in units of mm. */

#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor;

void setup()
{
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
  Wire.begin();

  sensor.init();
  sensor.setTimeout(500);

  // Start continuous back-to-back mode (take readings as
  // fast as possible).  To use continuous timed mode
  // instead, provide a desired inter-measurement period in
  // ms (e.g. sensor.startContinuous(100)).
  sensor.startContinuous();
}

void loop()
{
  static int i = 0;

  Serial.print("The TOF distance = ");
  Serial.print(sensor.readRangeContinuousMillimeters());
  if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }

  Serial.println();

  if(i == 0){
     digitalWrite(LED_BUILTIN, HIGH);
     i = 1;
  }
  else{
    i = 0;
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  }
}
