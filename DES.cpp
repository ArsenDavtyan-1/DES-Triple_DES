#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <istream>
#include <ostream>
#include "DES.h"


// for keys
int pc1[56] = {
57,49,41,33,25,17,9,
1,58,50,42,34,26,18,
10,2,59,51,43,35,27,
19,11,3,60,52,44,36,
63,55,47,39,31,23,15,
7,62,54,46,38,30,22,
14,6,61,53,45,37,29,
21,13,5,28,20,12,4
};
int pc2[48] = {
14,17,11,24,1,5,
3,28,15,6,21,10,
23,19,12,4,26,8,
16,7,27,20,13,2,
41,52,31,37,47,55,
30,40,51,45,33,48,
44,49,39,56,34,53,
46,42,50,36,29,32
};
// until here is for keys

// for plaintext
int initial_permutation[64] = {
58,50,42,34,26,18,10,2,
60,52,44,36,28,20,12,4,
62,54,46,38,30,22,14,6,
64,56,48,40,32,24,16,8,
57,49,41,33,25,17,9,1,
59,51,43,35,27,19,11,3,
61,53,45,37,29,21,13,5,
63,55,47,39,31,23,15,7
};


int inverse_permutation[64] = {
40,8,48,16,56,24,64,32,
39,7,47,15,55,23,63,31,
38,6,46,14,54,22,62,30,
37,5,45,13,53,21,61,29,
36,4,44,12,52,20,60,28,
35,3,43,11,51,19,59,27,
34,2,42,10,50,18,58,26,
33,1,41,9,49,17,57,25
};

int expansion_table[48] = {
32,1,2,3,4,5,4,5,
6,7,8,9,8,9,10,11,
12,13,12,13,14,15,16,17,
16,17,18,19,20,21,20,21,
22,23,24,25,24,25,26,27,
28,29,28,29,30,31,32,1
};


int substition_boxes[8][4][16] =
{ {
14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,
4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13
},
{
15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,
3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,
0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,
13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9
},
{
10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,
13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,
13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,
1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12
},
{
7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,
13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,
10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,
3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14
},
{
2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,
14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,
4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,
11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3
},
{
12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,
10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,
9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,
4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13
},
{
4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,
13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,
1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,
6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12
},
{
13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,
1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,
7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,
2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11
} };
int permutation_box[32] = {
16,7,20,21,29,12,28,17,
1,15,23,26,5,18,31,10,
2,8,24,14,32,27,3,9,
19,13,30,6,22,11,4,25
};

// unti here is for plaintext

void char_to_binary(unsigned char array[], unsigned char key[], int size)
{
	for (int i = 0; i < size; i++)
	{
		int n = (int)key[i];
		for (int j = 0; j < 8; j++) {
			if ((n & 1) == 1)
			{
				array[(i + 1) * 8 - j - 1] = '1';
			}
			else {
				array[(i + 1) * 8 - j - 1] = '0';
			}
			n >>= 1;
		}
	}
}

void key_pc1(unsigned char binary_key[], unsigned char key_aft_pc1[])
{
	for (int i = 0; i < 56; i++)
	{
		key_aft_pc1[i] = binary_key[pc1[i] - 1];
	}
}

void left_shift_one(unsigned char half_key[])
{
	unsigned char temp = half_key[0];
	for (int i = 1; i < 28; i++)
	{
		half_key[i - 1] = half_key[i];
	}
	half_key[27] = temp;
}

void left_shift_two(unsigned char half_key[])
{
	unsigned char temp1 = half_key[0], temp2 = half_key[1];
	for (int i = 2; i < 28; i++)
	{
		half_key[i - 2] = half_key[i];
	}
	half_key[26] = temp1;
	half_key[27] = temp2;
}



void key_pc2(unsigned char subkey[], unsigned char left_half[], unsigned char right_half[])
{
	for (int i = 0; i < 24; i++)
	{
		subkey[i] = left_half[pc2[i] - 1];
		subkey[i + 24] = right_half[pc2[i + 24] - 28 - 1];
	}
}
void XOR_char(unsigned char first[], unsigned char second[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (first[i] == second[i])
		{
			first[i] = '0';
		}
		else
		{
			first[i] = '1';
		}
	}
}

void init_perm(unsigned char plaintext[], unsigned char plain_aft_init[])
{
	for (int i = 0; i < 64; i++)
	{
		plain_aft_init[i] = plaintext[initial_permutation[i] - 1];
	}
}

int binary_to_decimal(unsigned char a, unsigned char b)
{
	int sum = 0;
	if (a == '1')
		sum += 2;
	if (b == '1')
		sum += 1;
	return sum;
}

int binary_to_decimal(unsigned char arr[], int start_position)
{
	int a = 1;
	int sum = 0;
	for (int index = 3; index >= 0; index--) {
		if (arr[start_position + index] == '1')
		{
			sum += a;
		}
		a *= 2;
	}
	return sum;
}



void decimal_to_binary(unsigned char array[], int start_position, int val)
{
	for (int index = 3; index >= 0; index--) {
		if (val % 2 == 1)
		{
			array[start_position + index] = '1';
		}
		else
		{
			array[start_position + index] = '0';
		}
		val /= 2;
	}
}




void DES_round(unsigned char left_half[], unsigned char right_half[], unsigned char subkey[])
{
	unsigned char expanded[48];
	for (int i = 0; i < 48; i++)
	{
		expanded[i] = right_half[expansion_table[i] - 1];
	}
	XOR_char(expanded, subkey);
	unsigned char aft_sub[32];
	for (int i = 0; i < 8; i++)
	{
		int row = binary_to_decimal(expanded[i * 6], expanded[i * 6 + 5]);
		int col = binary_to_decimal(expanded, i * 6 + 1);
		int val = substition_boxes[i][row][col];
		decimal_to_binary(aft_sub, i * 4, val);
	}
	for (int i = 0; i < 32; i++)
	{
		expanded[i] = aft_sub[permutation_box[i] - 1];          // don't making another array,using expanded 
	}
	XOR_char(expanded, left_half, 32); // don't creating new array
	for (int i = 0; i < 32; i++)
	{
		left_half[i] = right_half[i];
		right_half[i] = expanded[i];
	}

}


void making_char_key_to_binary(unsigned char key[], unsigned char binary_key[], int size)
{
	for (int i = 0; i < size; i++)
	{
		making_char_binary(key[i], binary_key, i * 8);
	}
}

void making_char_binary(unsigned char a, unsigned char destination[], int start_position)
{
	int b = int(a);
	for (int i = 0; i < 8; i++)
	{
		if (b % 2 == 1)
		{
			destination[start_position + 7 - i] = '1';
		}
		else
		{
			destination[start_position + 7 - i] = '0';
		}
		b /= 2;
	}
}


unsigned char making_binary_to_char(unsigned char binary[], int start_position)
{
	int val = 0;
	int a = 1;
	for (int i = 7; i >= 0; i--)
	{
		if (binary[start_position + i] == '1')
		{
			val += a;
		}
		a *= 2;
	}
	unsigned char b = unsigned char(val);
	return b;
}


void making_binary_ciphertext_to_char(unsigned char binary_ciphertext[], unsigned char char_ciphertext[], int size)
{
	for (int i = 0; i < size; i++)
	{
		char_ciphertext[i] = making_binary_to_char(binary_ciphertext, i * 8);
	}
}


void DES_encrypt(std::string input, std::string output, std::string key_1)
{

	unsigned char key[9];
	key[8] = 0;
	/*std::cout << "input char key" << std::endl;
	for (int i = 0; i < 8; i++)
	{
		std::cin >> key[i];
	}*/
	for (int i = 0; i < 8; i++)
	{
		key[i] = static_cast<unsigned char>(key_1[i]);
	}
	//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	// for test
	//key[8] = 0;
	//key[0] = unsigned char(19), key[1] = unsigned char(52), key[2] = unsigned char(87);
	//key[3] = unsigned char(121), key[4] = unsigned char(155);
	//key[5] = unsigned char(188), key[6] = unsigned char(223), key[7] = unsigned char(241);
	std::cout << "key - " << key << std::endl;
	unsigned char buffer[9];
	// for test
	/*buffer[8] = 0;
	buffer[0] = unsigned char(1), buffer[1] = unsigned char(35);
	buffer[2] = unsigned char(69), buffer[3] = unsigned char(103), buffer[4] = unsigned char(137);
	buffer[5] = unsigned char(171), buffer[6] = unsigned char(205), buffer[7] = unsigned char(239);*/
	//std::string input = R"(C:\Users\HP\Desktop\test_for_DES.txt)";
	//std::string output = R"(C:\Users\HP\Desktop\Dest.txt)";
	std::ifstream inputFile(input, std::ios::binary); // Open input file with its full path
	std::ofstream outputFile(output, std::ios::binary); // Open output file with its full path
	/*if (inputFile)
	{
		std::cout << "input file is open for encryption" << std::endl;
	}*/
	if (!inputFile) {
		std::cerr << "Error opening input file." << std::endl;
		return;
	}

	/*if (inputFile)
	{
		std::cout << "output file is open for encryption" << std::endl;
	}*/

	if (!outputFile) {
		std::cerr << "Error opening output file." << std::endl;
		return;
	}

	unsigned char dest[65];
	dest[64] = 0;
	char buffer_char[9];

	//for test
	/*std::cout << "text - " << buffer << std::endl;
	std::cout << "key - " << key << std::endl;
	DES(buffer, dest, key);
	std::cout << "cipher - " << dest << std::endl;*/
	buffer_char[8] = 0;
	while (inputFile.read(buffer_char, 8)) { // Read 8 bytes at a time
		buffer_char[8] = '\0'; // Null terminate the buffer

		for (int i = 0; i < 8; i++)
			buffer[i] = static_cast<unsigned char>(buffer_char[i]);

		DES(buffer, dest, key);
		dest[64] = 0;
		buffer[8] = 0;



		outputFile << dest; // Write the buffer to the output file
		//std::cout << "buffer - " << buffer << std::endl;
		//std::cout << "(after_encrypt) - " << dest << std::endl;
		//std::cout << "(after_making_char) - " << test_dest << std::endl;
		//std::cout << "(key)-" << key << std::endl;
		//std::cout << std::endl;
	}
	inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	inputFile.close();
	outputFile.close();

	std::cout << "Data encrypted successfully." << std::endl;


}



void print_subkeys(unsigned char subkey[][48])
{
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 48; j++)
		{
			if (j == 24) std::cout << " ";
			std::cout << subkey[i][j];
		}
		std::cout << std::endl;
	}
}

void DES(unsigned char plaintext_char[], unsigned char ciphertext_binary[], unsigned char key[], int size) //plaintext need to be char[64]
{

	/*std::cout << "plaintext - ";
	for (int i = 0; i < size; i++)
	{
		std::cout << plaintext_char[i];
	}
	std::cout << std::endl;*/

	unsigned char plaintext[65];
	plaintext[64] = 0;
	making_char_key_to_binary(plaintext_char, plaintext);
	/*std::cout << "char plaintext - " << plaintext_char << std::endl;
	std::cout << "binary plaintext - " << plaintext << std::endl;*/
	//std::cout << "binary plaintext - " << plaintext << std::endl;


	// key part

	unsigned char binary_key[65];
	binary_key[64] = 0;
	making_char_key_to_binary(key, binary_key);
	/*std::cout << "key - " << key << std::endl;
	std::cout << "binary key - " << binary_key << std::endl;*/


	unsigned char key_aft_pc1[57];
	key_aft_pc1[56] = 0;
	key_pc1(binary_key, key_aft_pc1);
	/*std::cout << "key after pc1 - " << key_aft_pc1 << std::endl << std::endl << std::endl;
	std::cout << "printing subkeys for each round " << std::endl;*/
	unsigned char subkeys[16][48];
	unsigned char left_key[28], right_key[28];
	for (int i = 0; i < 28; i++)
	{
		left_key[i] = key_aft_pc1[i];
		right_key[i] = key_aft_pc1[i + 28];
	}
	for (int i = 0; i < 16; i++)
	{
		if (i == 0 || i == 1 || i == 8 || i == 15)
		{
			left_shift_one(left_key);
			left_shift_one(right_key);
		}
		else
		{
			left_shift_two(left_key);
			left_shift_two(right_key);
		}
		unsigned char left_key_for_pc2[28];
		unsigned char right_key_for_pc2[28];
		for (int i = 0; i < 28; i++)
		{
			left_key_for_pc2[i] = left_key[i];
			right_key_for_pc2[i] = right_key[i];
		}
		key_pc2(subkeys[i], left_key_for_pc2, right_key_for_pc2);
	}
	//print_subkeys(subkeys);
	//std::cout << std::endl << std::endl << std::endl;
	// key part over




	unsigned char aft_init_perm[65];
	aft_init_perm[64] = 0;

	init_perm(plaintext, aft_init_perm);
	//std::cout << "plaintext after init perm - " << aft_init_perm << std::endl;
	unsigned char left_plaintext[32], right_plaintext[32];
	for (int i = 0; i < 32; i++)
	{
		left_plaintext[i] = aft_init_perm[i];
		right_plaintext[i] = aft_init_perm[i + 32];
	}
	//std::cout << "left part before round - ";
	//printing_half_plaintext(left_plaintext);
	//std::cout << "right part before round - ";
	//printing_half_plaintext(right_plaintext);
	//std::cout << std::endl;


	for (int i = 0; i < 16; i++)
	{
		DES_round(left_plaintext, right_plaintext, subkeys[i]);
	}

	for (int i = 0; i < 32; i++)
	{
		plaintext[i] = right_plaintext[i];
		plaintext[i + 32] = left_plaintext[i];
	}
	//std::cout << "plaitext after rounds and swaping - " << plaintext << std::endl;
	unsigned char* ciphertext = aft_init_perm;
	for (int i = 0; i < 64; i++)
	{
		ciphertext[i] = plaintext[inverse_permutation[i] - 1];
	}


	for (int i = 0; i < size; i++)
		ciphertext_binary[i] = ciphertext[i];


	//std::cout << "ciphertext after inverse permutation - " << ciphertext << std::endl;
	//std::cout << std::endl << "binary ciphertext - " << ciphertext << std::endl;
	//making_binary_ciphertext_to_char(ciphertext, ciphertext_char); // wrong,changing scheme
	//std::cout << "That ciphertext after making char - " << ciphertext_char << std::endl;
	/*std::cout << "ciphertext - ";
	for (int i = 0; i < 8; i++)
	{
		std::cout << ciphertext_char[i];
	}
	std::cout << std::endl;*/
}



void DES_decryption_helper(unsigned char binary_cipher[], unsigned char char_plain[], unsigned char key[])
{
	//unsigned char cipher[65];
	//cipher[64] = 0;
	//making_char_key_to_binary(char_cipher, cipher); will cause problems,changed scheme
	//std::cout << "binary ciphertext - " << cipher << std::endl;
	unsigned char binary_key[65];
	binary_key[64] = 0;
	making_char_key_to_binary(key, binary_key);
	//std::cout << "binary key - " << binary_key << std::endl;
	unsigned char key_aft_pc1[57];
	key_aft_pc1[56] = 0;
	key_pc1(binary_key, key_aft_pc1);
	//std::cout << "key after perm choice 2 - " << key_aft_pc1 << std::endl;

	unsigned char subkeys[16][48];
	unsigned char left_key[28], right_key[28];
	for (int i = 0; i < 28; i++)
	{
		left_key[i] = key_aft_pc1[i];
		right_key[i] = key_aft_pc1[i + 28];
	}
	for (int i = 0; i < 16; i++)
	{
		if (i == 0 || i == 1 || i == 8 || i == 15)
		{
			left_shift_one(left_key);
			left_shift_one(right_key);
		}
		else
		{
			left_shift_two(left_key);
			left_shift_two(right_key);
		}
		unsigned char left_key_for_pc2[28];
		unsigned char right_key_for_pc2[28];
		for (int i = 0; i < 28; i++)
		{
			left_key_for_pc2[i] = left_key[i];
			right_key_for_pc2[i] = right_key[i];
		}
		key_pc2(subkeys[i], left_key_for_pc2, right_key_for_pc2);
	}

	unsigned char aft_init_perm[65];
	aft_init_perm[64] = 0;
	init_perm(binary_cipher, aft_init_perm);
	//std::cout << "ciphertext after init perm - " << aft_init_perm << std::endl;
	unsigned char left_plaintext[32], right_plaintext[32];
	for (int i = 0; i < 32; i++)
	{
		left_plaintext[i] = aft_init_perm[i];
		right_plaintext[i] = aft_init_perm[i + 32];
	}

	for (int i = 0; i < 16; i++)
	{
		DES_round(left_plaintext, right_plaintext, subkeys[15 - i]);
	}

	for (int i = 0; i < 32; i++)
	{
		binary_cipher[i] = right_plaintext[i];
		binary_cipher[i + 32] = left_plaintext[i];
	}
	unsigned char* ciphertext = aft_init_perm;
	for (int i = 0; i < 64; i++)
	{
		ciphertext[i] = binary_cipher[inverse_permutation[i] - 1];
	}

	//std::cout << "binary plaintext - " << ciphertext << std::endl;
	making_binary_ciphertext_to_char(ciphertext, char_plain);
}

void DES_decrypt(std::string input, std::string output, std::string key_1)
{
	unsigned char key[9];
	key[8] = 0;
	//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	//std::cout << "input char key" << std::endl;
	/*for (int i = 0; i < 8; i++)
	{
		std::cin >> key[i];
	}*/
	for (int i = 0; i < 8; i++)
	{
		key[i] = static_cast<unsigned char>(key_1[i]);
	}
	//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	std::cout << "key - " << key << std::endl;

	unsigned char buffer[65];
	buffer[64] = 0;

	//std::string input = R"(C:\Users\HP\Desktop\Dest.txt)";;
	//std::string output = R"(C:\Users\HP\Desktop\decr_test.txt)";
	std::ifstream inputFile(input, std::ios::binary); // Open input file with its full path
	std::ofstream outputFile(output, std::ios::binary); // Open output file with its full path

	/*if (inputFile) {
		std::cout << " for decryption file is open" << std::endl;
	}*/
	if (!inputFile) {
		std::cerr << "Error opening input file." << std::endl;
		return;
	}

	/*if (outputFile) {
		std::cout << " outputFile file is open" << std::endl;
	}*/

	if (!outputFile) {
		std::cerr << "Error opening output file." << std::endl;
		return;
	}
	//For testing
	/*key[8] = 0;
	key[0] = unsigned char(19), key[1] = unsigned char(52), key[2] = unsigned char(87);
	key[3] = unsigned char(121), key[4] = unsigned char(155);
	key[5] = unsigned char(188), key[6] = unsigned char(223), key[7] = unsigned char(241);
	std::cout << "key - " << key << std::endl;
	buffer[8] = 0;
	buffer[0] = unsigned char(133), buffer[1] = unsigned char(232);
	buffer[2] = unsigned char(19), buffer[3] = unsigned char(84), buffer[4] = unsigned char(15);
	buffer[5] = unsigned char(10), buffer[6] = unsigned char(180), buffer[7] = unsigned char(5);*/
	unsigned char dest[9];
	dest[8] = 0;
	//std::cout << "ciphertext - " << buffer << std::endl;
	char buffer_char[65];


	while (inputFile.read(buffer_char, 64)) {
		buffer_char[64] = 0;

		for (int i = 0; i < 64; i++)
			buffer[i] = static_cast<unsigned char>(buffer_char[i]);

		DES_decryption_helper(buffer, dest, key);

		outputFile << dest;
	}
	inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	inputFile.close();
	outputFile.close();

	//std::cout << "after decryption - " << dest << std::endl;
	std::cout << "Data decrypted successfully." << std::endl;
}








void printing_half_plaintext(unsigned char a[])
{
	for (int i = 0; i < 32; i++)
	{
		std::cout << a[i];
	}
	std::cout << std::endl;
}



/*void encryption_with_DES()    // I made this for working with no arguments only with terminal input
{								// now it works with arguments,there are not need of these funcions
	std::string input_pathname;
	std::string output_pathname;
	std::cout << "input file pathname for encryption" << std::endl;
	std::cin >> input_pathname;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	//std::cout << "inputed pathname - " << input_pathname << std::endl;
	std::cout << "output file pathname for encrypted ciphertext" << std::endl;

	std::cin >> output_pathname;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	//std::cout << "outputed pathname - " << output_pathname << std::endl;

	DES_encrypt(input_pathname, output_pathname);
}


void decryption_with_DES()
{
	std::string input_pathname;
	std::string output_pathname;

	std::cout << "input file pathname for decryption" << std::endl;
	std::cin >> input_pathname;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "output file pathname for decrypted plaintext" << std::endl;
	std::cin >> output_pathname;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	DES_decrypt(input_pathname, output_pathname);
}*/