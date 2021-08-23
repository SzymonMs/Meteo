#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Adafruit_BMP085.h>

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0);  
Adafruit_BMP085 bmp;
 
void setup()
{
  u8g2.begin();
  if (!bmp.begin())
  {
    while (1) {}
  }
}
 
void loop(void){
float temp =bmp.readTemperature();
float pres=bmp.readPressure()/100;
u8g2.clearBuffer(); // clear the internal memory
u8g2.setFont(u8g2_font_t0_13b_mr); // set fonts
u8g2.setCursor(10,10); // set cursor position
u8g2.print(temp); // write something to the internal memory
u8g2.print(" *C"); // write something to the internal memory
u8g2.setCursor(10,30); // set cursor position
u8g2.print(pres); // write something to the internal memory
u8g2.print(" hPa"); // write something to the internal memory
u8g2.sendBuffer(); // transfer internal memory to the display
delay(2000);
}
