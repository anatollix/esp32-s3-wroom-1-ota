#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <ElegantOTA.h>
#include "../include/config.h"

WebServer server(80);

void handleRoot() {
  server.send(200, "text/plain", "ESP32-S3 OTA Server Running!\nGo to /update for firmware update");
}

void setup() {
  Serial.begin(115200);
  delay(3000);

  Serial.println("\n========================================");
  Serial.println("   ESP32-S3 OTA");
  Serial.println("========================================");
  Serial.printf("Board: ESP32-S3-WROOM-1\n");
  Serial.printf("CPU Freq: %d MHz\n", ESP.getCpuFreqMHz());
  Serial.printf("Free Heap: %d bytes\n", ESP.getFreeHeap());
  Serial.printf("WiFi SSID: %s\n", WIFI_SSID);
  Serial.println("========================================\n");
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\n✓ WiFi Connected!");
  Serial.println("IP: " + WiFi.localIP().toString());
  Serial.println("Go to: http://" + WiFi.localIP().toString() + "/update\n");
  
  server.on("/", HTTP_GET, handleRoot);
  ElegantOTA.begin(&server);
  server.begin();
  
  Serial.println("✓ Web Server Started");
}

void loop() {
  server.handleClient();
  ElegantOTA.loop();
  delay(10);
}
