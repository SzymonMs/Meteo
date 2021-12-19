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


void setup()
{
  Serial.begin(9600);
  clock.begin();
  // Ustawiany date i godzine kompilacji szkicu
  clock.setDateTime(__DATE__, __TIME__);
  u8g2.begin();
  dht.setup(DHTPIN);
  if (!bmp.begin())
  {
    while (1) {}
  }
}

void loop(void) {

  dt = clock.getDateTime();

  delay(dht.getMinimumSamplingPeriod());

  int h = dht.getHumidity();
  float temp = bmp.readTemperature();
  int pres = bmp.readPressure() / 100;

  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_t0_13b_mr);

  //Pomiar temperatury
  u8g2.setCursor(5, 10);
  u8g2.print(temp);
  u8g2.print(" *C");
  //Pomiar wilgotności
  u8g2.setCursor(70, 10);
  u8g2.print(" RH ");
  u8g2.print(h);
  u8g2.print("%");
  //Pomiar ciśnienia
  u8g2.setCursor(5, 30);
  u8g2.print(pres);
  u8g2.print(" hPa");
  //Czas
  //u8g2.setCursor(0,30);
  //u8g2.print(dt.year);
  //u8g2.print("-");
  //u8g2.print(dt.month);
  //u8g2.print("-");
  //u8g2.print(dt.day);
  //u8g2.print(" ");
  //u8g2.print(dt.hour);
  //u8g2.print(":");
  //u8g2.print(dt.minute);
  //u8g2.print(":");
  //u8g2.print(dt.second);

  u8g2.sendBuffer();


  delay(1000);
}
