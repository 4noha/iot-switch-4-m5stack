#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>

#define SSID_ "--------------------------------"
#define PASSWORD "--------------------------------"

#define API_HOST "api.switch-bot.com"
#define SWITCHBOT_ACCESSTOKEN "--------------------------------"
// device
/* Exsample
#define LIGHT "--------------------------------"
#define AIRCON "--------------------------------"
#define AIRCON2 "--------------------------------"
*/
RTC_DATA_ATTR int mode = 0;

void connectWifi() {
  WiFi.begin(SSID_, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
  }
}

void requestCommand(String path, String body) {
  String host = API_HOST;
  HTTPClient http;
  http.begin("https://" + host + path);
  http.addHeader("Authorization", SWITCHBOT_ACCESSTOKEN);
  http.POST(body);
  http.end();
}

void requestCommands(int count, String *deviceIds, String *commands) {
  // TODO: Onetime https connection
  for(int i=0; i<count; i++) {
    String path = "/v1.0/devices/" + deviceIds[i] + "/commands";
    String body = "{\"command\":\"" + commands[i] + "\",\"comandType\":\"command\"}";
    requestCommand(path, body);
  }
}

void setup() {

  if(mode == 1) {
    connectWifi();
    /* Exsample
    String deviceIds[2] = { AIRCON, AIRCON };
    String commandTypes[2] = { "commnand", "commnand" };
    String commands[2] = { "turnOn", "turnOff" };
    requestCommands(2, deviceIds, commands);
    */
  } else if(mode == 2) {
    M5.Lcd.setCursor(100, 100);
    M5.Lcd.print("OFF");
    connectWifi();
    /* Exsample
    String deviceIds[1] = { AIRCON };
    String commandTypes[1] = { "commnand" };
    String commands[1] = { "turnOff" };
    requestCommands(1, deviceIds, commands);
    */
    mode = 0;
  }
  mode++;
  
  esp_deep_sleep_enable_gpio_wakeup(1 << 3, ESP_GPIO_WAKEUP_GPIO_LOW);
  esp_deep_sleep_start();
}

void loop() {
}
