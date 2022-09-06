#include <WiFi.h>
#include <PubSubClient.h>

const char *ssid = "KNUET-Gast";
const char *password = "Knuet201";
WiFiClient espClient;

const char *mqttBrocker = "broker.emqx.io";
const char *topic = "esp32/test";
const char *mqttUsername = "emqx";
const char *mqttPassword = "public";
const int mqttPort = 1883;
PubSubClient client(espClient);
  
void setup() {

  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("Connection to ");
    Serial.println(ssid);
  }
  Serial.println("Connection done.");
  // mqtt
  client.setServer(mqttBrocker, mqttPort);
  client.setCallback(callback);
  while(!client.connected()){
    String clientID = "esp32-basakerkek-";
    clientID += String(WiFi.macAddress());
    Serial.printf("The %s tries to connect to mqtt brocker...\n",clientID.c_str());
    if(client.connect(clientID.c_str(), mqttUsername, mqttPassword)){
    }
    else {
      Serial.print("mqtt connection failed");
      Serial.println(client.state());
      delay(2000);
    }
  }
  client.publish(topic, "Hi EMQX brocker I´m a ESP32 :)");
  client.subscribe(topic);
}

void loop() {
  client.loop();
}


void callback(char *topic, byte *payload, unsigned int length){
  Serial.print ("Message recieved in topic: ");
  Serial.println(topic);
  Serial.print("The message is: ");
  for(int i=0;i<length; i++){
    Serial.print((char) payload[i]);
  }
  Serial.println();
  Serial.println("-+-+-+End+-+-+-+-");
}
  
