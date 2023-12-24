#include "plugins/TelegramBotPlugin.h"
#include "secrets.h"
#include "messages.h"

TelegramBotPlugin::TelegramBotPlugin() : myBot(client, 2048) {}
///TelegramBotPlugin::TelegramBotPlugin() : myBot(WiFiClientSecure(), 2048) {}

void TelegramBotPlugin::setup() {
   //     client = WiFiClientSecure(); // Initialize WiFiClientSecure object
        client.setCACert(telegram_cert);

        myBot.setTelegramToken(BOT_TOKEN);
        if (myBot.begin()) {
           Serial.println("Telegram Bot Connection OK");
           authorizedUserIds.push_back(TGID1);
           authorizedUsernames.push_back(TGNAME1);

        }
        else
           Serial.println("Telegram Bot Connectionk NOK");
}

void TelegramBotPlugin::loop() {
    this->handleIncomingMessages(msg);
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

  if (myBot.getNewMessage(msg)) {

    // check if we find the userID in the list of accepted users
    isAuthorized = false;
    for (int i = 0; i < sizeof(authorizedUserIds) / sizeof(authorizedUserIds[0]); i++) {
        if (msg.sender.id == authorizedUserIds[i]) {
            isAuthorized = true;
            break;
        }
    }

    // if not found check for user name
    if (!isAuthorized) {
        for (int i = 0; i < sizeof(authorizedUsernames) / sizeof(authorizedUsernames[0]); i++) {
            if (msg.sender.username.c_str() == authorizedUsernames[i]) {
                isAuthorized = true;
                break;
            }
          }
     }

  if (isAuthorized) { // we process the request

  // if there is an incoming message...

 //   if (msgText.equals("/message")) {   
    if (msg.text.equals("/message")) {                   
        lastMessage = ""; // Clear any previous messages
        awaitingMessage = true;
         myBot.sendMessage(msg, "Please enter your message:");
    }
    else if (msg.text.equals("/clear")) {           // if the received message is "LIGHT OFF"...
      myBot.sendMessage(msg, "Message cleared.");
      Messages.remove();
    }
    /*
    else if (msg.text.equals("/poweroff")) {           // if the received message is "LIGHT OFF"...
      myBot.sendMessage(msg, "Turn power off");
      currentStatus = POWEROFF;
      Serial.println("Poweroff messsage received, set status from NONE to POWEROFF");
      Messages.add("Goodbye :-(");
      Messages.scroll();
      Screen.clear();
    }
    else if (msg.text.equals("/poweron")) {           // if the received message is "LIGHT OFF"...
      myBot.sendMessage(msg, "Turn power on");
      currentStatus = NONE;
      Serial.println("Poweron message received, set status from POWEROFF to NONE");
      Messages.add("Wellcome back");
      Messages.scroll();
    }
    */
    else if (msg.text.equals("/next")) {           // if the received message is "LIGHT OFF"...
      myBot.sendMessage(msg, "Switch to next mode");
      pluginManager.activateNextPlugin();
      myBot.sendMessage(msg,pluginManager.getActivePlugin()->getName());
    }
    else if (awaitingMessage) {
     awaitingMessage = false;
     lastMessage = msg.text;
     myBot.sendMessage(msg, "Message received and\nwill be displayed on panel:\n" + lastMessage);
     Messages.add(std::string(lastMessage.c_str()), -1); // repeat=-1, e.g. infinite repeat every minute
   }
    else {                                              // otherwise...
      // generate the message for the sender
      String reply;
      reply = "Welcome " ;
      reply += msg.sender.username + " " + msg.sender.firstName + " " + msg.sender.lastName + " " + msg.sender.id;
///reply += ".\nTry /message, /clear, /next, /poweroff or /poweron";
      reply += ".\nTry /message, /clear or /next";

      myBot.sendMessage(msg, reply);                    // and send it
    }
  }
 else {    // Not an authorized user, send a message indicating unauthorized access
   String reply;
      reply = "NOT WELCOME:\n" ;
      reply += msg.sender.username + " " + msg.sender.firstName + " " + msg.sender.lastName + " " + msg.sender.id;
      reply += ".\nis not allowed to use this bot";
      myBot.sendMessage(msg, reply);     
       }
  }
 }
