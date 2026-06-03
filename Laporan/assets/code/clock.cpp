/**
 * @author Yuke Brilliant Hestiavin 5024241016
 * Clock with RTC DS1307, TM1637, and Potensiometer
 */

#include <TM1637Display.h>
#include <Wire.h>

#include "RTClib.h"

RTC_DS1307 rtc;

// Pin I2C DS1307 ESP32
#define SDA_PIN 21
#define SCL_PIN 22

// Pin TM1637
#define TM_CLK 19
#define TM_DIO 18

// Pin potensio
#define POT_PIN 34

TM1637Display display(TM_CLK, TM_DIO);

void print2(int v) {
  if (v < 10) Serial.print('0');
  Serial.print(v);
}

void showDate(const char* txt, const DateTime& dt) {
  Serial.print(txt);
  Serial.print(' ');
  Serial.print(dt.year());
  Serial.print('/');
  print2(dt.month());
  Serial.print('/');
  print2(dt.day());
  Serial.print(' ');
  print2(dt.hour());
  Serial.print(':');
  print2(dt.minute());
  Serial.print(':');
  print2(dt.second());

  Serial.print(" = ");
  Serial.print(dt.unixtime());
  Serial.print("s / ");
  Serial.print(dt.unixtime() / 86400L);
  Serial.print("d since 1970s");

  Serial.println();
}

int readBrightness() {
  int raw = analogRead(POT_PIN);             // ESP32 ADC: 0 - 4095
  Serial.print("raw = ");
  Serial.println(raw);
  int brightness = map(raw, 0, 4095, 0, 7);  // TM1637: 0 - 7

  brightness = constrain(brightness, 0, 7);
  return brightness;
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Wire.begin(SDA_PIN, SCL_PIN);

  analogReadResolution(12);  // 0 - 4095

  if (!rtc.begin()) {
    Serial.println("RTC DS1307 tidak terdeteksi!");
    while (1) delay(1000);
  }

  if (!rtc.isrunning()) {
    Serial.println("RTC belum running, set waktu dari compile time...");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  // Aktifkan sekali saja kalau mau paksa set waktu,
  // lalu komen lagi setelah waktu RTC benar.
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  display.setBrightness(5);
  display.clear();

  Serial.println("RTC + TM1637 + Potensio siap.");
}

void loop() {
  DateTime now = rtc.now();

  int brightness = readBrightness();
  display.setBrightness(brightness);

  showDate("now", now);

  int hour = now.hour();
  int minute = now.minute();
  int second = now.second();

  int displayTime = hour * 100 + minute;

  // 0b01000000 = colon/titik dua
  uint8_t colon = (second % 2 == 0) ? 0b01000000 : 0;

  display.showNumberDecEx(displayTime, colon, true, 4, 0);

  Serial.print("brightness = ");
  Serial.println(brightness);

  delay(100);
}