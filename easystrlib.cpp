#include <string>
#include <vector>
#include "easystrlib.h"

std::vector<std::string> split(char* str, char delim)
{
	size_t len = strlen(str);
	std::vector<std::string> result;
	std::string buffer;

	for (int i = 0; i < len; i++)
	{
		if (str[i] != delim) buffer += str[i];
		else
		{
			result.push_back(buffer);
			buffer.clear();
		}
	}

	result.push_back(buffer);

	return result;
}

int contains(std::string str, char c)
{
	int count = 0;

	for (size_t i = 0; i < str.length(); i++) if (str[i] == c) count++;

	return count;
}

int contains(std::string str, std::string cont)
{
	std::string buf;
	int count = 0;

	for (size_t i = 0; i < str.length(); i++)
	{
		buf.clear();
		for (size_t j = 0; j < cont.length(); j++) buf += str[i + j];

		if (buf == cont) count++;
	}

	return count;
}

bool isupper(char c)
{
	return (c >= 65 && c <= 90);
}

bool islower(char c)
{
	return (c >= 97 && c <= 122);
}

bool startswith(std::string str, char c)
{
	return str[0] == c;
}

bool startswith(std::string str, std::string start)
{
	std::string buf;
	for (int i = 0; i < start.length(); i++) buf += str[i];
	return buf == start;
}

bool endswith(std::string str, char c)
{
	return str[str.length() - 1] == c;
}

bool endswith(std::string str, std::string end)
{
	std::string buf;
	for (int i = str.length() - end.length(); i < str.length(); i++) buf += str[i];
	return buf == end;
}

std::string toupper(std::string str)
{
	char* buf = (char*)str.c_str();

	for (int i = 0; i < str.length(); i++)
	{
		if (islower(str[i])) buf[i] = (char)(str[i] - 32);
		else if (isupper(str[i])) buf[i] = str[i];
		else buf[i] = str[i];
	}

	return std::string(buf);
}

std::string tolower(std::string str)
{
	char* buf = (char*)str.c_str();

	for (int i = 0; i < str.length(); i++)
	{
		if (isupper(str[i])) buf[i] = (char)(str[i] + 32);
		else if (islower(str[i])) buf[i] = str[i];
		else buf[i] = str[i];
	}

	return std::string(buf);
}

std::string del(std::string str, int start, int end)
{
	std::string buf;

	for (size_t i = 0; i < str.length(); i++) if (i < start || i > end) buf += str[i];
	return buf;
}

std::string insert(std::string str, std::string ins, int pos)
{
	std::string buf;

	for (size_t i = 0; i < str.length(); i++)
	{
		if (i != pos) buf += str[i];
		else
		{
			buf += ins;

		}
	}

	return buf;
}