#include "DHT.h"

DHT dht;

void setup()
{
  Serial.begin(9600);
  dht.setup(4);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  pinMode(12, INPUT);
  pinMode(13, INPUT);
}

void loop()
{
  // Ritmo Refresco;
  delay(1000);

  // DHT22 y AM2302
  float humedad = dht.getHumidity();
  float temperatura = dht.getTemperature();
 
  // MQ-3
  int mq3_adc = analogRead(A12);
  float mq3_voltaje = mq3_adc * (5.0 / 1023.0);
  float mq3_resistencia = 1000*((5-mq3_voltaje)/mq3_voltaje); 
  double alcohol = 0.4091*pow(mq3_resistencia/5463, -1.497);
  bool mq3_umbral = digitalRead(12);

  // JSON
  String jsonSerial = "{";

  if (isnan(alcohol)) {
  
    jsonSerial += "\"alcohol\": {";
    jsonSerial += "\"valido\": false,";
    jsonSerial += "\"error\": \"Valor númerico no valido\"";
    jsonSerial += "},";
  
  } else {

    jsonSerial += "\"alcohol\": {";
    jsonSerial += "\"valido\": true,";
    jsonSerial += "\"valor\":"; 
    jsonSerial += alcohol;
    jsonSerial += ",\"unidad\": \"mg/L\",";
    jsonSerial += "\"descripcion\": \"Alcohol (Benceno, Propano, Etanol, Metanol)\",";      
    jsonSerial += "\"formulaQuimica\": [\"C6H6\", \"C3H8\", \"C2H6O\", \"CH3OH\"],";    
    jsonSerial += "\"umbralAlcanzado\": ";
    jsonSerial += mq3_umbral;
    jsonSerial += ",\"voltaje\": ";
    jsonSerial += mq3_voltaje;
    jsonSerial += ",\"resistencia\":";
    jsonSerial += mq3_resistencia;
    jsonSerial += ",\"valorAnalogico\":";
    jsonSerial += mq3_adc;
    jsonSerial += ",\"sensor\": \"MQ-3\"";
    jsonSerial += "},";     

  }
  
  // Temperatura y Humedad (DHT22, AM2302)
  if (isnan(temperatura) || isnan(humedad)) {

    jsonSerial += "\"humedad\": {";
    jsonSerial += "\"valido\": false,";
    jsonSerial += "\"error\": \"Valor númerico no valido\"";
    jsonSerial += "},";
    jsonSerial += "\"temperatura\": {";
    jsonSerial += "\"valido\": false,";
    jsonSerial += "\"error\": \"Valor númerico no valido\"";   
    jsonSerial += "}";

  } else {

    jsonSerial += "\"humedad\": {";
    jsonSerial += "\"valido\": true,";
    jsonSerial += "\"valor\":";
    jsonSerial += humedad;
    jsonSerial += ",\"sensor\": \"AM2302\",";
    jsonSerial += "\"unidad\": \"%\"";  
    jsonSerial += "},";
    
    jsonSerial += "\"temperatura\": {";
    jsonSerial += "\"valido\": true,";
    jsonSerial += "\"valor\":";
    jsonSerial += temperatura;
    jsonSerial += ",\"sensor\": \"DHT22\",";
    jsonSerial += "\"unidad\": \"°C\"";    
    jsonSerial += "}";    
      
  }

  jsonSerial += "}";

  // Impresión
  Serial.println(jsonSerial);
}