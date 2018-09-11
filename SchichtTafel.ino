#include "CTBot.h"
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN D4
#define LEDS 50
int schicht = 0;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LEDS, PIN, NEO_GRB + NEO_KHZ800);
CTBot myBot;
CTBotInlineKeyboard myKbd; 

String ssid = "your_ssid";
String pass = "your_wifi_password";
String token = "Telegram_Bot_Token";   


void ReSetLED(byte LED, byte red, byte green, byte blue){
   for(int i = 0; i < LEDS; i++) {
    strip.setPixelColor(i, 0,0,0);
   }
  strip.setPixelColor(LED, red, green, blue);
  strip.show();
  }


void setup() {
strip.begin(); 
for(int i = 0; i < LEDS; i++) {
    strip.setPixelColor(i, 0,0,0);
   }
strip.show();
Serial.begin(9600);
Serial.println("Starting TelegramBot...");
#define Fruehschicht "Frueh"
#define Spaetschicht "Spaet"
#define Nachtschicht "Nacht"
#define Werkstatt "Werkstatt"
#define Status "Status"

myBot.wifiConnect(ssid, pass);

  // set the telegram bot token
  myBot.setTelegramToken(token);

  myKbd.addButton("Frühschicht", Fruehschicht, CTBotKeyboardButtonQuery);
  myKbd.addButton("Spätschicht", Spaetschicht, CTBotKeyboardButtonQuery);
  myKbd.addButton("Nachtschicht", Nachtschicht, CTBotKeyboardButtonQuery);
  myKbd.addButton("Werkstatt", Werkstatt, CTBotKeyboardButtonQuery);
  myKbd.addRow();
  myKbd.addButton("Status", Status, CTBotKeyboardButtonQuery);
   if (myBot.testConnection())
    Serial.println("\ntestConnection OK");
  else
    Serial.println("\ntestConnection NOK");
}
void status(byte msgid) {
  if (schicht = 0) {
    myBot.sendMessage(msgid, "Bot wurde neugestartet und hat keinen Wert!");
    }
  if (schicht = 1) {
    myBot.sendMessage(msgid, "Aktuelle Schicht: Frühschicht");
    }
  if (schicht = 2) {
    myBot.sendMessage(msgid, "Aktuelle Schicht: Spätschicht");
    }
  if (schicht = 3) {
    myBot.sendMessage(msgid, "Aktuelle Schicht: Nachtschicht");
    }
  if (schicht = 4) {
    myBot.sendMessage(msgid, "Aktuelle Schicht: Werkstatt");
    }
  }

void loop() {
  // a variable to store telegram message data
  TBMessage msg;

  if (myBot.getNewMessage(msg)) {
    if (msg.messageType == CTBotMessageText) {
        if(msg.text.equalsIgnoreCase("/help")) {
          myBot.sendMessage(msg.sender.id, "Help:\n/schicht - Zeigt Schicht Keyboard\n/status - Zeit den aktuellen Status der LED´s");
        } else if(msg.text.equalsIgnoreCase("/schicht")) {
          myBot.sendMessage(msg.sender.id, "Schicht Keyboard", myKbd);
        } else if(msg.text.equalsIgnoreCase("/status")) {
              if (schicht == 0) {
               myBot.sendMessage(msg.sender.id, "Bot wurde neugestartet und hat keinen Wert!");
              }
              if (schicht == 1) {
              myBot.sendMessage(msg.sender.id, "Aktuelle Schicht: Frühschicht");
              }
              if (schicht == 2) {
              myBot.sendMessage(msg.sender.id, "Aktuelle Schicht: Spätschicht");
              }
              if (schicht == 3) {
              myBot.sendMessage(msg.sender.id, "Aktuelle Schicht: Nachtschicht");
              }
              if (schicht == 4) {
               myBot.sendMessage(msg.sender.id, "Aktuelle Schicht: Werkstatt");
              }
        } else {
          myBot.sendMessage(msg.sender.id, "Unbekannter Befehl");
        }
    } else if (msg.messageType == CTBotMessageQuery) {
        if (msg.callbackQueryData.equals(Fruehschicht)) {
            schicht = 1;
            ReSetLED(0,0,255,0);
           myBot.endQuery(msg.callbackQueryID, "Frühschicht", false);
        } else if (msg.callbackQueryData.equals(Spaetschicht)) {
            schicht = 2;
            ReSetLED(1,0,0,255);
            myBot.endQuery(msg.callbackQueryID, "Spätschicht", false);
        } else if (msg.callbackQueryData.equals(Nachtschicht)) { 
            schicht = 3;
            ReSetLED(2,255,0,0);
            myBot.endQuery(msg.callbackQueryID, "Nachtschicht", false);
        }else if (msg.callbackQueryData.equals(Werkstatt)) { 
            schicht = 4;
            ReSetLED(4,185,190,20);
            myBot.endQuery(msg.callbackQueryID, "Werkstatt", false);
        } else if (msg.callbackQueryData.equals(Status)) { 
            myBot.endQuery(msg.callbackQueryID, "status", false);
            if (schicht == 0) {
               myBot.sendMessage(msg.sender.id, "Bot wurde neugestartet und hat keinen Wert!");
              }
              if (schicht == 1) {
              myBot.sendMessage(msg.sender.id, "Aktuelle Schicht: Frühschicht");
              }
              if (schicht == 2) {
              myBot.sendMessage(msg.sender.id, "Aktuelle Schicht: Spätschicht");
              }
              if (schicht == 3) {
              myBot.sendMessage(msg.sender.id, "Aktuelle Schicht: Nachtschicht");
              }
              if (schicht == 4) {
               myBot.sendMessage(msg.sender.id, "Aktuelle Schicht: Werkstatt");
              }
        }
     } 
  }
}
