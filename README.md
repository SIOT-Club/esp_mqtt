# ESP8266 MQTT Client Documentation

This documentation provides an overview and explanation of the ESP8266 MQTT client code.

## Prerequisites

To use this code, you need to have the following:

- Arduino IDE with ESP8266 board support installed.
- Wi-Fi network credentials (SSID and password).
- MQTT broker/server address and port.
- `ESP8266WiFi` library installed.
- `PubSubClient` library installed.

## Code Overview

The code establishes a connection between an ESP8266 module and an MQTT broker, and publishes the chip ID to a specified topic.

### Importing Libraries

The required libraries, `ESP8266WiFi` and `PubSubClient`, are imported.

```cpp
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
```
### Wi-Fi and MQTT Configuration

The Wi-Fi credentials, MQTT server address, port, and topic are defined.

```cpp
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";
const char* mqttServer = "192.168.100.11";
const int mqttPort = 1883;
const char* mqttTopic = "esp/init";
```

### Initializing Objects

The code initializes the `WiFiClient` and `PubSubClient` objects.
```cpp
WiFiClient espClient;
PubSubClient client(espClient);
```
### Setup Function
The `setup()` function is executed once at the beginning. It connects to the Wi-Fi network, sets up the MQTT server and port, connects to the MQTT broker, and publishes the chip ID to the specified topic.

```cpp
void setup() {
  connectToWifi(ssid, password);
  initMqtt(mqttServer, mqttPort);
}
```

### connectToWifi Function
The `connectToWifi()` function establishes a connection between the client and the Wi-Fi network.
```cpp
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
```

### initMqtt Function
The `initMqtt()` function is designed to initialize the MQTT client and establishing a connection to the specified MQTT broker.
```cpp
void initMqtt(const char* server, int port){
  // Set the broker server adress and port
  client.setServer(server, port);
  // Set the callback
  client.setCallback(callback);


  // Connect to the broker.
  while (!client.connected()) {
    if (client.connect("ESP8266Client")) {
      Serial.println("Connected to MQTT broker");
    } else {
      Serial.print("Failed to connect to MQTT broker, retrying in 5 seconds...");
      delay(5000);
    }
  }
```

### Loop Function

The `loop()` function runs repeatedly after the setup() function. It calls the client.loop() method to maintain the MQTT connection.

```cpp
void loop() {
  // Maintain MQTT connection
  client.loop();
}
```

### Usage

To use this code:
<ol>
  <li>Set the ssid and password variables to your Wi-Fi network credentials.</li>
  <li>Set the mqttServer and mqttPort variables to the MQTT broker/server address and port.</li>
  <li>Compile and upload the code to your ESP8266 module using the Arduino IDE.</li>
  <li>Open the serial monitor to view the status messages.</li>
  <li>The ESP8266 module will connect to the Wi-Fi network and MQTT broker, and publish the chip ID to the specified topic.</li>
</ol> 
    
Note: Make sure to install the required libraries and set the correct values for Wi-Fi, MQTT, and topic configurations.

> IMPORTANT: Replace "YOUR_SSID", "YOUR_PASSWORD", and "192.168.100.11" with your own values.

