#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Adafruit_BMP085.h>
#include "DHT.h"
#include <DS3231.h>

#define DHTPIN 2
DHT dht;
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0);
Adafruit_BMP085 bmp;
DS3231 clock;
RTCDateTime dt;
const char DEGREE_SYMBOL[] = {0xB0,'\0'};

void i_am(U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C screen){
    screen.clearBuffer();
    
   screen.setCursor(10, 10);
//   screen.drawStr("°");
    screen.print("SZYMON MURAWSKI");
    screen.setCursor(25, 30);
    screen.print("AiR 144485");
    screen.sendBuffer();
    delay(4000);
}
void meteo(U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C screen,DHT dht1,Adafruit_BMP085 bmp1){
    screen.clearBuffer();
    delay(dht1.getMinimumSamplingPeriod());
    int h = dht1.getHumidity();
    float temp = bmp1.readTemperature();
    int pres = bmp1.readPressure() / 100;
    screen.setCursor(5, 10);
    screen.print(temp);
    screen.print(" ");
    screen.print(DEGREE_SYMBOL);
    screen.print("C");
    screen.setCursor(70, 10);
    screen.print(" RH ");
    screen.print(h);
    screen.print("%");
    screen.setCursor(5, 30);
    screen.print(pres);
    screen.print(" hPa");
    screen.sendBuffer();
    delay(2000);
}
void times(U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C screen){
    screen.clearBuffer();
    dt = clock.getDateTime();
    screen.setCursor(30, 10);
    screen.print(dt.day);
    screen.print("-");
    screen.print(dt.month);
    screen.print("-");
    screen.print(dt.year);
    screen.setCursor(45, 30);
    screen.print(dt.hour);
    screen.print(":");
    screen.print(dt.minute);
    screen.sendBuffer();
    delay(2000);
}

void setup()
{
  Serial.begin(9600);
  clock.begin();
  clock.setDateTime(__DATE__, __TIME__);
  u8g2.begin();
  dht.setup(DHTPIN);
  if (!bmp.begin()){
    while (1) {}
  }
  u8g2.setFont(u8g2_font_t0_13_tf);
  i_am(u8g2);
}
void loop(void) {
    times(u8g2);
    meteo(u8g2,dht,bmp);

}
