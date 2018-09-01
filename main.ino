#include "ESP8266.h"
#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); /* RX:D10, TX:D11 */
ESP8266 wifi(mySerial);
const String SSID = "";
const String PASSWORD = "";

void setup(){
  pinMode(9,OUTPUT);
  Serial.begin(9600);
  Serial.print("setup begin\r\n");
  while(!wifi.setOprToStationSoftAP()){
    wifi.setOprToStationSoftAP();
    Serial.println("to station + softap err");
    delay(250);
  }
  Serial.println("setOperation Ok");
  while(!wifi.joinAP(SSID, PASSWORD)) {
    wifi.joinAP(SSID, PASSWORD);
    Serial.println("Erro ao dar join");
    delay(250);
  }
  Serial.print("Join AP success\r\n");
  Serial.print("IP:");
  Serial.println( wifi.getLocalIP().c_str());
  while(!wifi.enableMUX()){
    Serial.println("Erro ao iniciar MUX");
    wifi.enableMUX();
  }
  Serial.println("MUX iniciado");
  while(!wifi.startTCPServer(4444)){
    Serial.println("Erro ao criar TCPServer");
    delay(500);
    wifi.startTCPServer(4444);
  }
  Serial.println("TCPServer Criado");
}

int parseData(String _data){
  if (_data.equals("Turn ON")){
    digitalWrite(9,HIGH);
  }
  if(_data.equals("Turn OFF")){
    digitalWrite(9,LOW);
  }
}
void loop(){
  String string;
  uint8_t buffer[128] = {0};
  uint32_t len = wifi.recv(buffer, sizeof(buffer), 500);
  if (len > 0) {
        Serial.print("Received:[");
        for(uint32_t i = 0; i < len; i++) {
          string += (char)buffer[i];
            //Serial.print((char)buffer[i]);
        }
        Serial.print(string);
        parseData(string);
        Serial.print("]\r\n");
  }
}
