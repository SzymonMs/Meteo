#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Adafruit_BMP085.h>
#include "DHT.h" 
       
#define DHTPIN 2          

DHT dht;  
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0);  
Adafruit_BMP085 bmp;
 
void setup()
{
  u8g2.begin();
  dht.setup(DHTPIN);    
  if (!bmp.begin())
  {while (1){}}
}
 
void loop(void){
  
delay(dht.getMinimumSamplingPeriod());

int h = dht.getHumidity();  
float temp =bmp.readTemperature();
int pres=bmp.readPressure()/100;

u8g2.clearBuffer();
u8g2.setFont(u8g2_font_t0_13b_mr);

//Pomiar temperatury
u8g2.setCursor(5,10);
u8g2.print(temp);
u8g2.print(" *C");
//Pomiar wilgotności
u8g2.setCursor(70,10);
u8g2.print(" RH ");
u8g2.print(h);
u8g2.print("%");
//Pomiar ciśnienia
u8g2.setCursor(5,30);
u8g2.print(pres);
u8g2.print(" hPa");

u8g2.sendBuffer();

delay(2000);
}
