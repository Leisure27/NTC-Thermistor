#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

#define ntc_pin 12

float Rt = 0;                // 热敏电阻的阻值
const float R1 = 10.0;       // NTC连接的分压电阻10K
const float T = 273.15 + 25; // 参考温度
const int B = 3334;          // 温度范围25~85℃
float temp = 0;

void setup()
{
  Serial.begin(115200);

  u8g2.begin();
  u8g2.enableUTF8Print();
  pinMode(ntc_pin, INPUT);
}

void loop()
{
  int ntcvalue = analogRead(ntc_pin);
  Rt = (4095.0 / (float)ntcvalue - 1.0) * R1;

  Serial.print("NTC模拟量：");
  Serial.println(ntcvalue);

  Serial.print("NTC阻值：");
  Serial.println(Rt);

  Serial.print("PCB温度：");
  temp = ((T * B) / (B + T * log(Rt / R1))) - 273.15;
  Serial.println(temp);

  // OLED数据显示
  u8g2.setFont(u8g2_font_wqy12_t_gb2312b); // 设置中文字符集
  u8g2.clearBuffer();
  u8g2.setCursor(0, 15);
  u8g2.print("NTC模拟量：");
  u8g2.print(ntcvalue);
  u8g2.sendBuffer();

  u8g2.setCursor(0, 35);
  u8g2.print("NTC阻值：");
  u8g2.print(Rt);
  u8g2.sendBuffer();

  u8g2.setCursor(0, 55);
  u8g2.print("PCB温度：");
  u8g2.print(temp);
  u8g2.sendBuffer();

  delay(1000);
}