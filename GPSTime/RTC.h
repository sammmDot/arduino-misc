RTC_DS3231 rtc;

void initRTC()
{
  
  Serial.println("Inicializando modulo RTC");
  if (!rtc.begin()) {
    Serial.println("No se pudo encontrar el módulo RTC DS3231. Verifica la conexión.");
    while (true);
  }
}

void configRTC()
{
  TinyGPSDate d = gps.date;
  TinyGPSTime t = gps.time;

  // rtc.adjust(DateTime(d.year(), d.month(), d.day(), t.hour() - 3 , t.minute(), t.second()));
  rtc.adjust(DateTime(anoConfigRTC, mesConfigRTC, diaConfigRTC, horaConfigRTC, minConfigRTC, segConfigRTC));  //AÑO, MES, DIA, HORA, MINUTO, SEGUNDO

  DateTime now = rtc.now(); 
  Serial.print(F("RTC Date/Time: "));
  Serial.print(now.year());
  Serial.print(F("/"));
  if (now.month() < 10) Serial.print(F("0"));
  Serial.print(now.month());
  Serial.print(F("/"));
  if (now.day() < 10) Serial.print(F("0"));
  Serial.print(now.day());

  Serial.print(F(" "));

  if (now.hour() < 10) Serial.print(F("0"));
  Serial.print(now.hour());
  Serial.print(F(":"));
  if (now.minute() < 10) Serial.print(F("0"));
  Serial.print(now.minute());
  Serial.print(F(":"));
  if (now.second() < 10) Serial.print(F("0"));
  Serial.print(now.second());

  Serial.println();
}
