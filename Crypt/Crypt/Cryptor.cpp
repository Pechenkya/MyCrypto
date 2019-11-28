#include "Cryptor.h"
#include <ctime>
#include <cstdlib>

char Cryptor::crypt_key_digit(int digit)
{
	return static_cast<char>(digit + Cryptor::min_digit_value);
}

char Cryptor::crypt_char(int shift, char _char)
{
	int char_code = _char + shift;
	if (char_code > Cryptor::max_digit_value)
		return static_cast<char>(char_code - Cryptor::max_digit_value + Cryptor::min_digit_value);
	else if (char_code < Cryptor::min_digit_value)
		return static_cast<char>(char_code + Cryptor::min_digit_value);
	else
		return static_cast<char>(char_code);
}

int Cryptor::decrypt_key_digit(char _char)
{
	return _char - Cryptor::min_digit_value;
}

char Cryptor::decrypt_char(int shift, char _char)
{
	int char_code = _char - shift;
	if (char_code > Cryptor::max_digit_value)
		return static_cast<char>(char_code - Cryptor::max_digit_value);
	else if (char_code < Cryptor::min_digit_value)
		return static_cast<char>(char_code - Cryptor::min_digit_value + Cryptor::max_digit_value);
	else
		return static_cast<char>(char_code);
}

std::pair<std::string, std::string> Cryptor::crypt_message(std::string & message, std::string key)
{
	srand(time(NULL));
	const int msg_size = message.length();
	std::string crypted_msg = message;
	std::string new_key;
	if (key == "Generate key")
	{
		const int jump = msg_size % 10 + 2;
		new_key += Cryptor::crypt_key_digit(jump);

		const int sign_change = jump / 3 + 1;
		new_key += Cryptor::crypt_key_digit(sign_change);

		for (int i = 0; i < msg_size; i += jump)
		{
			int shift = rand() % Cryptor::min_digit_value;
			for (int j = i; j < i + jump && j < msg_size; j++)
			{
				int character_code = static_cast<int>(crypted_msg.at(i));
				if ((j - i) % sign_change == 0)
					crypted_msg.at(j) = Cryptor::crypt_char(shift*(-1), message.at(j));
				else
					crypted_msg.at(j) = Cryptor::crypt_char(shift, message.at(j));
			}
			new_key += Cryptor::crypt_key_digit(shift);
		}
	}
	else
	{
		new_key = key;

		const int jump = Cryptor::decrypt_key_digit(key.at(0));
		const int sign_change = Cryptor::decrypt_key_digit(key.at(1));

		for (int i = 0, k = 2; i < msg_size; i += jump, k++)
		{
			int shift = Cryptor::decrypt_key_digit(key.at(k));
			for (int j = i; j < i + jump && j < msg_size; j++)
			{
				int character_code = static_cast<int>(crypted_msg.at(i));
				if ((j - i) % sign_change == 0)
					crypted_msg.at(j) = Cryptor::crypt_char(shift*(-1), message.at(j));
				else
					crypted_msg.at(j) = Cryptor::crypt_char(shift, message.at(j));
			}
		}
	}
	return std::make_pair(crypted_msg, new_key);
}

std::string Cryptor::decrypt_message(std::string & message, std::string key)
{
	const int msg_size = message.length();
	std::string decrypted_msg = message;

	const int jump = Cryptor::decrypt_key_digit(key.at(0));
	const int sign_change = Cryptor::decrypt_key_digit(key.at(1));

	for (int i = 0, k = 2; i < msg_size; i += jump, k++)
	{
		int shift = Cryptor::decrypt_key_digit(key.at(k));
		for (int j = i; j < i + jump && j < msg_size; j++)
		{
			int character_code = static_cast<int>(decrypted_msg.at(i));
			if ((j - i) % sign_change == 0)
				decrypted_msg.at(j) = Cryptor::decrypt_char(shift*(-1), message.at(j));
			else
				decrypted_msg.at(j) = Cryptor::decrypt_char(shift, message.at(j));
		}
	}
	return decrypted_msg;
}
