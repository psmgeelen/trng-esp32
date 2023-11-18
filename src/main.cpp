#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoJson.h>
// #include <FreeRTOS.h>

const char *SSID = "FamGeelen2.4Ghz";
const char *PWD = "Schnitzel123#";


// Web server running on port 80
WebServer server(80);

// JSON data buffer
StaticJsonDocument<250> jsonDocument;
char buffer[250];


void connectToWiFi() {
  Serial.print("Connecting to ");
  Serial.println(SSID);
  
  WiFi.begin(SSID, PWD);
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
    // we can even make the ESP32 to sleep
  }
 
  Serial.print("Connected. IP: ");
  Serial.println(WiFi.localIP());
}

void create_json(char *tag, int32_t value, char *unit) {  
  jsonDocument.clear();  
  jsonDocument["type"] = tag;
  jsonDocument["value"] = value;
  jsonDocument["unit"] = unit;
  serializeJson(jsonDocument, buffer);
}


void randomNr32Bit() {
  Serial.println("Get Random Nr");
  create_json("random32Bit", esp_random(), "int");
  server.send(200, "application/json", buffer);
}

void ping() {
  Serial.println("Ping!");
  create_json("ping", 0, "pong");
  server.send(200, "application/json", buffer);
}

void setup_routing() {
  server.on("/random_nr_32bit", randomNr32Bit);
  server.on("/ping", ping);

  // start server
  server.begin();
}


void setup() {
  Serial.begin(9600);

  connectToWiFi();
  // setup_task();
  setup_routing();
};

void loop() {
  server.handleClient();
}