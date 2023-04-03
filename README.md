采用的热敏电阻型号：10kΩ，电阻精度:±1%，3380K  
热敏电阻的阻值与温度之间的关系：$ Rt = R0 * exp(B * (1/T - 1/T0)) $  
* Rt：热敏电阻在温度T下的阻值
* R0：热敏电阻在参考温度T0下的阻值
* T0 = 298.15
* B：热敏电阻的B值
* exp：自然指数函数
* T：热敏电阻的工作温度（单位：开尔文）
示例程序：采用ESP32作为主控，ADC为12位，2^12=4096
```c
#include <Arduino.h>

#define ntc_pin 34
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
```
