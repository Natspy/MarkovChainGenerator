#ifndef MARKOVCHAIN_H
#define MARKOVCHAIN_H

#include <string>
#include <unordered_map>
#include <vector>
#include <random>

class MarkovChain {
public:
    MarkovChain(const std::string &text, int k);
    int freq(const std::string &kevent) const;
    int freq(const std::string &kevent, const std::string &c) const;
    std::string rand(const std::string &kevent);
    std::string gen(const std::string &kevent, int T);

private:
    void buildMarkovChain();
    std::string text;
    int k;
    std::unordered_map<std::string, std::vector<std::string>> markovChain;
    std::default_random_engine randomEngine;
};

#endif //MARKOVCHAIN_H
