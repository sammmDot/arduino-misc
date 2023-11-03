#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
#include "HardwareSerial.h"

#define RX_PIN 10
#define TX_PIN 9
#define GPS_BAUD 9600

TinyGPSPlus gps;
SoftwareSerial ss(RX_PIN, TX_PIN);

void setup() {
  Serial.begin(9600); // MONITOR SERIAL
  ss.begin(GPS_BAUD);

  Serial.println(F(" -- INICIALIZANDO MODULO -- "));
  Serial.println();
  Serial.println(F("Sats   Latitude   Longitude   Alt    Date       Time"));
  Serial.println(F("       (deg)      (deg)       (m)"));
  Serial.println(F("-----------------------------------------------------"));
}

void loop() {
  printInt(gps.satellites.value(), gps.satellites.isValid(), 5);
  printFloat(gps.location.lat(), gps.location.isValid(), 11, 6);
  printFloat(gps.location.lng(), gps.location.isValid(), 12, 6);
  printFloat(gps.altitude.meters(), gps.altitude.isValid(), 7, 2);
  printDateTime(gps.date, gps.time);
  Serial.println();

  smartDelay(1000);

  if (millis() > 5000 && gps.charsProcessed() < 10)
    Serial.println(F("No se reciben datos desde el GPS. Revisa el cableado."));
}

static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}

static void printFloat(float val, bool valid, int len, int prec)
{
  if (!valid)
  {
    while (len-- > 1)
      Serial.print('*');
    Serial.print(' ');
  }
  else
  {
    Serial.print(val, prec);
    int vi = abs((int)val);
    int flen = prec + (val < 0.0 ? 2 : 1); // . and -
    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
    for (int i=flen; i<len; ++i)
      Serial.print(' ');
  }
  smartDelay(0);
}

static void printInt(unsigned long val, bool valid, int len)
{
  char sz[32] = "*****************";
  if (valid)
    sprintf(sz, "%ld", val);
  sz[len] = 0;
  for (int i=strlen(sz); i<len; ++i)
    sz[i] = ' ';
  if (len > 0) 
    sz[len-1] = ' ';
  Serial.print(sz);
  smartDelay(0);
}

static void printDateTime(TinyGPSDate &d, TinyGPSTime &t)
{
  if (!d.isValid())
  {
    Serial.print(F("********** "));
  }
  else
  {
    char sz[32];
    sprintf(sz, "%02d/%02d/%02d ", d.day(), d.month(), d.year());
    Serial.print(sz);
  }
  
  if (!t.isValid())
  {
    Serial.print(F("******** "));
  }
  else
  {
    char sz[32];
    sprintf(sz, "%02d:%02d:%02d ", t.hour() - 3, t.minute(), t.second());
    Serial.print(sz);
  }

  printInt(d.age(), d.isValid(), 5);
  smartDelay(0);
}