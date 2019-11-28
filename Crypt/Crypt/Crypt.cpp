#include <iostream>
#include <string>
#include "Cryptor.h"

int main()
{
	while (true)
	{
		char input;
		std::string message;
		std::cout << "What do you want to do?" << std::endl;
		std::cout << "E - encrypt" << std::endl;
		std::cout << "D - decrypt" << std::endl;
		std::cin >> input;
		if (toupper(input) == 'D')
		{
			std::string decryption_result;
			std::string key;
			system("CLS");
			std::cin.ignore();
			std::cout << "Enter message to Decrypt: " << std::endl;
			std::getline(std::cin, message);
			std::cout << "Enter encryption key: " << std::endl;
			std::getline(std::cin, key);
			system("CLS");
			decryption_result = Cryptor::decrypt_message(message, key);
			std::cout << "Decrypted message: " << decryption_result << std::endl;
		}
		else if (toupper(input) == 'E')
		{
			std::pair<std::string, std::string> encryption_result;
			system("CLS");
			std::cin.ignore();
			std::cout << "Enter message to Encrypt: " << std::endl;
			std::getline(std::cin, message);
			system("CLS");
			std::cout << "You want to generate key automaticly?" << std::endl;
			std::cout << "Y|N" << std::endl;
			std::cin >> input;
			if (toupper(input) == 'Y')
			{
				encryption_result = Cryptor::crypt_message(message);
			}
			else if(toupper(input) == 'N')
			{
				std::cin.ignore();
				std::cout << "Enter encryption key: " << std::endl;
				std::string key;
				std::getline(std::cin, key);
				encryption_result = Cryptor::crypt_message(message, key);
			}
			system("CLS");
			std::cout << "Encrypted message: " << encryption_result.first << std::endl;
			std::cout << "Encryption key: " << encryption_result.second << std::endl;
		}
		system("Pause");
		system("CLS");
	}
}
