bool TAGerrorINIT = 0;
bool TAGerrorSEND = 0;
bool TAGenvio = 0;

int contadorTry = 0;
int gprsStatus;

unsigned long horaConfigRTC = 0;
unsigned long minConfigRTC = 0;
unsigned long segConfigRTC = 0;
unsigned long anoConfigRTC = 0;
unsigned long mesConfigRTC = 0;
unsigned long diaConfigRTC = 0;

void onGPRS()
{
  Serial.begin(9600);
  Serial1.begin(9600);
}

void ClearSerialData(){
  Serial1.flush();
  while(Serial1.available() > 0){
    Serial1.read();
  }
}

void ShowSerialData(){
  Serial1.flush();
  while(Serial1.available() != 0){
    Serial.write(Serial1.read());
  }
  delay(5000);
}

void SendCMDAT(String AT, char* resp_correcta, unsigned int tiempo, unsigned int tipo){
  int x = 0;
  int entrada = 0;
  char resp[120];
  unsigned long banderaTiempo;
  int cuentaLoop = 0;
  bool TAGCGATT = 0;
  char* resp_correcta1;
  char* resp_correcta2;
  char* resp_correcta3;
  char* resp_correcta4;
  char* resp_correcta5;
  char* resp_correcta6;
  char* resp_correcta7;
  char* resp_correcta8;
  char* resp_correcta9;
  char* resp_correcta10;
  char* resp_noconecto;
  bool contadorEnvio = 0;
  
  switch(tipo){
    
    case 0: //AT
      while(entrada == 0){
        memset(resp,'\0', 120);
        ClearSerialData();
        Serial1.println(AT);
        Serial1.flush();
        
        x = 0;
        banderaTiempo = millis();
        do{
          if(Serial1.available() != 0){
            resp[x] = Serial1.read();
            x++;

            if(strstr(resp, resp_correcta) != NULL){
              entrada = 1;
            }
          }
        } while((entrada == 0) && ((millis() - banderaTiempo) < tiempo));

        Serial.println(resp);
        cuentaLoop++;
        if(cuentaLoop == 5){
          TAGerrorINIT = 1;
          return;
        }

        if(entrada == 1){
          Serial.println(F("Respuesta esperada"));
          TAGerrorINIT = 0;
        } else{
          Serial.println(F("Respuesta NO esperada"));
        }
      }
      break;

    case 1: //ATSEND
      while(entrada == 0){
        memset(resp,'\0', 120);
        ClearSerialData();
        Serial1.println(AT);
        Serial1.flush();
        x = 0;
        banderaTiempo = millis();

        do{
          if(Serial1.available() != 0){
            resp[x] = Serial1.read();
            x++;

            if(strstr(resp, resp_correcta) != NULL){
              entrada = 1;
            }
          }
        } while((entrada == 0) && ((millis() - banderaTiempo) < tiempo));

        Serial.println(resp);

        if(entrada == 1){
          Serial.println(F("Respuesta esperada"));
          TAGerrorSEND = 0;
        } else{
          Serial.println(F("Respuesta NO esperada"));
          TAGerrorSEND = 1;
          entrada = 2;
          delay(500);
        }
      }
      break;

    case 2: //ATCGATT
      while(entrada == 0){
        if(TAGCGATT == 0){
          memset(resp,'\0', 120);
          ClearSerialData();
          Serial1.println(AT);
          Serial1.flush();
          x = 0;
          banderaTiempo = millis();

          do{
            if(Serial1.available() != 0){
              resp[x] = Serial1.read();
              x++;

              if(strstr(resp, resp_correcta) != NULL){
                entrada = 1;
              }
            }
          } while((entrada == 0) && ((millis() - banderaTiempo) < tiempo));

          Serial.println(resp);
          cuentaLoop++;

          if(cuentaLoop == 3){
            TAGerrorINIT = 1;
            return;
          }

          if(entrada == 1){
            Serial.println(F("Respuesta esperada"));
            TAGerrorINIT = 0;
          } else{
            Serial.println(F("Respuesta NO esperada"));
            TAGCGATT = 1;
            delay(1000);
          }
//---------------------------------------------------------------------------//
        } else if(TAGCGATT == 1){
          int subx = 0;
          bool subentrada = 0;
          char subresp[120];
          unsigned long subbanderaTiempo;
          int subcuentaLoop = 0;
          char* subresp_correcta = "OK";
          String AT_CGATT = "AT+CGATT=1";
          unsigned int subtiempo = 14000;

          while(subentrada == 0){
            memset(subresp,'\0', 120);
            ClearSerialData();
            Serial1.println(AT_CGATT);
            Serial1.flush();
            subx = 0;
            subbanderaTiempo = millis();

            do{
              if(Serial1.available() != 0){
                subresp[subx] = Serial1.read();
                subx++;

                if(strstr(subresp, subresp_correcta) != NULL){
                  subentrada = 1;
                }
              }
            } while((subentrada == 0) && ((millis() - subbanderaTiempo) < subtiempo));

            Serial.println(subresp);
            subcuentaLoop++;
            if(subcuentaLoop == 3){
              TAGerrorINIT = 1;
              return;
            }

            if(subentrada == 1){
              Serial.println(F("Respuesta esperada"));
              TAGerrorINIT = 0;
              TAGCGATT = 0;
            } else{
              Serial.println(F("Respuesta NO esperada"));
              delay(1000);  //cambio de 10 seg a 5
            }
          }
        }
//---------------------------------------------------------------------------//
      }
      break;

    case 3: //ATCGATT2
      resp_correcta2 = "+SAPBR 1: DEACT";

      while(entrada == 0){
        memset(resp,'\0', 120);
        ClearSerialData();
        Serial1.println(AT);
        Serial1.flush();
        x = 0;
        banderaTiempo = millis();

        do{
          if(Serial1.available() != 0){
            resp[x] = Serial1.read();
            x++;

            if(strstr(resp, resp_correcta) != NULL){
              entrada = 1;
            } else if((strstr(resp, resp_correcta2) != NULL)){
              entrada = 1;
            }
          }
        } while((entrada == 0) && ((millis() - banderaTiempo) < tiempo));

        Serial.println(resp);
        cuentaLoop++;

        if(cuentaLoop == 4){
          //TAGerrorINIT = 1;
          return;
        }

        if(entrada == 1){
          Serial.println(F("Respuesta esperada"));
        } else{
          Serial.println(F("Respuesta NO esperada"));
          delay(1000);
        }
      }
      break;

    case 4: //ATCREG
      resp_correcta2 = "+CREG: 0,1";
      resp_correcta3 = "+CREG: 0,2";
      resp_correcta4 = "+CREG: 0,3";
      resp_correcta5 = "+CREG: 0,4";

      while(entrada == 0){
        memset(resp,'\0', 120);
        ClearSerialData();
        Serial1.println(AT);
        Serial1.flush();
        x = 0;
        banderaTiempo = millis();

        do{
          if(Serial1.available() != 0){
            resp[x] = Serial1.read();
            x++;

            if (strstr(resp, resp_correcta) != NULL){
              entrada = 1;
            } else if(strstr(resp, resp_correcta2) != NULL){
              entrada = 1;
            } else if(strstr(resp, resp_correcta3) != NULL){
              entrada = 1;
            } else if(strstr(resp, resp_correcta4) != NULL){
              entrada = 1;
            } else if(strstr(resp, resp_correcta5) != NULL){
              entrada = 1;
            }
          }
        } while((entrada == 0) && ((millis() - banderaTiempo) < tiempo));

        Serial.println(resp);
        cuentaLoop++;

        if(cuentaLoop == 5){
          TAGerrorINIT = 1;
          return;
        }

        if(entrada == 1){
          Serial.println(F("Respuesta esperada"));
          TAGerrorINIT = 0;
        } else{
          Serial.println(F("Respuesta NO esperada"));
          delay(2000);
        }
      }
      break;

    case 5: //ATCIPS
      while(entrada == 0){
        memset(resp,'\0', 120);
        ClearSerialData();
        Serial1.println(AT);
        Serial1.flush();
        x = 0;
        banderaTiempo = millis();

        do{
          if(Serial1.available() != 0){
            resp[x] = Serial1.read();
            x++;

            if((strstr(resp, resp_correcta) != NULL)){
              entrada = 1;
            }
          }
        } while((entrada == 0) && ((millis() - banderaTiempo) < tiempo));

        Serial.println(resp);
        cuentaLoop++;

        if(cuentaLoop == 4){
          return;
        }

        if(entrada == 1){
          Serial.println(F("Respuesta esperada"));
        } else{
          Serial.println(F("Respuesta NO esperada"));
          return;
          delay(2000);
        }
      }
      break;

    case 6: //ATERROR
      resp_correcta2 = "ERROR";

      while(entrada == 0){
        memset(resp,'\0', 120);
        ClearSerialData();
        Serial1.println(AT);
        Serial1.flush();
        x = 0;
        banderaTiempo = millis();

        do{
          if(Serial1.available() != 0){
            resp[x] = Serial1.read();
            x++;

            if(strstr(resp, resp_correcta) != NULL){
              entrada = 1;
            } else if(strstr(resp, resp_correcta2) != NULL){
              entrada = 1;
            }
          }
        } while((entrada == 0) && ((millis() - banderaTiempo) < tiempo));

        Serial.println(resp);
        cuentaLoop++;
        if(cuentaLoop == 4){
          TAGerrorINIT = 1;
          return;
        }

        if(entrada == 1){
          Serial.println(F("Respuesta esperada"));
          TAGerrorINIT = 0;
        } else{
          Serial.println(F("Respuesta NO esperada"));
          delay(2000);
        }
      }
      break;

    case 7: //ATTCP
      resp_correcta2 = "ALREADY CONNECT";
      resp_correcta3 = "OK";
      resp_correcta4 = "STATE: TCP CLOSED";
      resp_correcta5 = "ERROR";
      resp_noconecto = "CONNECT FAIL";

      while(entrada == 0){
        memset(resp,'\0', 120);
        ClearSerialData();
        if(contadorEnvio == 0){
          Serial1.println(AT);
          Serial1.flush();
          contadorEnvio = 1;
        }
        x = 0;
        banderaTiempo = millis();
        
        do{
          if(Serial1.available() != 0){
            resp[x] = Serial1.read();
            x++;

            if((strstr(resp, resp_correcta) != NULL)){
              entrada = 1;
              TAGerrorSEND = 0;
            } else if((strstr(resp, resp_correcta2) != NULL)){
              entrada = 1;
              TAGerrorSEND = 0;
            } else if((strstr(resp, resp_correcta3) != NULL) && x < 4){
              contadorEnvio = 1;
              //x = 0;
              //Serial.println(F("OK recibido"));
            } else if((strstr(resp, resp_noconecto) != NULL)){
              entrada = 2;
              TAGerrorSEND = 1;
            } else if((strstr(resp, resp_correcta4) != NULL)){
              entrada = 2;
              TAGerrorSEND = 1;
            } else if((strstr(resp, resp_correcta5) != NULL)){
              entrada = 2;
              TAGerrorSEND = 1;
            }
          }
        } while((entrada == 0) && ((millis() - banderaTiempo) < tiempo));

        Serial.println(resp);
        cuentaLoop++;
        if(cuentaLoop == 5){
          TAGerrorSEND = 1;
          entrada = 3;
          return;
        }

        if(entrada == 1){
          Serial.println(F("Respuesta esperada"));
          TAGerrorSEND = 0;
        } else if(entrada == 2){
          Serial.println(F("Respuesta sin conexión"));
          TAGerrorSEND = 1;
          delay(500);
        } else if(entrada == 0){
          Serial.println(F("Respuesta NO esperada, reintentando"));
          delay(500);
        }
      }
      break;

    case 8: //ATRESET
      while(entrada == 0){
        memset(resp,'\0', 120);
        delay(1000);

        ClearSerialData();
        Serial1.println(AT);
        Serial1.flush();
        x = 0;
        banderaTiempo = millis();

        do{
          if(Serial1.available() != 0){
            resp[x] = Serial1.read();
            x++;

            if((strstr(resp, resp_correcta) != NULL)){
              entrada = 1;
            }
          }
        } while((entrada == 0) && ((millis() - banderaTiempo) < tiempo));

        Serial.println(resp);

        if(entrada == 1){
          Serial.println(F("Respuesta esperada"));
          TAGerrorINIT = 0;
        } else{
          Serial.println(F("Respuesta NO esperada"));
          return;
        }
      }
      break;

    case 9: //ATSTATUS
      resp_correcta1 = "STATE: IP INITIAL";
      resp_correcta2 = "STATE: IP START";
      resp_correcta3 = "STATE: IP CONFIG";
      resp_correcta4 = "STATE: IP GPRSACT";
      resp_correcta5 = "STATE: IP STATUS";
      resp_correcta6 = "STATE: TCP CONNECTING";
      resp_correcta7 = "STATE: CONNECT OK";
      resp_correcta8 = "STATE: TCP CLOSING";
      resp_correcta9 = "STATE: TCP CLOSED";
      resp_correcta10 = "STATE: PDP DEACT";

      while(entrada == 0){
        memset(resp,'\0', 120);
        delay(1000);
        
        ClearSerialData();
        Serial1.println(AT);
        Serial1.flush();
        x = 0;
        banderaTiempo = millis();

        do{
          if(Serial1.available() != 0){
            resp[x] = Serial1.read();
            x++;

            if (strstr(resp, resp_correcta1) != NULL){
              entrada = 1;
              gprsStatus = 1;
            } else if(strstr(resp, resp_correcta2) != NULL){
              entrada = 1;
              gprsStatus = 2;
            } else if(strstr(resp, resp_correcta3) != NULL){
              entrada = 1;
              gprsStatus = 3;
            } else if(strstr(resp, resp_correcta4) != NULL){
              entrada = 1;
              gprsStatus = 4;
            } else if(strstr(resp, resp_correcta5) != NULL){
              entrada = 1;
              gprsStatus = 5;
            } else if(strstr(resp, resp_correcta6) != NULL){
              entrada = 1;
              gprsStatus = 6;
            } else if(strstr(resp, resp_correcta7) != NULL){
              entrada = 1;
              gprsStatus = 7;
            } else if(strstr(resp, resp_correcta8) != NULL){
              entrada = 1;
              gprsStatus = 8;
            } else if(strstr(resp, resp_correcta9) != NULL){
              entrada = 1;
              gprsStatus = 9;
            } else if(strstr(resp, resp_correcta10) != NULL){
              entrada = 1;
              gprsStatus = 10;
            }
          }
        } while((entrada == 0) && ((millis() - banderaTiempo) < tiempo));

        //Serial.println(resp);
        cuentaLoop++;

        if(cuentaLoop == 5){
          return;
        }

        if(entrada == 1){
          //Serial.println(F("Respuesta esperada"));
        } else{
          //Serial.println(F("Respuesta NO esperada"));
        }
      }
      break;

    default:
      Serial.println(F("Caso distinto SEND AT\n"));
      break;
  }
}

void SIMRTC() {
  while (true) {
    Serial.println(F("Sincronizando RTC"));

    Serial1.println("AT+CCLK?");
    ShowSerialData();
    Serial1.flush();

    if (Serial1.available()) {
      String response = Serial1.readString();
      // Serial.println("Respuesta recibida: " + response);

      int index = response.indexOf('"');
      String parte1 = response.substring(0, index);
      String parte2 = response.substring(index + 1);
      index = parte2.indexOf(',');
      String parte3 = parte2.substring(0, index);
      int index2 = parte2.indexOf('-');
      String parte4 = parte2.substring(index + 1, index2);
      int index3 = parte2.indexOf('"');
      String parte5 = parte2.substring(index2 + 1, index3);

      //Serial.println("Fecha: " + parte3);
      index = parte3.indexOf('/');
      index2 = parte3.indexOf('/', index + 1);
      String anoSt = parte3.substring(0, index);
      String mesSt = parte3.substring(index + 1, index2);
      String diaSt = parte3.substring(index2 + 1);
      anoConfigRTC = anoSt.toInt();
      mesConfigRTC = mesSt.toInt();
      diaConfigRTC = diaSt.toInt();

      //Serial.println("Hora: " + parte4);
      index = parte4.indexOf(':');
      index2 = parte4.indexOf(':', index + 1);
      String horaSt = parte4.substring(0, index);
      String minSt = parte4.substring(index + 1, index2);
      String segSt = parte4.substring(index2 + 1);

      horaConfigRTC = horaSt.toInt();
      minConfigRTC = minSt.toInt();
      segConfigRTC = segSt.toInt();
      if (segConfigRTC < 53) {
        segConfigRTC = segConfigRTC + 1;
      } else if (segConfigRTC == 53) {
        segConfigRTC = 0;
      } else if (segConfigRTC > 53) {
        segConfigRTC = segConfigRTC + 1;
        segConfigRTC = segConfigRTC - 60;
        minConfigRTC++;
      }

      int GMT = parte5.toInt();
      // Serial.println("GMT: " + String(GMT));
      GMT = GMT / 4;
      horaConfigRTC = horaConfigRTC - GMT;
    }
  }
}

void configGPRS(){
  //Serial1.listen();
  delay(5000);
  Serial.println(F("Configurando módulo SIM800L"));
  delay(15000);
  // configGPRS();
  SendCMDAT("AT","OK",6000,0);
  SendCMDAT("AT+CBAND=ALL_BAND","OK",6000,0);
  //SendCMDAT("AT&W","OK",2000,0);
  SendCMDAT("AT+CIURC=0","OK",3000,0);
  SendCMDAT("AT+CPIN?","+CPIN: READY",2000,0);
  if(TAGerrorINIT == 1){
    return;
  }
  SendCMDAT("AT+CREG?","+CREG: 0,5",2000,4);
  
  SendCMDAT("AT+CSQ","OK",2000,0);
  SendCMDAT("AT+CIPSHUT","SHUT OK",2000,0);
  if(TAGerrorINIT == 1){
    return;
    
  }
  SendCMDAT("AT+CGATT?","+CGATT: 1",2000,2);
  if(TAGerrorINIT == 1){
    return;
  }
  SendCMDAT("AT+CIPSTATUS","STATE: IP INITIAL",3000,0);
  SendCMDAT("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"","OK",3000,0);
  
  SendCMDAT("AT+SAPBR=3,1,\"APN\",\"gigsky-02\"","OK",2000,0);
  SendCMDAT("AT+CSTT=\"gigsky-02\",\"\",\"\"","OK",3000,0);
  SendCMDAT("AT+CGDCONT=1,\"IP\",\"gigsky-02\"","OK",2000,0);

  SendCMDAT("AT+CGACT=1,1","OK",150000,0);
  SendCMDAT("AT+SAPBR=1,1","OK",6000,6);
  if(TAGerrorINIT == 1){
    return;
  }
  SendCMDAT("AT+CREG?","OK",2000,0);
//  SendCMDAT("AT+CGATT=1","OK",2000,0);
//  if(TAGerrorINIT == 1){
//    return;
//  }
  //SendCMDAT("AT+CIPMUX=0","OK",3000,6);
  SendCMDAT("AT+CIPQSEND=1","OK",2000,0);
  //SendCMDAT("AT+CIPRXGET=0","OK",2000,0);
  //SendCMDAT("AT+CIPRXGET=1","OK",2000,0);
  SendCMDAT("AT+CIICR","OK",30000,6);
  if(TAGerrorINIT == 1){
    return;
  }
  ClearSerialData();
  Serial1.println("AT+CIFSR");
  delay(3000);
  ShowSerialData();
  SendCMDAT("AT+CDNSCFG=\"8.8.8.8\",\"8.8.4.4\"","OK",2000,0);
  Serial.println(F("Configuración y conexión SIM800L lista!\n"));
  TAGenvio = 0;
  TAGerrorINIT = 0;
  
  Serial1.flush();
}