#include "Preprocessor.h"

Preprocessor::Preprocessor() {
    stopwords = {"the", "is", "are", "and", "or", "not", "to", "of", "in", "on"};
}

string Preprocessor::toLowerCase(const string &s)
{
    string result=s;
    transform(result.begin(),result.end(),result.begin(),::tolower);
    return result;
}

vector<string> Preprocessor::tokenize(const string&s)
{
    vector<string> tokens;
    string word;
    for(char c:s)
    {
        if(isalnum(c))
        {
            word.push_back(c);
        }
        else if(!word.empty())
        {
            tokens.push_back(word);
            word.clear();
        }
    }
    if(!word.empty())
    {
        tokens.push_back(word);
    }
    return tokens;
}

bool Preprocessor::isStopWord(const string &word)
{
    return stopwords.count(word) >0 ;
}

vector<string> Preprocessor::preprocessEmail(const string&text)
{
    string lowerd=toLowerCase(text);
    vector<string> tokens=tokenize(lowerd);
    vector<string> result;
    for(auto &w:tokens)
    {
        if(!isStopWord(w))
        {
            result.push_back(w);
        }
    }
    return result;
}