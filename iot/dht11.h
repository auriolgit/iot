#include <DHT.h>

#define DHTPIN 5      // Pin al que está conectado el DHT11
#define DHTTYPE DHT11 // Definir el tipo de sensor como DHT11

DHT dht(DHTPIN, DHTTYPE);  // Crear el objeto DHT

float leerHumedad() {
  dht.begin(); // Inicializar el sensor
  float h = dht.readHumidity(); // Leer la humedad
  delay(50);
  
  // Verificar si el sensor ha fallado
  if (isnan(h)) {
    return -1; // Devuelve -1 si hay un error en la lectura
  } else {
    return h;
  }
}
