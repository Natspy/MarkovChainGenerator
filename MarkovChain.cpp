#include "MarkovChain.h"

#include <algorithm>
#include <fstream>
#include <iterator>

using namespace std;

MarkovChain::MarkovChain(const string &text, int k) : text(text), k(k), randomEngine(random_device{}()) {
    buildMarkovChain();
}

void MarkovChain::buildMarkovChain() {
    markovChain.clear();
    for (size_t i = 0; i <= text.length() - k; ++i) {
        string kevent = text.substr(i, k);
        string nextEvent = (i + k < text.length()) ? string(1, text[i + k]) : "";
        markovChain[kevent].push_back(nextEvent);
    }
}

string MarkovChain::rand(const string &kevent) {
    auto it = markovChain.find(kevent);
    if (it == markovChain.end() || it->second.empty()) return "";
    uniform_int_distribution<> dist(0, it->second.size() - 1);
    return it->second[dist(randomEngine)];
}

string MarkovChain::gen(const string &kevent, int T) {
    string generatedText = kevent;
    string currentEvent = kevent;
    while (generatedText.length() < static_cast<size_t>(T)) {
        string nextEvent = rand(currentEvent);
        if (nextEvent.empty()) {
            uniform_int_distribution<> dist(0, text.length() - k);
            int start = dist(randomEngine);
            currentEvent = text.substr(start, k);
            nextEvent = rand(currentEvent);
        }
        generatedText += nextEvent;
        currentEvent = generatedText.substr(generatedText.length() - k, k);
    }
    return generatedText;
}