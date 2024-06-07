#include "MarkovChain.h"

#include <algorithm>
#include <fstream>
#include <iterator>

MarkovChain::MarkovChain(const std::string &text, int k) : text(text), k(k), randomEngine(std::random_device{}()) {
    buildMarkovChain();
}

void MarkovChain::buildMarkovChain() {
    markovChain.clear();
    for (size_t i = 0; i <= text.length() - k; ++i) {
        std::string kevent = text.substr(i, k);
        std::string nextEvent = (i + k < text.length()) ? std::string(1, text[i + k]) : "";
        markovChain[kevent].push_back(nextEvent);
    }
}

int MarkovChain::freq(const std::string &kevent) const {
    auto it = markovChain.find(kevent);
    if (it == markovChain.end()) return 0;
    return it->second.size();
}

int MarkovChain::freq(const std::string &kevent, const std::string &c) const {
    auto it = markovChain.find(kevent);
    if (it == markovChain.end()) return 0;
    return std::count(it->second.begin(), it->second.end(), c);
}

std::string MarkovChain::rand(const std::string &kevent) {
    auto it = markovChain.find(kevent);
    if (it == markovChain.end() || it->second.empty()) return "";
    std::uniform_int_distribution<> dist(0, it->second.size() - 1);
    return it->second[dist(randomEngine)];
}

std::string MarkovChain::gen(const std::string &kevent, int T) {
    std::string generatedText = kevent;
    std::string currentEvent = kevent;
    while (generatedText.length() < static_cast<size_t>(T)) {
        std::string nextEvent = rand(currentEvent);
        if (nextEvent.empty()) {
            std::uniform_int_distribution<> dist(0, text.length() - k);
            int start = dist(randomEngine);
            currentEvent = text.substr(start, k);
            nextEvent = rand(currentEvent);
        }
        generatedText += nextEvent;
        currentEvent = generatedText.substr(generatedText.length() - k, k);
    }
    return generatedText;
}
