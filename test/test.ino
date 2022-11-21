#include <Wire.h>

#define RX8901_ADDR 0x32

#define BIT(nr) (1UL << (nr))

/* RX4801/RX8901 Register definitions */
#define RX48901_REG_SEC    0x00
#define RX48901_REG_MIN   0x01
#define RX48901_REG_HOUR  0x02
#define RX48901_REG_WEEKDAY 0x03
#define RX48901_REG_DAY   0x04
#define RX48901_REG_MONTH 0x05
#define RX48901_REG_YEAR  0x06
#define RX48901_REG_ALM_MIN 0x07
#define RX48901_REG_ALM_HOUR  0x08
#define RX48901_REG_ALM_WEEKDAY 0x09
#define RX48901_REG_WTCNT_L 0x0A
#define RX48901_REG_WTCNT_M 0x0B
#define RX48901_REG_WTCNT_H 0x0C
#define RX48901_REG_TCTL  0x0D
#define RX48901_REG_INTF  0x0E
#define RX48901_REG_INTE  0x0F

#define RX48901_REG_BUF1_CFG2 0x29
#define RX48901_REG_PWSW_CFG  0x37

#define RX48901_REG_SRAM0 0x60
#define RX48901_REG_SRAM1 0x61
#define RX48901_REG_SRAM2 0x62
#define RX48901_REG_SRAM3 0x63
#define RX48901_REG_SRAM4 0x64
#define RX48901_REG_SRAM5 0x65
#define RX48901_REG_SRAM6 0x66
#define RX48901_REG_SRAM7 0x67
#define RX48901_REG_SRAM8 0x68
#define RX48901_REG_SRAM9 0x69
#define RX48901_REG_SRAMA 0x6A
#define RX48901_REG_SRAMB 0x6B
#define RX48901_REG_SRAMC 0x6C
#define RX48901_REG_SRAMD 0x6D
#define RX48901_REG_SRAME 0x6E
#define RX48901_REG_SRAMF 0x6F

/* Timer Control Register (0Dh) bit positions */
#define RX48901_BITS_TCTL_TSEL_1024HZ 0x00
#define RX48901_BITS_TCTL_TSEL_64HZ 0x01
#define RX48901_BITS_TCTL_TSEL_1HZ  0x02
#define RX48901_BITS_TCTL_TSEL_MIN  0x03
#define RX48901_BIT_TCTL_WADA       BIT(3)
#define RX48901_BIT_TCTL_TE         BIT(4)
#define RX48901_BIT_TCTL_USEL0      BIT(5)
#define RX48901_BITS_TCTL_FSEL_32768HZ  0x00
#define RX48901_BITS_TCTL_FSEL_1024HZ 0x40
#define RX48901_BITS_TCTL_FSEL_1HZ  0x80
#define RX48901_BITS_TCTL_FSEL_OFF  0xC0

/* Status Flag Register (0Eh) bit positions */
#define RX48901_BIT_INTF_VTMPLF   BIT(0)
#define RX48901_BIT_INTF_VLF    BIT(1)
#define RX48901_BIT_INTF_EVF    BIT(2)
#define RX48901_BIT_INTF_AF   BIT(3)
#define RX48901_BIT_INTF_TF   BIT(4)
#define RX48901_BIT_INTF_UF   BIT(5)
#define RX48901_BIT_INTF_OSCSTPF  BIT(6)
#define RX48901_BIT_INTF_PORF   BIT(7)

/* Interrupt Enable (0Fh) bit positions */
#define RX48901_BIT_INTE_STOP   BIT(0)
#define RX48901_BIT_INTE_EIE    BIT(2)
#define RX48901_BIT_INTE_AIE    BIT(3)
#define RX48901_BIT_INTE_TIE    BIT(4)
#define RX48901_BIT_INTE_UIE    BIT(5)
#define RX48901_BIT_INTE_CSEL_500MS 0x00
#define RX48901_BIT_INTE_CSEL_2SEC  0x40  /* default */
#define RX48901_BIT_INTE_CSEL_10SEC 0x80
#define RX48901_BIT_INTE_CSEL_30SEC 0xC0

/* Miscellaneous bit positions */
#define RX48901_BIT_ALARM_XWAE    BIT(7)
#define RX48901_BIT_B1C2_SRAMMOD  BIT(6)
#define RX48901_BIT_PWSW_SWSEL    0x04  /* default */
#define RX48901_BIT_PWSW_INIEN    BIT(6)
#define RX48901_BIT_PWSW_CHGEN    BIT(7)

int rx48901_write_reg(const uint8_t addr, const uint8_t val) {
  return 0;
}

int rx48901_read_reg(const uint8_t addr, uint8_t *val) {
  return 0;
}

int rx48901_power_init(bool charge) {
  uint8_t pwsw = RX48901_BIT_PWSW_INIEN | RX48901_BIT_PWSW_SWSEL;
  if(charge) {
    pwsw |= RX48901_BIT_PWSW_CHGEN;
  }
  return rx48901_write_reg(RX48901_REG_PWSW_CFG, 0x00);
}

int rx8901_init() {
  int ret;
  delay(40);           // wait 40ms after power up before interacting with RTC
  ret = rx48901_write_reg(RX48901_REG_ALM_MIN, 0x00);
  if(ret)
    return ret;
  ret = rx48901_write_reg(RX48901_REG_ALM_HOUR, 0x00);
  if(ret)
    return ret;
  ret = rx48901_write_reg(RX48901_REG_ALM_WEEKDAY, 0x00);
  if(ret)
    return ret;
  ret = rx48901_write_reg(RX48901_REG_TCTL, RX48901_BITS_TCTL_TSEL_1HZ | RX48901_BIT_TCTL_WADA | RX48901_BITS_TCTL_FSEL_OFF);
  if(ret)
    return ret;
  ret = rx48901_write_reg(RX48901_REG_BUF1_CFG2, RX48901_BIT_B1C2_SRAMMOD);
  if(ret)
    return ret;
  ret = rx48901_power_init(false);
  if (ret)
    return ret;

  uint8_t flags;
  ret = rx48901_read_reg(RX48901_REG_INTF, &flags);
  if(ret)
    return ret;

  /* clear all flags BUT VLF */
  flags &= ~(RX48901_BIT_INTF_VTMPLF | RX48901_BIT_INTF_EVF | RX48901_BIT_INTF_AF | RX48901_BIT_INTF_TF | RX48901_BIT_INTF_UF | RX48901_BIT_INTF_OSCSTPF | RX48901_BIT_INTF_PORF);
  ret = rx48901_write_reg(RX48901_REG_INTF, flags);


  return ret;
}

static int rx48901_nvmem_read(void *priv, unsigned int offset, void *val, size_t bytes)
{
  u8 *data = val;
  size_t read;
  int ret;
  while (bytes) {
    ret = regmap_write(priv, RX48901_REG_BUF1_CFG2, ((offset>>4) & 0x0F) | RX48901_BIT_B1C2_SRAMMOD);
    if (ret)
      return ret;
    read = 16 - (offset&0x0F);  /* limit read to this page */
    if (read > bytes)
      read = bytes;
    ret = regmap_bulk_read(priv, RX48901_REG_SRAM0 + (offset&0x0F), data, read);
    if (ret)
      return ret;
    data += read;
    offset += read;
    bytes -= read;
  }

  return 0;
}

static int rx48901_nvmem_write(void *priv, unsigned int offset, void *val, size_t bytes)
{
  u8 *data = val;
  size_t write;
  int ret;
  while (bytes) {
    ret = regmap_write(priv, RX48901_REG_BUF1_CFG2, ((offset>>4) & 0x0F) | RX48901_BIT_B1C2_SRAMMOD);
    if (ret)
      return ret;
    write = 16 - (offset&0x0F); /* limit write to this page */
    if (write > bytes)
      write = bytes;
    ret = regmap_bulk_write(priv, RX48901_REG_SRAM0 + (offset&0x0F), data, write);
    if (ret)
      return ret;
    data += write;
    offset += write;
    bytes -= write;
  }

  return 0;
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
  Wire.write(0);              // sends one byte  
  Wire.endTransmission();    // stop transmitting
}
