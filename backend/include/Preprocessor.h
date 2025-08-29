#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include<bits/stdc++.h>
using namespace std;

class Preprocessor {
private:
    unordered_set<string> stopwords;

public:
    Preprocessor();

    string toLowerCase(const string &s);
    vector<string> tokenize(const string &s);
    bool isStopWord(const string &word);
    vector<string> preprocessEmail(const string &text);
};

#endif
