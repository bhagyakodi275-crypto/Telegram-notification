#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

const char* ssid = "OnePlus Nord  Bhagyashri Kodi";
const char* password = "Bhagya@123";

#define BOT_TOKEN "8806995806:AAHBkf_lsIJFUFySH-MlARfuTgVOPN5K4lM"
#define CHAT_ID "6777170148"

#define PIR_PIN 7

WiFiClientSecure client;
UniversalTelegramBot bot(BOT_TOKEN, client);

int previousState = LOW;

void setup()
{
  Serial.begin(115200);

  pinMode(PIR_PIN, INPUT);

  WiFi.begin(ssid, password);

  Serial.println("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  client.setInsecure();

  Serial.println("Telegram connected");

  bot.sendMessage(
    CHAT_ID,
    "ESP32-S3 PIR sensor connected successfully!",
    ""
  );

  previousState = digitalRead(PIR_PIN);
}

void loop()
{
  int currentState = digitalRead(PIR_PIN);

  if (currentState == HIGH && previousState == LOW)
  {
    Serial.println("Motion Detected!");

    bot.sendMessage(
      CHAT_ID,
      "Motion Detected!",
      ""
    );

    previousState = HIGH;
  }
  else if (currentState == LOW && previousState == HIGH)
  {
    Serial.println("Motion Not Detected");

    bot.sendMessage(
      CHAT_ID,
      "Motion stopped.",
      ""
    );

    previousState = LOW;
  }

  delay(200);
}