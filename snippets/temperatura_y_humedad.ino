#include "DHT.h"

DHT dht;

void setup()
{
  Serial.begin(9600);
  Serial.println("Empecemos...");
  dht.setup(4);
}

void loop()
{
  delay(dht.getMinimumSamplingPeriod());

  float humedad = dht.getHumidity();
  float temperatura = dht.getTemperature();
 

  if (isnan(temperatura) || isnan(humedad)) {
    Serial.println("Error en la lectura de datos.");
  } else {
    Serial.print("Humedad: ");
    Serial.print(humedad);
    Serial.print("%\t");
    Serial.print("Temperatura: ");
    Serial.print(temperatura);
    Serial.println("°C");
  }
}