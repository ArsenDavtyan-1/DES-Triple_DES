#include <iostream>
#include <fstream>
#include <istream>
#include <ostream>
#include <string>
#include <cstdlib>
#include "DES.h"
#include "Triple_DES.h"


int main()
{
	/*std::string input = R"(C:\Users\HP\Desktop\DES1.txt)";
	std::string output = R"(C:\Users\HP\Desktop\DES2.txt)";
	std::string key = R"(asdeefls)";

	std::string input_for_decrypt = R"(C:\Users\HP\Desktop\DES2.txt)";
	std::string output_for_decrypt = R"(C:\Users\HP\Desktop\DES3.txt)";

	DES_encrypt(input, output, key);

	DES_decrypt(input_for_decrypt, output_for_decrypt, key);*/


	std::string input = R"(C:\Users\HP\Desktop\triple1.txt)";
	std::string output = R"(C:\Users\HP\Desktop\triple2.txt)";
	std::string key1 = R"(asdeefls)", key2 = R"(as*/- fls)", key3 = R"(5-+==efls)";

	std::string input_for_decrypt = R"(C:\Users\HP\Desktop\triple2.txt)";
	std::string output_for_decrypt = R"(C:\Users\HP\Desktop\triple3.txt)";

	Triple_DES_encrypt(input, output, key1, key2, key3);

	Triple_DES_decrypt(input_for_decrypt, output_for_decrypt, key1, key2, key3);

}



