#include <SoftwareSerial.h>
#include "ds18b20.h"
#include "hcsr04.h"
#include "dht11.h"  // Incluir el archivo del sensor DHT11

char resultdis[20];
char resulttemp[20];
char resulthum[20];  // Almacenar el valor de la humedad

int rele = 8;

SoftwareSerial mySerial(0, 1); // RX, TX

void setup() {
  mySerial.begin(115200);
  pinMode(8, OUTPUT);
  delay(5000);  // Esperar 5 segundos
}

void loop() {
  // Leer y convertir los datos de los sensores a cadenas de texto (char)
  String DISTANCIA = String(distancia_cm(3, 4)); // Sensor de distancia
  DISTANCIA.toCharArray(resultdis, 20);

  String TEMPERATURA = String(ds1820(2)); // Sensor de temperatura
  TEMPERATURA.toCharArray(resulttemp, 20);

  float h = leerHumedad();  // Llamar la función para leer la humedad
  if (h != -1) {  // Verificar que la lectura de humedad sea válida
    String HUMEDAD = String(h);
    HUMEDAD.toCharArray(resulthum, 20);
  } else {
    String HUMEDAD = "Error";
    HUMEDAD.toCharArray(resulthum, 20);
  }

  // Condicionales de transmisión de datos UART
  if (mySerial.available() > 0) {
    byte lectura = mySerial.read();
    delay(5);

    if (lectura == '1') {
      mySerial.write(resulthum);  // Enviar la humedad al recibir '1'
    }
    if (lectura == '2') {
      mySerial.write(resultdis);  // Enviar la distancia al recibir '2'
    }
    if (lectura == '3') {
      mySerial.write(resulttemp);  // Enviar la temperatura al recibir '3'
    }
    // Control de la bomba (encender/apagar)
    if (lectura == '5') {
      digitalWrite(rele, HIGH); 
      mySerial.write('1');
    }
    if (lectura == '6') {
      digitalWrite(rele, LOW);
      mySerial.write('1');
    }
  }
}