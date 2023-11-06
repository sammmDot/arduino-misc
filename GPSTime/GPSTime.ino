#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
#include <HardwareSerial.h>
#include <RTClib.h>
#include "GPRS.h"
#include "GPS.h"
#include "RTC.h"

void setup() {
  // initGPS();
  // delay(10000);
  Serial.begin(9600);
  initRTC();
  delay(10000);
  onGPRS();
  configGPRS();
}

void loop() {
  // configGPS();
  SIMRTC();
  configRTC();
}
