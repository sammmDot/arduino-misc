#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
#include <HardwareSerial.h>
#include <RTClib.h>
#include "GPS.h"
#include "RTC.h"

void setup() {
  initGPS();
  delay(10000);
  initRTC();
}

void loop() {
  configGPS();
  configRTC();
}
