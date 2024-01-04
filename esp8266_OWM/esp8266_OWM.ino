#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

const char *ssid = "netis";
const char *password = "password";
const char *apiKey = "000be634412f078ad203b00957e74c50"; 

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

float kelvinToCelsius(float kelvin) {
  return kelvin - 273.15; 
}

void loop() {
  Serial.println("Введите название города:");
  while (Serial.available() == 0) {
  }

  String cityName = Serial.readStringUntil('\n');
  cityName.trim();

  HTTPClient http;
  WiFiClient client;

  String url = "http://api.openweathermap.org/data/2.5/weather?q=" + cityName + "&lang=ru&appid=" + String(apiKey);

  http.begin(client, url);
  int httpCode = http.GET();

  if (httpCode > 0) {
    String payload = http.getString();
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, payload);
    float temperature = doc["main"]["temp"];
    temperature = kelvinToCelsius(temperature);
    String weatherDescription = doc["weather"][0]["description"];
    int humidity = doc["main"]["humidity"];
    float windSpeed = doc["wind"]["speed"];
    Serial.println("Температура: " + String(temperature) + "°C");
    Serial.println("Состояние облачности: " + weatherDescription);
    Serial.println("Влажность: " + String(humidity) + "%");
    Serial.println("Скорость ветра: " + String(windSpeed) + " м/с");
  } else {
    Serial.println("Error on HTTP request");
  }
  
  http.end();
  delay(5000);
}
