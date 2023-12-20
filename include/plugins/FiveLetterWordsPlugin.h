#pragma once
#include <vector>
#include <string>
#include "PluginManager.h"
//#include <unordered_set>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include "FiveLetterWordsConstants.h"


class FiveLetterWordsPlugin : public Plugin {
private:
  //  std::unordered_set<std::string> wordList;
  //  void addWord(const std::string& word);
  //  void removeWord(const std::string& word);
  //  bool searchWord(const std::string& word) const;
    std::string getRandomWord();
    int previousMs;


public:
    FiveLetterWordsPlugin();

    void setup() override;
    void loop() override;
    const char* getName() const override;

    void teardown() override; // optional
    void websocketHook(DynamicJsonDocument &request) override; // optional
};
