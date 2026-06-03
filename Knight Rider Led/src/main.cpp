/**
 * @author Yuke Brilliant Hestiavin 5024241016
 * Knight Rider Running Light with Brightness Control and Speed Control using Potentiometer,
 * LDR control, and async WiFi Network Scanner
 */

#include <Arduino.h>
#include <WiFi.h>

// LED Pins
#define LED1_PIN 25
#define LED2_PIN 26
#define LED3_PIN 27

// Potentiometer Pins
#define POT_PIN_SPEED 34
#define POT_PIN_BRIGHTNESS 35

// LDR Pin
#define LDR_PIN 32
const int LDR_THRESHOLD = 2000;

const unsigned long WIFI_SCAN_INTERVAL = 10000;
unsigned long lastScanTime = 0;
bool scanRunning = false;

const int ledSequence[] = {LED1_PIN, LED2_PIN, LED3_PIN, LED2_PIN};
const int sequenceLength = 4;

int currentLedIndex = 0;
unsigned long lastLedMoveTime = 0;

void turnOffAllLEDs() {
  analogWrite(LED1_PIN, 0);
  analogWrite(LED2_PIN, 0);
  analogWrite(LED3_PIN, 0);
}

void runKnightRider() {
  int ldrValue = analogRead(LDR_PIN);

  Serial.print("LDR Value: ");
  Serial.println(ldrValue);

  if (ldrValue > LDR_THRESHOLD) {
    // Serial.println(" - It's dark, running Knight Rider effect.");

    int speedValue = analogRead(POT_PIN_SPEED);
    int brightnessValue = analogRead(POT_PIN_BRIGHTNESS);
    Serial.print("Speed Pot Value: ");
    Serial.print(speedValue);
    Serial.print(", Brightness Pot Value: ");
    Serial.println(brightnessValue);

    int speedDelay = map(speedValue, 0, 4095, 50, 500);

    int brightness = map(brightnessValue, 0, 4095, 0, 255);

    if (millis() - lastLedMoveTime >= speedDelay) {
      lastLedMoveTime = millis();

      turnOffAllLEDs();
      analogWrite(ledSequence[currentLedIndex], brightness);

      currentLedIndex++;
      if (currentLedIndex >= sequenceLength) {
        currentLedIndex = 0;
      }

      Serial.print("Speed Delay: ");
      Serial.print(speedDelay);
      Serial.print(" ms, Brightness: ");
      Serial.println(brightness);
    }

  } else {
    // Serial.println(" - It's bright, turning off LEDs.");
    turnOffAllLEDs();
  }
}

void handleWiFiScan() {
  int scanResult = WiFi.scanComplete();

  if (scanRunning && scanResult >= 0) {
    Serial.printf("\nFound %d networks:\n", scanResult);

    if (scanResult == 0) {
      Serial.println("No networks found.");
    } else {
      Serial.println("Network List:");
      for (int i = 0; i < scanResult; ++i) {
        Serial.printf(
          "%d: SSID: %s, RSSI: %d dBm, Channel: %d, Encryption: %s\n",
          i + 1,
          WiFi.SSID(i).c_str(),
          WiFi.RSSI(i),
          WiFi.channel(i),
          (WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? "Open" : "Secured"
        );
      }
    }

    Serial.println("==============================");

    WiFi.scanDelete();
    scanRunning = false;
    lastScanTime = millis();
  }

  if (!scanRunning && millis() - lastScanTime >= WIFI_SCAN_INTERVAL) {
    Serial.println("\n==== WiFi Network Scanner ====");
    Serial.println("Scanning for WiFi networks...");
    Serial.println("==============================");

    WiFi.scanNetworks(true); // true = async scan
    scanRunning = true;
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);

  pinMode(POT_PIN_SPEED, INPUT);
  pinMode(POT_PIN_BRIGHTNESS, INPUT);
  pinMode(LDR_PIN, INPUT);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  Serial.println("System started.");

  lastScanTime = millis() - WIFI_SCAN_INTERVAL;
}

void loop() {
  handleWiFiScan();
  runKnightRider();

  delay(50);
}