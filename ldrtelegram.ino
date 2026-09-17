#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

char ssid[] = "OnePlus Nord  Bhagyashri Kodi";
char password[] = "Bhagya@123";

#define BOT_TOKEN "8806995806:AAHBkf_lsIJFUFySH-MlARfuTgVOPN5K4lM"
#define CHAT_ID "6777170148"

WiFiClientSecure client;
UniversalTelegramBot bot(BOT_TOKEN, client);

#define LDR_PIN 4

void setup() {
  Serial.begin(115200);

  pinMode(LDR_PIN, INPUT);

  WiFi.begin(ssid, password);

  Serial.println("Connecting to WIFI");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WIFI Connected");

  client.setInsecure();

  Serial.println("Telegram connected");

  bot.sendMessage(CHAT_ID, "ESP32 and LDR connected successfully", "");
}

void loop() {
  int ldrValue = analogRead(LDR_PIN);

  Serial.print("LDR Value: ");
  Serial.println(ldrValue);

  if (ldrValue < 1500) {
    Serial.println("DARK");
    bot.sendMessage(CHAT_ID, "ALERT! It is Bright", "");
    delay(5000);
  }
  else {
    Serial.println("Dark");
  }

  delay(2000);
}