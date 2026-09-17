#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

const char* ssid = "OnePlus Nord  Bhagyashri Kodi";
const char* password = "Bhagya@123";

#define BOT_TOKEN "8806995806:AAHBkf_lsIJFUFySH-MlARfuTgVOPN5K4lM"
#define CHAT_ID "6777170148"

#define TRIG_PIN 7
#define ECHO_PIN 8

WiFiClientSecure client;
UniversalTelegramBot bot(BOT_TOKEN, client);

void setup()
{
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  WiFi.begin(ssid, password);

  Serial.println("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Connected!");

  client.setInsecure();

  bot.sendMessage(
    CHAT_ID,
    "ESP32-S3 Ultrasonic Sensor connected successfully!",
    ""
  );
}

void loop()
{
  long duration;
  float distance;

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);

  distance = duration * 0.0343 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance < 10)
  {
    Serial.println("Object is VERY CLOSE");

    bot.sendMessage(
      CHAT_ID,
      "Object is VERY CLOSE!\nDistance: " + String(distance, 1) + " cm",
      ""
    );
  }
  else if (distance < 20)
  {
    Serial.println("Object is NEAR");

    bot.sendMessage(
      CHAT_ID,
      "Object is NEAR.\nDistance: " + String(distance, 1) + " cm",
      ""
    );
  }
  else if (distance < 50)
  {
    Serial.println("Object is at MEDIUM distance");

    bot.sendMessage(
      CHAT_ID,
      "Object is at MEDIUM distance.\nDistance: " + String(distance, 1) + " cm",
      ""
    );
  }
  else
  {
    Serial.println("Object is FAR");

    bot.sendMessage(
      CHAT_ID,
      "Object is FAR.\nDistance: " + String(distance, 1) + " cm",
      ""
    );
  }

  delay(5000);
}