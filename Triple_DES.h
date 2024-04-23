#ifndef TRIPLE_DES_H_
#define TRIPLE_DES_H_

void key_making_char(unsigned char key[], std::string string_key);

void Triple_DES_encrypt(std::string input, std::string output, std::string key_1,
	std::string key_2, std::string key_3);
//void encryption_with_Triple_DES();

void Triple_DES_decrypt(std::string input, std::string output, std::string key_1,
	std::string key_2, std::string key_3);
//void decryption_with_Triple_DES();

#endif