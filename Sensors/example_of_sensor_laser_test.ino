#include "distance_sensor.h"

void setup() 
    {
        Serial.begin(9600);
    }
void loop() 
    {
       /*  int laser_address=22;
         int laser_pin=4;
         bool Is_set_address=true;
         static laser_VL53L0X laser_VL53L0X_1(laser_address,laser_pin);    
         Serial.println(  laser_VL53L0X_1.get_distance (Is_set_address) ) ;*/


         static laser_VL53L0X laser_VL53L0X_1(22,4);    // (int Address , int pin )
         Serial.println(  laser_VL53L0X_1.get_distance (0) ) ;
        
    }
