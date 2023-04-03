#include <Arduino.h>

#define ntc_pin 12

float Rt = 0;                // 热敏电阻的阻值
const float R1 = 10.0;       // NTC连接的分压电阻10K
const float T = 273.15 + 25; // 参考温度
const int B = 3334;  // 温度范围25~85℃

void setup()
{
  Serial.begin(115200);
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
  Serial.println(((T * B) / (B + T * log(Rt / R1))) - 273.15);
  
  delay(1000);
}