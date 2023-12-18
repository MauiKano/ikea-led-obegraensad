#pragma once
#include <vector>
#include <string>
////#include <UniversalTelegramBot.h> // Include the UniversalTelegramBot library
#include <AsyncTelegram2.h>
#include "PluginManager.h"
#include <WiFiClientSecure.h>  // Include WiFiClientSecure library for secure connection



class TelegramBotPlugin : public Plugin {
private:
    WiFiClientSecure client;
    AsyncTelegram2 myBot;
    String lastMessage;
    TBMessage msg;

public:

    void setup() override;
    void loop() override;
    const char* getName() const override;
    void teardown() override; // optional
    void websocketHook(DynamicJsonDocument &request) override; // optional
    void handleIncomingMessages(TBMessage msg);
        TelegramBotPlugin();

};