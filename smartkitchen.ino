#include <Wire.h>
#include "DHT.h"
DHT dht(13, DHT11);

#include <LiquidCrystal.h>
LiquidCrystal lcd(14, 27, 26, 25, 33, 32);

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

// Replace with your network credentials
const char* ssid = "kitchen";
const char* password = "12345678";

// Initialize Telegram BOT
#define BOTtoken "5721238020:AAEhluM7VgBaq3EyWmI5_YHsMcymsOMBHcE"  // your Bot Token (Get from Botfather)

// Use @myidbot to find out the chat ID of an individual or a group
// Also note that you need to click "start" on a bot before it can
// message you
#define CHAT_ID "5757055741"

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);



#define gas 35
#define buzzer 19
#define motor 23

void setup() {
  pinMode(buzzer, OUTPUT);
  pinMode(gas, INPUT);
  pinMode(motor, OUTPUT);
  Serial.begin(9600);
  dht.begin();
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT);  // Add root certificate for api.telegram.org

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

 

  bot.sendMessage(CHAT_ID, "Bot started up", "");
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("SMART KITCHEN   ");
  lcd.setCursor(0, 1);
  lcd.print("                ");
  delay(5000);
  lcd.clear();
}

void loop() {
  lcd.clear();
  float T = dht.readTemperature();
  if (T > 45) {
    bot.sendMessage(CHAT_ID, "Alert!!High Temperature.", "");
    lcd.setCursor(0, 0);
    lcd.print("High Temperature");
    lcd.setCursor(0, 1);
    lcd.print("                ");
    digitalWrite(buzzer, HIGH);
    delay(1000);
    digitalWrite(buzzer, LOW);

   if (digitalRead(gas) == LOW) {
    bot.sendMessage(CHAT_ID, "Alert!! Gas detected,  FAN On", "");
    lcd.setCursor(0, 0);
    lcd.print("Gas Detected    ");
    lcd.setCursor(0, 1);
    lcd.print("Fan ON          ");
    digitalWrite(motor, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(1000);
    digitalWrite(buzzer, LOW);
   }
  } else if (digitalRead(gas) == LOW) {
    bot.sendMessage(CHAT_ID, "Alert!! Gas detected,  FAN On", "");
    lcd.setCursor(0, 0);
    lcd.print("Gas Detected    ");
    lcd.setCursor(0, 1);
    lcd.print("Fan ON          ");
    digitalWrite(motor, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(1000);
    digitalWrite(buzzer, LOW);
  }
  else {
  {
    digitalWrite(motor, LOW);
  }
  }
  delay(1000);
}
