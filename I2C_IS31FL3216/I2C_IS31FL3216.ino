#define DEVICE_ADDR 0xE8

#include <Wire.h>
#include "IS31FL3216.h"


// Functions
void transmit_2(byte addr, byte* sameB)
{
  Wire.beginTransmission(addr);
  Wire.write(sameB, 2);
  Wire.endTransmission();
}

void IS31FL3216_write_byte(byte addr, byte sett){
  byte data[2] = {0xB0,0x55};
  data[0] = addr;
  data[1] = sett;
  transmit_2(DEVICE_ADDR >> 1, data);
}

void SN3216_PWM_INIT(void)
{
	byte pwm_temp=0;
	IS31FL3216_write_byte(0X04,0x00);
	IS31FL3216_write_byte(0X05,0x00);
	IS31FL3216_write_byte(0X07,0x00);
	IS31FL3216_write_byte(CONFIG,SD_OPEN|MODE_PWM|CURRENT_REG);
	IS31FL3216_write_byte(OUT1_PWM,pwm_temp);
	IS31FL3216_write_byte(OUT2_PWM,pwm_temp);
	IS31FL3216_write_byte(OUT3_PWM,pwm_temp);
	IS31FL3216_write_byte(OUT4_PWM,pwm_temp);
	IS31FL3216_write_byte(OUT5_PWM,pwm_temp);
	IS31FL3216_write_byte(OUT6_PWM,pwm_temp);
	IS31FL3216_write_byte(OUT7_PWM,pwm_temp);
	IS31FL3216_write_byte(OUT8_PWM,pwm_temp);
	IS31FL3216_write_byte(OUT9_PWM,pwm_temp);
	IS31FL3216_write_byte(OUT10_PWM,pwm_temp);
	IS31FL3216_write_byte(OUT11_PWM,pwm_temp);
	IS31FL3216_write_byte(OUT12_PWM,pwm_temp);
	IS31FL3216_write_byte(OUT13_PWM,pwm_temp);
	IS31FL3216_write_byte(OUT14_PWM,pwm_temp);
	IS31FL3216_write_byte(OUT15_PWM,pwm_temp);
	IS31FL3216_write_byte(OUT16_PWM,pwm_temp);
	IS31FL3216_write_byte(UPDATE,pwm_temp);
}

void SN3216_PWM_ALL(byte pwm_temp)
{
	IS31FL3216_write_byte(OUT1_PWM,pwm_temp);
	IS31FL3216_write_byte(OUT2_PWM,pwm_temp);
	IS31FL3216_write_byte(OUT3_PWM,pwm_temp);
	IS31FL3216_write_byte(OUT4_PWM,pwm_temp);
	IS31FL3216_write_byte(OUT5_PWM,pwm_temp);
	IS31FL3216_write_byte(OUT6_PWM,pwm_temp);
	IS31FL3216_write_byte(OUT7_PWM,pwm_temp);
	IS31FL3216_write_byte(OUT8_PWM,pwm_temp);
	IS31FL3216_write_byte(OUT9_PWM,pwm_temp);
	IS31FL3216_write_byte(OUT10_PWM,pwm_temp);
	IS31FL3216_write_byte(OUT11_PWM,pwm_temp);
	IS31FL3216_write_byte(OUT12_PWM,pwm_temp);
	IS31FL3216_write_byte(OUT13_PWM,pwm_temp);
	IS31FL3216_write_byte(OUT14_PWM,pwm_temp);
	IS31FL3216_write_byte(OUT15_PWM,pwm_temp);
	IS31FL3216_write_byte(OUT16_PWM,pwm_temp);
	IS31FL3216_write_byte(UPDATE,pwm_temp);
}

// --------------------


/// Main Loop ///////
void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Wire.begin(D1, D2); /* join i2c bus with SDA=D1 and SCL=D2 of NodeMCU */
  SN3216_PWM_INIT();
}

void loop() {
  static byte count = 0;
  Serial.print("Brightness = ");
  Serial.print(count);
  Serial.print("\n");
  SN3216_PWM_ALL(count++);

  if(count > 100)
    count = 0;

  delay(1000);
}
