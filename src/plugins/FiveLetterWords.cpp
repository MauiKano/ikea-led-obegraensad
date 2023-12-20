#include "plugins/FiveLetterWordsPlugin.h"
#include "plugins/FiveLetterWordsConstants.h"
#include "messages.h"

FiveLetterWordsPlugin::FiveLetterWordsPlugin() {
    // Loop to add words from constants to the wordList
   // for (const auto& word : WordConstants::words) {
   //     wordList.insert(word);
   // }
    // Example: Searching for a word
    //std::cout << "Searching for 'banana': " << std::boolalpha << wp.searchWord("banana") << std::endl;

    // Example: Removing a word
    //wp.removeWord("orange");

    // Example: Printing all words
    //wp.printWords();
}

void FiveLetterWordsPlugin::setup() {
        previousMs = 0;
    // Setup logic for your plugin
}

void FiveLetterWordsPlugin::loop() {

        // Check if the current minute is different from the previous minute
        if ((millis() - previousMs) > 4000) // wait at least 3 seconds between displaying words
        {
           Messages.add(getRandomWord());
           previousMs = millis();
        } 
}

const char* FiveLetterWordsPlugin::getName() const {
    return "FiveLetterWordsPlugin"; // name in GUI
}

void FiveLetterWordsPlugin::teardown() {
  // code if plugin gets deactivated
}

void FiveLetterWordsPlugin::websocketHook(DynamicJsonDocument &request) {
  // handle websocket requests
}

/*
void FiveLetterWordsPlugin::addWord(const std::string& word) {
    wordList.insert(word);
}

void FiveLetterWordsPlugin::removeWord(const std::string& word) {
    wordList.erase(word);
}

bool FiveLetterWordsPlugin::searchWord(const std::string& word) const {
    return (wordList.find(word) != wordList.end());
}
*/

/*
std::string FiveLetterWordsPlugin::getRandomWord() {
        if (wordList.empty()) {
            return "No words available.";
        }

        // Seed the random number generator
        std::srand(static_cast<unsigned int>(std::time(nullptr)));

        // Generate a random index within the size of the set
        int randomIndex = std::rand() % wordList.size();

        // Iterate to the random index to retrieve the word
        auto it = wordList.begin();
        std::advance(it, randomIndex);

        return *it;
    }
*/
   std::string FiveLetterWordsPlugin::getRandomWord() {
        int numWords = sizeof(WordConstants::wordList) / sizeof(WordConstants::wordList[0]);

        // Seed the random number generator
        std::srand(static_cast<unsigned int>(std::time(nullptr)));

        // Generate a random index within the size of the wordList array
        int randomIndex = std::rand() % numWords;

        // Retrieve the word pointer from PROGMEM using the random index
        const char* wordPtr = reinterpret_cast<const char*>(pgm_read_ptr(&WordConstants::wordList[randomIndex]));

        char buffer[50]; // Adjust the size as needed
        strcpy_P(buffer, wordPtr);

        return std::string(buffer);
    }

/*
void FiveLetterWordsPlugin::printWords() const {
    std::cout << "Words in the list:" << std::endl;
    for (const auto& word : wordList) {
        std::cout << word << std::endl;
    }
}
*/