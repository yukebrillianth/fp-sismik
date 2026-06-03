/**
 * @author Yuke Brilliant Hestiavin 5024241016
 * ESP32 WiFi Network Scanner
 */
#include <Arduino.h>
#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  delay(100);
  Serial.printf("==== WiFi Network Scanner ====");
  Serial.printf("Scanning for WiFi networks...");
  Serial.printf("==============================");
}

void loop() {
  int numNetworks = WiFi.scanNetworks();
  Serial.printf("Found %d networks:\n", numNetworks);

  if (numNetworks == 0) {
    Serial.println("No networks found.");
  } else {
    Serial.println("Network List:");
    for (int i = 0; i < numNetworks; ++i) {
      Serial.printf("%d: SSID: %s, RSSI: %d dBm, Channel: %d, Encryption: %s\n",
                    i + 1,
                    WiFi.SSID(i).c_str(),
                    WiFi.RSSI(i),
                    WiFi.channel(i),
                    (WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? "Open" : "Secured");
    }
    Serial.println("==============================");

    WiFi.scanDelete(); // Clear scan results to free memory
    delay(10000);  // Scan every 10 seconds
  }
}