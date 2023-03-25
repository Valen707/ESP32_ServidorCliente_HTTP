#include <WiFi.h>
void conectarWifi(const char * ssid, const char * password);
void scanNetworks();
String getTipoCifrado(wifi_auth_mode_t tipoCifrado);
