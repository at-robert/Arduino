#include <SPI.h>

#define PIN_VSYNC   D2      // GPIO4
#define PIN_CS    D8      // GPIO15

void setup() {
  Serial.begin(115200);

   // 初始化 SPI
  SPI.begin(); // 預設 SCLK:14, MISO:12, MOSI:13

  // 設定 GPIO 為輸出
  pinMode(PIN_VSYNC, OUTPUT);
  pinMode(PIN_CS, OUTPUT);

  digitalWrite(PIN_VSYNC, LOW);
  digitalWrite(PIN_CS, HIGH);  // CS 初始為高（閒置）

  digitalWrite(PIN_VSYNC, HIGH);
  delayMicroseconds(20);
  digitalWrite(PIN_VSYNC, LOW);
  delayMicroseconds(100);
  //delay(1);

  //delayMicroseconds(100);
}

void spiSendWord(uint16_t data) {
  SPI.transfer(highByte(data));  // 傳送高位元組
  SPI.transfer(lowByte(data));   // 傳送低位元組
}


void loop() {
  int i = 0;
  uint16_t chk_sum = 0x0000,indor = 0x00000, cmd = 0x0000,dat_buf = 0x0000;

  // 使用 SPI 傳送資料
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));    // 8 MHz
  digitalWrite(PIN_CS, LOW);           // 啟動 SPI 裝置
  delayMicroseconds(10);

  indor = 0xAA55; // indicator
  cmd = 0x0000; // command
  dat_buf = 0xFF00; // Data
  chk_sum = 0x0000; // Checksum
  
  spiSendWord(indor);
  chk_sum = chk_sum ^ indor;
  
  spiSendWord(cmd);
  chk_sum = chk_sum ^ cmd;
  
  for(i =0 ;i < 1152 ; i++){
    spiSendWord(dat_buf); //1152個
    chk_sum = chk_sum ^ dat_buf;
  }
  
  spiSendWord(chk_sum);
  
  
  // 傳送一個 byte
  digitalWrite(PIN_CS, HIGH);          // 關閉 SPI 裝置
  SPI.endTransaction(); //傳輸結束

  digitalWrite(PIN_VSYNC, HIGH);
  delayMicroseconds(20);
  digitalWrite(PIN_VSYNC, LOW);
  delayMicroseconds(100);
}
