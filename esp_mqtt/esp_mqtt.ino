#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";
const char* mqttServer = "192.168.100.11";
const int mqttPort = 1883;
const char* mqttTopic = "esp/init";

WiFiClient espClient;
PubSubClient client(espClient);

// Function declarations
// Lihat kode setelah void loop(); untuk mengetahui cara fungsinya bekerja.
void callback(char* topic, byte* payload, unsigned int length);
void connectToWifi(const char* ssid, const char* password);
void initMqtt(const char* server, int port);

void setup() {
  Serial.begin(115200);
  // Menghubungkan ke jaringan Wi-Fi
  connectToWifi(ssid, password);
  // Menghubungkan ke Broker MQTT
  initMqtt(mqttServer, mqttPort);
}

void loop() {
  // Tetapkan waktu tunggu jika diperlukan
    client.loop();
}

void callback(char* topic, byte* payload, unsigned int length){
  char response[length + 1];
  memcpy(response, payload, length);
  response[length] = '\0';
  Serial.println(response);
  Serial.println(topic);
}

void connectToWifi(const char* ssid, const char* password){
  Serial.println();

  WiFi.begin(ssid, password);

  Serial.print("Connecting to WIFI");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}

void initMqtt(const char* server, int port){
   // Mengatur server dan port MQTT
  client.setServer(server, port);
  client.setCallback(callback);


  // Menghubungkan ke broker MQTT
  while (!client.connected()) {
    if (client.connect("ESP8266Client")) {
      Serial.println("Connected to MQTT broker");
    } else {
      Serial.println("Failed to connect to MQTT broker, retrying in 5 seconds...");
      delay(5000);
    }
  }

  // Mengambil dan mempublikasikan ID chip
  char chipId[12];
  sprintf(chipId, "%06X", ESP.getChipId());
  String chipIdStr = chipId;
  String msg = "{\"espId\":\"" + chipIdStr + "\"}";
  client.publish(mqttTopic, msg.c_str());

  //Subcribe ke URI Chip
  String topic = "esp/" + String(chipId) + "/response";
  client.subscribe(topic.c_str());
}