#include <Wire.h>

#define RX8901_ADDR 0x32

typedef enum {
  RX8901_REG_SEC,
  RX8901_REG_MIN,
  RX8901_REG_HOUR,
  RX8901_REG_WEEKDAY,
  RX8901_REG_DAY,
  RX8901_REG_MONTH,
  RX8901_REG_YEAR,
  RX8901_REG_ALM_MIN,
  RX8901_REG_ALM_HOUR,
  RX8901_REG_ALM_WEEKDAY,
  RX8901_REG_WTCNT_L,
  RX8901_REG_WTCNT_M,
  RX8901_REG_WTCNT_H,
  RX8901_REG_TCTL,
  RX8901_REG_INTF,
  RX8901_REG_TSTP_INTE,

} rx8901_reg_t; 

void rx8901_init() {
  Delay(40);           // wait 40ms after power up before interacting with RTC
}

void setup() {
  // put your setup code here, to run once:
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
  
}

void loop() {
  // put your main code here, to run repeatedly:
  Wire.beginTransmission(4); // transmit to device #4
  Wire.write("x is ");        // sends five bytes
  Wire.write(x);              // sends one byte  
  Wire.endTransmission();    // stop transmitting
}
