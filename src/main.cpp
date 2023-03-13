#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoOTA.h>
#include <Ticker.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#define WIFI_SSID ""
#define WIFI_PASSWORD ""

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "id.pool.ntp.org", 7*3600);

Ticker timer1Sec;
void onTimer1Sec()
{
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  // Serial.println("Hello World");
  Serial.println("Now: "+timeClient.getFormattedTime());
}

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
  ArduinoOTA.setHostname("esp32_iot8");
  ArduinoOTA.begin();
  timeClient.begin();
  timer1Sec.attach(1, onTimer1Sec);
}

void loop()
{
  timeClient.update();
  ArduinoOTA.handle();
}