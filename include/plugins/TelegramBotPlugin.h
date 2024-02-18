#pragma once
#include <vector>
#include <string>
////#include <UniversalTelegramBot.h> // Include the UniversalTelegramBot library
#include <AsyncTelegram2.h>
#include "PluginManager.h"
#include <WiFiClientSecure.h>  // Include WiFiClientSecure library for secure connection

#ifdef ENABLE_SERVER


class TelegramBotPlugin : public Plugin {
private:
    WiFiClientSecure client;
    AsyncTelegram2 myBot;
    String lastMessage;
    TBMessage msg;
    bool awaitingMessage = false;
    std::vector<int> authorizedUserIds; // Vector for dynamic IDs
    std::vector<std::string> authorizedUsernames; // Vector for dynamic names
    bool isAuthorized = false;

public:

    void setup() override;
    void loop() override;
    const char* getName() const override;
    void teardown() override; // optional
    void websocketHook(DynamicJsonDocument &request) override; // optional
    void handleIncomingMessages(TBMessage msg);
        TelegramBotPlugin();

};
#endif