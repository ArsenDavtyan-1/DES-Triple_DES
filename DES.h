#ifndef DES_H_
#define DES_H_

void char_to_binary(unsigned char array[], unsigned char key[], int size = 8);
void key_pc1(unsigned char binary_key[], unsigned char key_aft_pc1[]);
void left_shift_one(unsigned char half_key[]);
void left_shift_two(unsigned char half_key[]);
void key_pc2(unsigned char subkey[], unsigned char left_half[], unsigned char right_half[]);
void XOR_char(unsigned char first[], unsigned char second[], int size = 48);
void init_perm(unsigned char plaintext[], unsigned char plain_aft_init[]);
int binary_to_decimal(unsigned char a, unsigned char b);
int binary_to_decimal(unsigned char arr[], int start_position);
void decimal_to_binary(unsigned char array[], int start_position, int val);
void DES_round(unsigned char left_half[], unsigned char right_half[], unsigned char subkey[]);
void making_char_binary(unsigned char a, unsigned char destination[], int start_position);
void making_char_key_to_binary(unsigned char key[], unsigned char binary_key[], int size = 8);
unsigned char making_binary_to_char(unsigned char binary[], int start_position);
void making_binary_ciphertext_to_char(unsigned char binary_ciphertext[], unsigned char char_ciphertext[], int size = 8);
void DES(unsigned char plaintext_char[], unsigned char ciphertext_char[], unsigned char key[], int size = 64);
void DES_encrypt(std::string input, std::string output, std::string key_1);
void DES_decryption_helper(unsigned char char_cipher[], unsigned char char_plain[], unsigned char key[]);
void DES_decrypt(std::string input, std::string output, std::string key_1);

//void decryption_with_DES();
//void encryption_with_DES();

void printing_half_plaintext(unsigned char a[]);

#endif
