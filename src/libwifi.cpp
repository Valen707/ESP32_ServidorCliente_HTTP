#include <Arduino.h>
#include "libwifi.h"
#include <WiFi.h>



void conectarWifi(const char * ssid, const char * password){
  WiFi.begin(ssid, password);
  Serial.println("Estableciendo vinculo con el AP.");
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(1000);
  }
  Serial.println("\r\nConexion establecida");
  Serial.print("Numero IP asignado: ");
  Serial.println(WiFi.localIP()); //Imprime el numero IP
}

String getTipoCifrado(wifi_auth_mode_t tipoCifrado) {
 
  switch (tipoCifrado) {
    case (WIFI_AUTH_OPEN):
      return "Open";
    case (WIFI_AUTH_WEP):
      return "WEP";
    case (WIFI_AUTH_WPA_PSK):
      return "WPA_PSK";
    case (WIFI_AUTH_WPA2_PSK):
      return "WPA2_PSK";
    case (WIFI_AUTH_WPA_WPA2_PSK):
      return "WPA_WPA2_PSK";
    case (WIFI_AUTH_WPA2_ENTERPRISE):
      return "WPA2_ENTERPRISE";
  }
}
 
void scanNetworks() {
 
  int numberOfNetworks = WiFi.scanNetworks();
 
  Serial.print("Numero de redes encontradas: ");
  Serial.println(numberOfNetworks);
 
  for (int i = 0; i < numberOfNetworks; i++) {
 
    Serial.print("Nombre de red: ");
    Serial.println(WiFi.SSID(i));
 
    Serial.print("Fuerza de la señal: ");
    Serial.println(WiFi.RSSI(i));
 
    Serial.print("Direccion MAC: ");
    Serial.println(WiFi.BSSIDstr(i));
 
    Serial.print("Tipo de cifrado: ");
    String tipoCifradoDescription = getTipoCifrado(WiFi.encryptionType(i));
    Serial.println(tipoCifradoDescription);
    Serial.println("-----------------------");
 
  }
}