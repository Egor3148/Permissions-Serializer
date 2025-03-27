#include "../inc/cli_interface.h"
#include "../inc/perms_serializer.h"

#include <iostream>
#include <string>

#define CHECK 1488

int run_cli()
{
	std::string help_msg = "\n__________________ PERMISSIONS SERIALIZER _______________\nOptions available:\n[0] : \tHelp (print this message)\n[1] : \tSerialize file\n[2] : \tDeserialize file\n[3] : \tExit\n";

	std::cout << help_msg << std::endl;

	bool finish = false;
	std::string password = "";
	int sorry = CHECK;	// Flag defence
	while (!finish)
	{
		char actionCode;
		std::cout << "\nChoose your action: ";
		std::cin >> actionCode;
		std::cin.ignore(LLONG_MAX, '\n');

		switch (actionCode)
		{
		case '0':
		{
			std::cout << help_msg << std::endl;
			break;
		}
		case '1':	// Serialize
		{
			std::string sourcePath;
			std::cout << "Enter file path: ";
			std::cin >> sourcePath;

			std::cout << "\nChoose password:";
			std::cin >> password;

			std::cout << "\nSerialization in progress . . .";
			int result = serialize(&sourcePath, &password);
			if (result == 1)
			{
				std::cout << "\nERROR! File not open\n";
			}
			else if (result == 2)
			{
				std::cout << "\nERROR! Encryption failed\n";
			}

			break;
		}
		case '2':	// Deserialize
		{
			std::string sourcePath;
			std::cout << "Enter source file path: ";
			std::cin >> sourcePath;

			std::cout << "\nEnter password:";
			std::cin >> password;

			std::cout << "\nDeserialization in progress . . .";
			int result = deserialize(&sourcePath, &password);
			if (result == 1)
			{
				std::cout << "\nERROR! File not open\n";
			}
			else if (result == 2)
			{
				std::cout << "\nERROR! Decryption failed\n";
			}

			break;
		}
		case '3':	// Exit
		{
			finish = true;
			break;
		}
		default:	// Something is wrong
		{
			std::cout << "\nWrong input! Enter [0] to see help\n";
		}
		}
		if (sorry != CHECK)
		{
			std::cout << "SECURITY ALERT! Stack corruption detected";
			return -1;
		}
	}

	return 0;
}
