#pragma once
#include <string>
//getting specific word in a string
std::string  getStr(std::string mainStr, int minIndex, int maxIndex);
int getTotalWords(std::string books);
std::string replaceStr(std::string mainStr, std::string toReplace, std::string replacement, bool escapeSymbol=false);
std::string toUpperCase(std::string str);
std::string toLowerCase(std::string str);
std::string replaceText(std::string mainStr, std::string toReplace, std::string replacement);


