#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
#include <HardwareSerial.h>
#include <RTClib.h>
#include <NTPClient.h>
#include "GetTime.h"
#include "RTC.h"

void setup() {
  Serial.begin(9600);
  // initGPS();
  OnGPRS();
  configGPRS();
}

void loop() {
 switch (TypeTime) {
    case 0:
      configGPS();
    
    case 1:
      if (ModeGPRS == 0){
        Serial.println(" -- EN CONSTRUCCIÓN --");
      }
      else if (ModeGPRS == 1){
        GPRSDateTime();
    }
  }
}
