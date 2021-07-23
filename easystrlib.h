#pragma once
#ifndef EASYSTRLIB_H
#define EASYSTRLIB_H

#include <string>
#include <vector>

#define _EASYSTRLIB_VER ("0.1")

std::vector<std::string> split(char* str, char delim);

std::string insert(std::string str, std::string ins, int pos);
std::string del(std::string str, int start, int end);
std::string toupper(std::string str);
std::string tolower(std::string str);

int contains(std::string str, std::string cont);
int contains(std::string str, char c);
bool startswith(std::string str, std::string start);
bool startswith(std::string str, char c);
bool endswith(std::string str, std::string start);
bool endswith(std::string str, char c);
bool isupper(char c);
bool islower(char c);

#endif // !EASYSTRLIB_H