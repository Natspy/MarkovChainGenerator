#ifndef MARKOVCHAIN_H
#define MARKOVCHAIN_H

#include <string>
#include <unordered_map>
#include <vector>
#include <random>

using namespace std;

class MarkovChain {
public:
    MarkovChain(const string &text, int k);
    int freq(const string &kevent) const;
    int freq(const string &kevent, const string &c) const;
    string rand(const string &kevent);
    string gen(const string &kevent, int T);

private:
    void buildMarkovChain();
    string text;
    int k;
    unordered_map<std::string, vector<string>> markovChain;
    default_random_engine randomEngine;
};

#endif //MARKOVCHAIN_H
