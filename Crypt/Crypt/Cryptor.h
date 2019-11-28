#pragma once
#include<fstream>
#include<string>
#include<utility>

class Cryptor
{
	static const int max_digit_value = 126;
	static const int min_digit_value = 32;
	static char crypt_key_digit(int digit);
	static char crypt_char(int shift, char _char);
	static int decrypt_key_digit(char _char);
	static char decrypt_char(int shift, char _char);

public:

	static std::pair<std::string, std::string> crypt_message(std::string& message, std::string key = "Generate key");
	static std::string decrypt_message(std::string& message, std::string key);
};

