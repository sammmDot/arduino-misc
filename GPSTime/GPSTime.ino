#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
#include <HardwareSerial.h>
#include "GPS.h"

void setup() {
  initGPS();
}

void loop() {
  configGPS();
}
