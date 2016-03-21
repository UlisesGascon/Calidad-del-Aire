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

  // JSON
  String jsonSerial = "{\"temperatura\":";
  jsonSerial += temperatura;
  jsonSerial +=",\"humedad\":";
  jsonSerial += humedad;
  jsonSerial +="}";

  // Impresión
  Serial.println(jsonSerial);

}