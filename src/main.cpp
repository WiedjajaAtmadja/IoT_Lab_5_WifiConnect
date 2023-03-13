#include <Arduino.h>
#include <WiFi.h>

#define WIFI_SSID "Lab-Eng"
#define WIFI_PASSWORD "Lab-Eng123!"

void setup()
{
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("Booting...");
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }  
  Serial.print("System connected with IP address: ");
  Serial.println(WiFi.localIP());
  Serial.printf("RSSI: %d\n", WiFi.RSSI());
}

void loop()
{
  //blink LED_BUILTIN
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}