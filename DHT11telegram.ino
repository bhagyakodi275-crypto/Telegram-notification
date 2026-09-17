#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <DHT.h>

const char* ssid = "OnePlus Nord  Bhagyashri Kodi";
const char* password = "Bhagya@123";

#define BOT_TOKEN "8806995806:AAHBkf_lsIJFUFySH-MlARfuTgVOPN5K4lM"
#define CHAT_ID "6777170148"

#define DHTPIN 7
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

WiFiClientSecure client;
UniversalTelegramBot bot(BOT_TOKEN, client);

void setup()
{
  Serial.begin(115200);

  dht.begin();

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
    "ESP32-S3 DHT11 connected successfully!",
    ""
  );
}

void loop()
{
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature))
  {
    Serial.println("Failed to read DHT11 sensor");
    delay(2000);
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  String message = "DHT11 Sensor Data\n";
  message += "Temperature: ";
  message += String(temperature, 1);
  message += " °C\n";
  message += "Humidity: ";
  message += String(humidity, 1);
  message += " %";

  bot.sendMessage(CHAT_ID, message, "");

  delay(1000);
}