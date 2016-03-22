#include "DHT.h"

DHT dht;

void setup()
{
  Serial.begin(9600);
  dht.setup(4);
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
 
  // MQ-2
  int mq2_adc = analogRead(A13);
  float mq2_voltaje = mq2_adc * (5.0 / 1023.0);
  float mq2_resistencia = 1000*((5-mq2_voltaje)/mq2_voltaje);
  // PENDIENTE DE AJUSTE 
  double glp = 0.4091*pow(mq2_resistencia/5463, -1.497);
  bool mq2_umbral = digitalRead(13); 

  // MQ-3
  int mq3_adc = analogRead(A12);
  float mq3_voltaje = mq3_adc * (5.0 / 1023.0);
  float mq3_resistencia = 1000*((5-mq3_voltaje)/mq3_voltaje); 
  double alcohol = 0.4091*pow(mq3_resistencia/5463, -1.497);
  String mq3_umbral = "false";

  if(digitalRead(12) == 0){
    mq3_umbral = "true";
  }

  // MQ-4
  int mq4_adc = analogRead(A11);
  float mq4_voltaje = mq4_adc * (5.0 / 1023.0);
  float mq4_resistencia = 1000*((5-mq4_voltaje)/mq4_voltaje);
  // PENDIENTE DE AJUSTE 
  double metano = 0.4091*pow(mq4_resistencia/5463, -1.497);
  String mq4_umbral = "false";

  if(digitalRead(11) == 0){
    mq4_umbral = "true";
  }

  // MQ-6
  int mq6_adc = analogRead(A9);
  float mq6_voltaje = mq6_adc * (5.0 / 1023.0);
  float mq6_resistencia = 1000*((5-mq6_voltaje)/mq6_voltaje);
  // PENDIENTE DE AJUSTE
  double propano = 0.4091*pow(mq6_resistencia/5463, -1.497);
  String mq6_umbral = "false";

  if(digitalRead(9) == 0){
    mq6_umbral = "true";
  }

  // MQ-7
  int mq7_adc = analogRead(A8);
  float mq7_voltaje = mq7_adc * (5.0 / 1023.0);
  float mq7_resistencia = 1000*((5-mq7_voltaje)/mq7_voltaje);
  // PENDIENTE DE AJUSTE
  double monoxidoDeCarbono = 0.4091*pow(mq7_resistencia/5463, -1.497);
  String mq7_umbral = "false";

  if(digitalRead(8) == 0){
    mq7_umbral = "true";
  }

  // MQ-8
  int mq8_adc = analogRead(A7);
  float mq8_voltaje = mq8_adc * (5.0 / 1023.0);
  float mq8_resistencia = 1000*((5-mq8_voltaje)/mq8_voltaje);
  // PENDIENTE DE AJUSTE
  double hidrogeno = 0.4091*pow(mq8_resistencia/5463, -1.497);
  String mq8_umbral = "false";

  if(digitalRead(7) == 0){
    mq8_umbral = "true";
  }

  // MQ-135
  int mq135_adc = analogRead(A5);
  float mq135_voltaje = mq135_adc * (5.0 / 1023.0);
  float mq135_resistencia = 1000*((5-mq135_voltaje)/mq135_voltaje);
  // PENDIENTE DE AJUSTE
  double dioxidoDeCarbono = 0.4091*pow(mq135_resistencia/5463, -1.497);
  double oxidosDeNitrogeno = 0.4091*pow(mq135_resistencia/5463, -1.497);
  double amoniaco = 0.4091*pow(mq135_resistencia/5463, -1.497);
  String mq135_umbral = "false";

  if(digitalRead(5) == 0){
    mq135_umbral = "true";
  }

  // JSON
  String jsonSerial = "{";

  // MQ-135
  if (isnan(dioxidoDeCarbono) || isnan(oxidosDeNitrogeno) || isnan(amoniaco)) {

    jsonSerial += "\"dioxidoDeCarbono\": {";
    jsonSerial += "\"valido\": false,";
    jsonSerial += "\"error\": \"Valor númerico no valido\"";
    jsonSerial += "},";

    jsonSerial += "\"oxidosDeNitrogeno\": {";
    jsonSerial += "\"valido\": false,";
    jsonSerial += "\"error\": \"Valor númerico no valido\"";
    jsonSerial += "},";

    jsonSerial += "\"amoniaco\": {";
    jsonSerial += "\"valido\": false,";
    jsonSerial += "\"error\": \"Valor númerico no valido\"";
    jsonSerial += "},";

  } else {

    jsonSerial += "\"amoniaco\": {";
    jsonSerial += "\"valido\": true,";
    jsonSerial += "\"valor\":"; 
    jsonSerial += amoniaco;
    jsonSerial += ",\"unidad\": \"ppm\",";
    jsonSerial += "\"descripcion\": \"Amoníaco\",";      
    jsonSerial += "\"formulaQuimica\": [\"NH3\"],";    
    jsonSerial += "\"umbralAlcanzado\": ";
    jsonSerial += mq135_umbral;
    jsonSerial += ",\"voltaje\": ";
    jsonSerial += mq135_voltaje;
    jsonSerial += ",\"resistencia\":";
    jsonSerial += mq135_resistencia;
    jsonSerial += ",\"valorAnalogico\":";
    jsonSerial += mq135_adc;
    jsonSerial += ",\"sensor\": \"MQ-135\"";
    jsonSerial += "},";

    jsonSerial += "\"dioxidoDeCarbono\": {";
    jsonSerial += "\"valido\": true,";
    jsonSerial += "\"valor\":"; 
    jsonSerial += dioxidoDeCarbono;
    jsonSerial += ",\"unidad\": \"ppm\",";
    jsonSerial += "\"descripcion\": \"Dióxido de carbono\",";      
    jsonSerial += "\"formulaQuimica\": [\"CO2\"],";    
    jsonSerial += "\"umbralAlcanzado\": ";
    jsonSerial += mq135_umbral;
    jsonSerial += ",\"voltaje\": ";
    jsonSerial += mq135_voltaje;
    jsonSerial += ",\"resistencia\":";
    jsonSerial += mq135_resistencia;
    jsonSerial += ",\"valorAnalogico\":";
    jsonSerial += mq135_adc;
    jsonSerial += ",\"sensor\": \"MQ-135\"";
    jsonSerial += "},";  

    jsonSerial += "\"oxidosDeNitrogeno\": {";
    jsonSerial += "\"valido\": true,";
    jsonSerial += "\"valor\":"; 
    jsonSerial += oxidosDeNitrogeno;
    jsonSerial += ",\"unidad\": \"ppm\",";
    jsonSerial += "\"descripcion\": \"Óxidos de nitrógeno (Óxido nitroso, Óxido nítrico, Anhídrido nitroso, Tetraóxido de nitrógeno, Peróxido nítrico, Anhídrido nítrico)\",";      
    jsonSerial += "\"formulaQuimica\": [\"NOx\", \"N2O\", \"NO\", \"N2O3\", \"N2O4\", \"NO2\", \"N2O5\"],";    
    jsonSerial += "\"umbralAlcanzado\": ";
    jsonSerial += mq135_umbral;
    jsonSerial += ",\"voltaje\": ";
    jsonSerial += mq135_voltaje;
    jsonSerial += ",\"resistencia\":";
    jsonSerial += mq135_resistencia;
    jsonSerial += ",\"valorAnalogico\":";
    jsonSerial += mq135_adc;
    jsonSerial += ",\"sensor\": \"MQ-135\"";
    jsonSerial += "},"; 

  }

  // MQ-8
  if (isnan(hidrogeno)) {

    jsonSerial += "\"hidrogeno\": {";
    jsonSerial += "\"valido\": false,";
    jsonSerial += "\"error\": \"Valor númerico no valido\"";
    jsonSerial += "},";

  } else {

    jsonSerial += "\"hidrogeno\": {";
    jsonSerial += "\"valido\": true,";
    jsonSerial += "\"valor\":"; 
    jsonSerial += hidrogeno;
    jsonSerial += ",\"unidad\": \"ppm\",";
    jsonSerial += "\"descripcion\": \"Hidrógeno\",";      
    jsonSerial += "\"formulaQuimica\": [\"H2\"],";    
    jsonSerial += "\"umbralAlcanzado\": ";
    jsonSerial += mq8_umbral;
    jsonSerial += ",\"voltaje\": ";
    jsonSerial += mq8_voltaje;
    jsonSerial += ",\"resistencia\":";
    jsonSerial += mq8_resistencia;
    jsonSerial += ",\"valorAnalogico\":";
    jsonSerial += mq8_adc;
    jsonSerial += ",\"sensor\": \"MQ-8\"";
    jsonSerial += "},";  

  }

  // MQ-7
  if (isnan(monoxidoDeCarbono)) {

    jsonSerial += "\"monoxidoDeCarbono\": {";
    jsonSerial += "\"valido\": false,";
    jsonSerial += "\"error\": \"Valor númerico no valido\"";
    jsonSerial += "},";

  } else {

    jsonSerial += "\"monoxidoDeCarbono\": {";
    jsonSerial += "\"valido\": true,";
    jsonSerial += "\"valor\":"; 
    jsonSerial += monoxidoDeCarbono;
    jsonSerial += ",\"unidad\": \"ppm\",";
    jsonSerial += "\"descripcion\": \"Monóxido de Carbono\",";      
    jsonSerial += "\"formulaQuimica\": [\"CO\"],";    
    jsonSerial += "\"umbralAlcanzado\": ";
    jsonSerial += mq7_umbral;
    jsonSerial += ",\"voltaje\": ";
    jsonSerial += mq7_voltaje;
    jsonSerial += ",\"resistencia\":";
    jsonSerial += mq7_resistencia;
    jsonSerial += ",\"valorAnalogico\":";
    jsonSerial += mq7_adc;
    jsonSerial += ",\"sensor\": \"MQ-7\"";
    jsonSerial += "},";

  }

  // MQ-6
  if (isnan(propano)) {

    jsonSerial += "\"propano\": {";
    jsonSerial += "\"valido\": false,";
    jsonSerial += "\"error\": \"Valor númerico no valido\"";
    jsonSerial += "},";

  } else {

    jsonSerial += "\"propano\": {";
    jsonSerial += "\"valido\": true,";
    jsonSerial += "\"valor\":"; 
    jsonSerial += propano;
    jsonSerial += ",\"unidad\": \"ppm\",";
    jsonSerial += "\"descripcion\": \"Propano\",";      
    jsonSerial += "\"formulaQuimica\": [\"C3H8\"],";    
    jsonSerial += "\"umbralAlcanzado\": ";
    jsonSerial += mq6_umbral;
    jsonSerial += ",\"voltaje\": ";
    jsonSerial += mq6_voltaje;
    jsonSerial += ",\"resistencia\":";
    jsonSerial += mq6_resistencia;
    jsonSerial += ",\"valorAnalogico\":";
    jsonSerial += mq6_adc;
    jsonSerial += ",\"sensor\": \"MQ-6\"";
    jsonSerial += "},";

  }

  // MQ-4
  if (isnan(metano)) {

    jsonSerial += "\"metano\": {";
    jsonSerial += "\"valido\": false,";
    jsonSerial += "\"error\": \"Valor númerico no valido\"";
    jsonSerial += "},";

  } else {

    jsonSerial += "\"metano\": {";
    jsonSerial += "\"valido\": true,";
    jsonSerial += "\"valor\":"; 
    jsonSerial += metano;
    jsonSerial += ",\"unidad\": \"ppm\",";
    jsonSerial += "\"descripcion\": \"Gas natural, Metano\",";      
    jsonSerial += "\"formulaQuimica\": [\"CH4\"],";    
    jsonSerial += "\"umbralAlcanzado\": ";
    jsonSerial += mq4_umbral;
    jsonSerial += ",\"voltaje\": ";
    jsonSerial += mq4_voltaje;
    jsonSerial += ",\"resistencia\":";
    jsonSerial += mq4_resistencia;
    jsonSerial += ",\"valorAnalogico\":";
    jsonSerial += mq4_adc;
    jsonSerial += ",\"sensor\": \"MQ-4\"";
    jsonSerial += "},"; 

  }

  // MQ-2
  if (isnan(glp)) {
    
    jsonSerial += "\"glp\": {";
    jsonSerial += "\"valido\": false,";
    jsonSerial += "\"error\": \"Valor númerico no valido\"";
    jsonSerial += "},";
  
  } else {

    jsonSerial += "\"glp\": {";
    jsonSerial += "\"valido\": true,";
    jsonSerial += "\"valor\":"; 
    jsonSerial += glp;
    jsonSerial += ",\"unidad\": \"ppm\",";
    jsonSerial += "\"descripcion\": \"Gas licuado del petróleo (Propano, Butano, ambos)\",";      
    jsonSerial += "\"formulaQuimica\": [\"C3H8\", \"C4H10\"],";    
    jsonSerial += "\"umbralAlcanzado\": ";
    jsonSerial += mq2_umbral;
    jsonSerial += ",\"voltaje\": ";
    jsonSerial += mq2_voltaje;
    jsonSerial += ",\"resistencia\":";
    jsonSerial += mq2_resistencia;
    jsonSerial += ",\"valorAnalogico\":";
    jsonSerial += mq2_adc;
    jsonSerial += ",\"sensor\": \"MQ-2\"";
    jsonSerial += "},";  

  }

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