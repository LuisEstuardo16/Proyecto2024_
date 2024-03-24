#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <Adafruit_Sensor.h>
#include "DHT.h"

// Credenciales Red WiFi
#define WIFI_SSID ""
#define WIFI_PASSWORD ""

// Credenciales Adafruit
#define ADAFRUIT_USER ""
#define ADAFRUIT_KEY ""
// Servidor
#define ADAFRUIT_SERVER "io.adafruit.com"
#define ADAFRUIT_PORT 1883
char ADAFRUIT_ID[30];
// Publicar
#define ADAFRUIT_FEED_TEM  ADAFRUIT_USER "/feeds/tem"
#define ADAFRUIT_FEED_GAS  ADAFRUIT_USER "/feeds/gas"
#define ADAFRUIT_FEED_HIGOMETRO  ADAFRUIT_USER "/feeds/higometro"
// Suscripción
#define ADAFRUIT_DATA_IN   ADAFRUIT_USER "/feeds/data_in"

#define humsuelo 34
#define SENSOR_PIN 35
#define DHTPIN    33
#define DHTTYPE DHT22       // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);
float ValTem = 0;

 // Define el pin al que está conectado el sensor
int valor;

int ValHumsuelo; // valor final del sensor
int valHum;

//**********************************
WiFiClient espClient;
PubSubClient client(espClient);

long lastMsg = 0;
long lastMsg2 = 0;
long lastMsg3 = 0;

//*****************************
//*** DECLARACION FUNCIONES ***
//*****************************
void setup_wifi();
void callback(char* topic, byte* payload, unsigned int length);
void reconnect();
void mqtt_publish(String feed, int val);
void get_MQTT_ID();

void setup() 
{
    Serial.begin(115200);
    delay(10);
  
    pinMode(humsuelo, INPUT);

    get_MQTT_ID();
    setup_wifi();
    client.setServer(ADAFRUIT_SERVER, ADAFRUIT_PORT);
    client.setCallback(callback);

    dht.begin(); //Inicializa el sensor dht
}
  
void loop() 
{
    if (!client.connected()) 
    {
      reconnect();
    }

    client.loop();
    
    long now = millis();

    if (now - lastMsg > 6500)
    {
      lastMsg = now;

      //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      ValTem = dht.readTemperature();
                
      if (isnan(ValTem)) {
          ValTem = 0;
          Serial.println(F("Error de lectura del sensor DHT22!"));
      }
              
     Serial.print(ValTem);Serial.println("°C");

      // Publicar
       mqtt_publish(ADAFRUIT_FEED_TEM, ValTem);
       //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    }

    if (now - lastMsg2 >5500 )//6500
    {
      lastMsg2 = now;

 Gas();
  Serial.print((String)"gas: "+valor+ "");
   // Publicar
   mqtt_publish2(ADAFRUIT_FEED_GAS, valor);
}

if (now - lastMsg3 > 7500)
    {
      lastMsg3 = now;
                
/*      if (isnan(ValHumsuelo)) {
          ValHumsuelo;
          Serial.println(F("Error de lectura del sensor!"));
      }*/
      
    humedadsuelo();
      Serial.print("Humedad: ");Serial.print(ValHumsuelo);
      // Publicar
       mqtt_publish3(ADAFRUIT_FEED_HIGOMETRO, ValHumsuelo);
       //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    }
}
// Función para Publicar por MQTT
void mqtt_publish(String feed, int val){
    String value = String(val);
    if(client.connected()){
        client.publish(feed.c_str(), value.c_str());
        Serial.println("Publicando al tópico: " + String(feed) + " | mensaje: " + value);        
    }
}
void mqtt_publish2(String feed2, int val2)
{
    String value2 = String(val2);
    if(client.connected()){
        client.publish(feed2.c_str(), value2.c_str());
        Serial.println("Publicando al tópico: " + String(feed2) + " | mensaje: " + value2);        
    }
}

void mqtt_publish3(String feed3, int val3){
    String value3 = String(val3);
    if(client.connected()){
        client.publish(feed3.c_str(), value3.c_str());
        Serial.println("Publicando al tópico: " + String(feed3) + " | mensaje: " + value3);        
    }
}

//*****************************
//***    CONEXION WIFI      ***
//*****************************
void setup_wifi()
{
    delay(10);
    
    // Nos conectamos a nuestra red Wifi
    Serial.println();
    Serial.print("Conectando a ");
    Serial.println(String(WIFI_SSID));

    //Serial.println(ssid);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }

    Serial.println("");
    Serial.println("Conectado a red WiFi!");
    Serial.println("Dirección IP: ");
    Serial.println(WiFi.localIP());
}

// Función para capturar data por MQTT
void callback(char *topic, byte *payload, unsigned int length)
{
    String mensaje  = "";
    String str_topic(topic); 

    for (uint16_t i = 0; i < length; i++){
        mensaje += (char)payload[i];
    }

    mensaje.trim();

    Serial.println("Tópico: " + str_topic);
    Serial.println("Mensaje: " + mensaje); 
}

// Capturar el ChipID para Id de MQTT
void get_MQTT_ID(){
    uint64_t chipid = ESP.getEfuseMac();    
    snprintf(ADAFRUIT_ID, sizeof(ADAFRUIT_ID),"%llu", chipid );
}

void reconnect() 
{
    while (!client.connected()) 
    {   
        if(client.connect(ADAFRUIT_ID, ADAFRUIT_USER, ADAFRUIT_KEY))
        {
           Serial.println("MQTT conectado!");
            client.subscribe(ADAFRUIT_DATA_IN);
            Serial.println("Suscrito al tópico: " + String(ADAFRUIT_DATA_IN));
       
          } else {
            Serial.print("falló :( con error -> ");
            Serial.print(client.state());
            Serial.println(" Intentamos de nuevo en 5 segundos");
            delay(5000);
          }
      }
}
void Gas(){
    int lectura = analogRead(SENSOR_PIN);

   valor = map(lectura, 4092, 0, 0, 100);

 
  //Imprimir valor
  Serial.print("gas en el ambiente: ");
  Serial.print(valor);
  Serial.println(" %");             
}

void humedadsuelo(){
    int lectura2 = analogRead(humsuelo);

  ValHumsuelo = map(lectura2, 4092, 0, 0, 100);

 
  //Imprimir valor
  Serial.print("Humedad del suelo: ");
  Serial.print(ValHumsuelo);
  Serial.println(" %");             
}
