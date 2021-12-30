#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Adafruit_BMP085.h>
#include "DHT.h"
#include <DS3231.h>

#define DHTPIN 2
#define START 8
#define SET 9
#define UP 10

DHT dht;
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0);
Adafruit_BMP085 bmp;
DS3231 clock;
int year = 2021;
int month = 0;
int day = 0;
int hour = 12;
int minute = 0;
RTCDateTime dt;
bool running = false;
int counter = 0;
const char DEGREE_SYMBOL[] = {0xB0, '\0'};

void i_am(U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C screen) {
  screen.clearBuffer();

  screen.setCursor(10, 10);
  screen.print("SZYMON MURAWSKI");
  screen.setCursor(5, 30);
  screen.print("USTAW CZAS I DATE");
  screen.sendBuffer();
  delay(10);
}
void meteo(U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C screen, DHT dht1, Adafruit_BMP085 bmp1) {
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
void times(U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C screen, RTCDateTime dt, int tim) {

  screen.clearBuffer();
  screen.setCursor(30, 10);
  if(day<10)
  screen.print("0");
  screen.print(day);
  screen.print("-");
  if(month<10)
  screen.print("0");
  screen.print(month);
  screen.print("-");
  screen.print(year);
  screen.setCursor(45, 30);
  if(hour<10)
  screen.print("0");
  screen.print(hour);
  screen.print(":");
  if(minute<10)
  screen.print("0");
  screen.print(minute);
  screen.sendBuffer();
  delay(tim);
}
void times2(U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C screen, RTCDateTime dt, int tim) {

  screen.clearBuffer();
  screen.setCursor(30, 10);
  if(dt.day<10)
  screen.print("0");
  screen.print(dt.day);
  screen.print("-");
  if(dt.month<10)
  screen.print("0");
  screen.print(dt.month);
  screen.print("-");
  screen.print(dt.year);
  screen.setCursor(45, 30);
  if(dt.hour<10)
  screen.print("0");
  screen.print(dt.hour);
  screen.print(":");
  if(dt.minute<10)
  screen.print("0");
  screen.print(dt.minute);
  screen.sendBuffer();
  delay(tim);
}
void set_time()
{
  dt = clock.getDateTime();
  if (digitalRead(UP) == LOW) {
    counter = counter + 1;
    delay(200);
  }
  if (counter == 0)
  {
    if (digitalRead(SET) == LOW)
    {
      month = month + 1;
      if (month > 12)
        month = 1;
      clock.setDateTime(year, month, day, hour, minute, 0);
      times(u8g2, dt, 10);
      delay(100);
    }
  }
  if (counter == 1)
  {
    if (digitalRead(SET) == LOW) {
      day = day + 1;
      if ((month==2)&&day>29)
        day = 1;
        else
        {
      if (((month==4)||(month==6)||(month==9)||(month==11))&&day>30)
        day = 1;
        else{
      if (((month==1)||(month==3)||(month==5)||(month==7)||(month==8)||(month==10)||(month==12))&&day>31)
        day = 1;
        }
        }
      clock.setDateTime(year, month, day, hour, minute, 0);
      times(u8g2, dt, 10);
      delay(100);
    }
  }
  if (counter == 2)
  {
    if (digitalRead(SET) == LOW) {
      year = year + 1;
      if (year > 2030)
        year = 2021;
      clock.setDateTime(year, month, day, hour, minute, 0);
      times(u8g2, dt, 10);
      delay(100);
    }
  }
  if (counter == 3)
  {
    if (digitalRead(SET) == LOW) {
      hour = hour + 1;
      if (hour > 24)
        hour = 1;
      clock.setDateTime(year, month, day, hour, minute, 0);
      times(u8g2, dt, 10);
      delay(100);
    }
  }
  if (counter == 4)
  {
    if (digitalRead(SET) == LOW) {
      minute = minute + 1;
      if (minute > 59)
        minute = 0;
      clock.setDateTime(year, month, day, hour, minute, 0);
      times(u8g2, dt, 10);
      delay(100);
    }
  }
  if (counter > 4)
    counter = 0;
}
void setup()
{
  pinMode(START, INPUT_PULLUP);
  pinMode(SET, INPUT_PULLUP);
  pinMode(UP, INPUT_PULLUP);
  Serial.begin(9600);
  clock.begin();
  clock.setDateTime(year, month, day, hour, minute, 0);
  u8g2.begin();
  dht.setup(DHTPIN);
  if (!bmp.begin()) {
    while (1) {}
  }
  u8g2.setFont(u8g2_font_t0_13_tf);
  i_am(u8g2);
}
void loop(void) {

  set_time();
  if (digitalRead(START) == LOW) {
    running = true;
  }
  if (running)
  {
    times2(u8g2, dt, 2000);
    meteo(u8g2, dht, bmp);
  }
}
