#include "mqtt.h"

/*--------------------------- MQTT ---------------------------*/
WiFiClient wifiClient;
PubSubClient client(wifiClient);
StaticJsonDocument<256> json;

const char* ssid = "AIoT Lab 2G";
const char* password = "ptitlab@123";
/*-------------------------------------------------------------*/

void Wifi_Setup(void) 
{
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}
 
void MQTT_Setup(void) 
{
  while (!client.connected()) 
  {
    Serial.println("MQTT: Attempting connection...");
    String clientId = "ESP32";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) 
    {
      Serial.println("MQTT: connected");
      // client.subscribe(MQTT_TOPIC);
    } 
    else 
    {
      Serial.print("MQTT: failed, rc= ");
      Serial.print(client.state());
      Serial.println(" try again in 2 seconds");
      delay(1000);
    }
  }
}

void MQTT_Publish(uint8_t state)
{
    char buffer[256];
    // Clear the JSON object
    json.clear();

    // Add data to the JSON object
    json["state"] = state;

    // Add a nested object
    serializeJson(json, buffer);

    // Print the JSON message to the Serial Monitor
    Serial.println(buffer);
    // Publish the JSON message to the MQTT topic
    client.publish(MQTT_TOPIC, buffer);
    // Clear the JSON object
    json.clear();
}