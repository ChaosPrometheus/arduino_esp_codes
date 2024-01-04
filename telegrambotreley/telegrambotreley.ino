#include <FastBot.h>
const int relayPin = D6;  // D1 on NodeMCU

#define WIFI_SSID "Wi-Fi Home"
#define WIFI_PASS "B@rs2023"
#define BOT_TOKEN "5941862271:AAHAU9K4PPy7L54EH10ZLQGYi74mANZ9z7I"

FastBot bot(BOT_TOKEN);

void setup() {
  connectWiFi();
  bot.attach(newMsg);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);
  String hostname = "NodeMCU";
  WiFi.hostname(hostname);
}

// обработчик сообщений
void newMsg(FB_msg& msg) {
  if (msg.text == "1") 
    digitalWrite(relayPin, HIGH);
    bot.sendMessage("Relay is deactivated.",msg.chatID);

  if (msg.text == "0") 
    digitalWrite(relayPin, LOW);
}

void loop() {
  bot.tick();
}

void connectWiFi() {
  delay(2000);
  // Serial.begin(115200);  // Commenting out the serial monitor initialization
  // Serial.println();     // Commenting out the initial newline

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    // Serial.print(".");   // Commenting out the dots during WiFi connection
    if (millis() > 15000) ESP.restart();
  }
  // Serial.println("Connected");  // Commenting out the "Connected" message
}

