#include "plugins/TelegramBotPlugin.h"
//#include "messages.h"
#include "secrets.h"
#include "messages.h"

TelegramBotPlugin::TelegramBotPlugin() : myBot(client, 2048) {}
///TelegramBotPlugin::TelegramBotPlugin() : myBot(WiFiClientSecure(), 2048) {}

void TelegramBotPlugin::setup() {
        client = WiFiClientSecure(); // Initialize WiFiClientSecure object
        client.setCACert(telegram_cert);

        myBot.setTelegramToken(BOT_TOKEN);
        if (myBot.begin())
           Serial.println("Telegram Bot Connection OK");
        else
           Serial.println("Telegram Bot Connectionk NOK");
/*
    myBot.onUpdate([](AsyncTelegramMessage message) {
        Serial.print("Received message: ");
        Serial.println(message.text);
        this->handleIncomingMessages(message);
    });
    */
    }

void TelegramBotPlugin::loop() {
    //TBMessage msg;
    this->handleIncomingMessages(msg);
     delay(2000);
}

const char* TelegramBotPlugin::getName() const {
    return "TelegramBotPlugin"; // name in GUI
}

void TelegramBotPlugin::teardown() {
  // code if plugin gets deactivated
}

void TelegramBotPlugin::websocketHook(DynamicJsonDocument &request) {
  // handle websocket requests
}

 void TelegramBotPlugin::handleIncomingMessages(TBMessage msg) {
  //String chatId = String(msg.chatId);
  //String text = msg.text;
  //String lastMessage;
  // if there is an incoming message...
  if (myBot.getNewMessage(msg)) {
  //  String msgText = msg.text;

 //   if (msgText.equals("/message")) {   
    if (msg.text.equals("/message")) {                   
        lastMessage = ""; // Clear any previous messages
         myBot.sendMessage(msg, "Please enter your message:");
    }
    else if (msg.text.equals("/clear")) {           // if the received message is "LIGHT OFF"...
      myBot.sendMessage(msg, "Message cleared.");
      Messages.remove();
    }
    else if (lastMessage == "") {
     lastMessage = msg.text;
     myBot.sendMessage(msg, "Message received: " + lastMessage);
  //   Messages.add(":-| :-)");
     Messages.add(std::string(lastMessage.c_str()), -1); // repeat=-1, e.g. infinite repeat every minute
   }
    else {                                              // otherwise...
      // generate the message for the sender
      String reply;
      reply = "Welcome " ;
      reply += msg.sender.username;
      reply += ".\nTry /message or /clear ";
      myBot.sendMessage(msg, reply);                    // and send it
    }
  }

}


