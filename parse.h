#ifndef PARSE_H
#define PARSE_H


#include<vector>
#include<string>


void prepareStr(std::string* str);
std::string mkUpper(std::string str);
bool isValid(char chr);
void parse(std::string str, std::vector<std::string>* words);




#endif 