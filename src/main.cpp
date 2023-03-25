#include <Arduino.h>
#include "libwifi.h"
#include <WiFi.h>
 
const char * ssid = "viper";
const char * password = "*******";
const int puerto = 80;
WiFiServer servidor(puerto);  // Construimos un objeto de tipo servidor TCP

void setup() {
  pinMode(2, OUTPUT);  //Coloco el pin 2 como salida
  Serial.begin(115200);
  Serial.println("Inicializando dispositivo");
  conectarWifi(ssid, password);
  servidor.begin();  //Inicializamos el servidor TCP
}

void loop() {

  WiFiClient cliente = servidor.available(); //Devolvemos un cliente TCP por wifi conectado a servidor

  if(cliente){  //PASO 1: Si existe un cliente conectado?
    String mensaje="";
    Serial.println("Se conecto un cliente");
    while(cliente.connected()){  
       if(cliente.available()){ 
        char letra = cliente.read();  
        Serial.print(letra);
        if(letra == '\n'){  
          if(mensaje.length()==0){            //Devolvemos una respuesta (response) HTTP
              cliente.println("HTTP/1.1 200 OK");
              cliente.println("Content-type:text/html");
              cliente.println();  //Enviamos una linea vacia indica al protocolo HTTP que la cabecera finalizo  

              cliente.println("Haga clic <a href=\"/H\">aqui</a> para encender el LED <br>");
              cliente.println("Haga clic  <a href=\"/L\">aqui</a> para apagar el LED");
              cliente.println();  //Finalizamos el envio del cuerpo (body) de la pagina
              break;
          } else {
            mensaje="";
          }
        } else if (letra != '\r'){
             mensaje+=letra;  // Concatenamos cada caracter que esta llegando en mensaje
        }

        if(mensaje.endsWith("GET /H")){
           digitalWrite(2, HIGH);
        }
        else if(mensaje.endsWith("GET /L")){   
          digitalWrite(2, LOW);
        }
       }
    }
    Serial.println("Cerrando conexion");
    cliente.stop();
  }
}
