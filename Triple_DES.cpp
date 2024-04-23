#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "DES.h"
#include "Triple_DES.h"

//these following two functions are for using with terminal input output,
// now I changed scheme and I will give functions input,output path and key
// as arguments
//void encryption_with_Triple_DES()
//{
//	std::string input_pathname;
//	std::string output_pathname;
//	std::cout << "input file pathname for encryption" << std::endl;
//	std::cin >> input_pathname;
//	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//	//std::cout << "inputed pathname - " << input_pathname << std::endl;
//	std::cout << "output file pathname for encrypted ciphertext" << std::endl;
//
//	std::cin >> output_pathname;
//	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//
//	Triple_DES_encryption_helper(input_pathname, output_pathname);
//}
//
//void decryption_with_Triple_DES()
//{
//	std::string input_pathname;
//	std::string output_pathname;
//	std::cout << "input file pathname for decryption the cyphertext" << std::endl;
//	std::cin >> input_pathname;
//	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//	//std::cout << "inputed pathname - " << input_pathname << std::endl;
//	std::cout << "output file pathname for decrypted text" << std::endl;
//
//	std::cin >> output_pathname;
//	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//
//	Triple_DES_decryption_helper(input_pathname, output_pathname);
//}


void Triple_DES_encrypt(std::string input, std::string output, std::string key_1,
	std::string key_2, std::string key_3)
{
	unsigned char key1[9], key2[9], key3[9];
	key1[8] = 0, key2[8] = 0, key3[8] = 0;
	//std::cout << "input key 1" << std::endl;
	//key_input(key1);
	//std::cout << "key1 = " << key1 << std::endl;
	//std::cout << "input key 2" << std::endl;
	//key_input(key2);
	//std::cout << "key2 = " << key2 << std::endl;
	//std::cout << "input key 3" << std::endl;
	//key_input(key3);
	//std::cout << "key3 = " << key3 << std::endl;

	key_making_char(key1, key_1);
	key_making_char(key2, key_2);
	key_making_char(key3, key_3);

	std::ifstream inputFile(input, std::ios::binary); // Open input file with its full path
	std::ofstream outputFile(output, std::ios::binary); // Open output file with its full pat

	if (!inputFile) {
		std::cerr << "Error opening input file." << std::endl;
		return;
	}
	if (!outputFile) {
		std::cerr << "Error opening output file." << std::endl;
		return;
	}

	unsigned char buffer[9];

	unsigned char dest[65];
	dest[64] = 0;
	char buffer_char[9];

	while (inputFile.read(buffer_char, 8)) { // Read 8 bytes at a time
		buffer_char[8] = '\0'; // Null terminate the buffer
		for (int i = 0; i < 8; i++)
			buffer[i] = (unsigned char)buffer_char[i];

		DES(buffer, dest, key1);
		DES_decryption_helper(dest, buffer, key2);
		DES(buffer, dest, key3);
		outputFile << dest; // Write the buffer to the output file
	}

	inputFile.close();
	outputFile.close();

	/*std::cout << "key1 = " << key1 << std::endl;
	std::cout << "key2 = " << key2 << std::endl;
	std::cout << "key3 = " << key3 << std::endl;*/

	std::cout << "Data encrypted successfully." << std::endl;
}


void Triple_DES_decrypt(std::string input, std::string output, std::string key_1,
	std::string key_2, std::string key_3)
{
	unsigned char key1[9], key2[9], key3[9];
	key1[8] = 0, key2[8] = 0, key3[8] = 0;
	//std::cout << "input key 1" << std::endl;
	//key_input(key1);
	//std::cout << "input key 2" << std::endl;
	//key_input(key2);
	//std::cout << "input key 3" << std::endl;
	//key_input(key3);

	/*std::cout << "key1 = " << key1 << std::endl;
	std::cout << "key2 = " << key2 << std::endl;
	std::cout << "key3 = " << key3 << std::endl;*/

	key_making_char(key1, key_1);
	key_making_char(key2, key_2);
	key_making_char(key3, key_3);

	std::ifstream inputFile(input, std::ios::binary); // Open input file with its full path
	std::ofstream outputFile(output, std::ios::binary); // Open output file with its full pat

	if (!inputFile) {
		std::cerr << "Error opening input file." << std::endl;
		return;
	}
	if (!outputFile) {
		std::cerr << "Error opening output file." << std::endl;
		return;
	}

	unsigned char buffer[65];

	unsigned char dest[9];
	dest[8] = 0;
	char buffer_char[65];

	while (inputFile.read(buffer_char, 64)) { // Read 8 bytes at a time
		buffer_char[64] = '\0'; // Null terminate the buffer
		for (int i = 0; i < 64; i++)
			buffer[i] = (unsigned char)buffer_char[i];

		DES_decryption_helper(buffer, dest, key3);
		DES(dest, buffer, key2);
		DES_decryption_helper(buffer, dest, key1);

		outputFile << dest; // Write the buffer to the output file
	}

	inputFile.close();
	outputFile.close();

	/*std::cout << "key1 = " << key1 << std::endl;
	std::cout << "key2 = " << key2 << std::endl;
	std::cout << "key3 = " << key3 << std::endl;*/

	std::cout << "Data decrypted successfully." << std::endl;
}







void key_making_char(unsigned char key[], std::string string_key)
{
	for (int i = 0; i < 8; i++)
	{
		key[i] = static_cast<unsigned char>(string_key[i]);
	}
	//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}