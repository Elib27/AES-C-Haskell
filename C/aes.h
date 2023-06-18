#include "aes_functions.h"

void cipher(byte in[16], byte out[16], byte key[], int keySize);
void invCipher(byte in[16], byte out[16], byte key[], int keySize);
void xorBloc(byte bloc1[16], byte bloc2[16], byte result[16]);
byte *cipherECB(byte in[], byte key[], int inSize, int keySize);
byte *invCipherECB(byte in[], byte key[], int originalSize, int inSize, int keySize);
byte *cipherCBC(byte in[], byte key[], int inSize, int keySize);
byte *invCipherCBC(byte in[], byte key[], int originalSize, int inSize, int keySize);
void cipherFile(char fileName[], char cipheredFileName[], byte key[], int keySize, char cipherType);
void invCipherFile(char fileName[], char decipheredFileName[], byte key[], int keySize, char cipherType);
void bitmapCipher(char fileName[], char cipheredFileName[], byte key[], int keySize, char cipherType);
void bitmapInvCipher(char fileName[], char cipheredFileName[], byte key[], int keySize, char cipherType);
void count_occurrences(FILE *file, int counts[256]);
double entropy(char fileName[]);