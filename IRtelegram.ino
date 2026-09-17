#include <WiFi.h>
#include <WiFiClientSecure.h> //https - ssl certificate 
#include <UniversalTelegramBot.h>

char ssid[]="OnePlus Nord  Bhagyashri Kodi";
char password[]="Bhagya@123";

#define BOT_TOKEN "8806995806:AAHBkf_lsIJFUFySH-MlARfuTgVOPN5K4lM"
#define CHAT_ID "6777170148"

WiFiClientSecure client;
UniversalTelegramBot bot(BOT_TOKEN,client);

#define ir 7

void setup() {
  Serial.begin(115200);
  pinMode(ir,INPUT);
  WiFi.begin(ssid,password);

  Serial.println("Connecting to WIFI");
  while (WiFi.status()!=WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WIFI Connected");

  client.setInsecure(); //disable ssl certificate
  Serial.println("Telegram connected");

  bot.sendMessage(CHAT_ID,"ESP32 and Telegram connected successfully");
}

void loop() {
  int value= digitalRead(ir);
  if (value==LOW){
    Serial.println("Object detected");
    bot.sendMessage(CHAT_ID,"ALERT! Someone is near your home");
    delay(3000);
  }
  else{
    Serial.println("Object is not detected");
  }
  delay(2000);
}