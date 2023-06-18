#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "aes.h"
#include "utils.h"

void cipher128Tests(void);
void cipher192Tests(void);
void cipher256Tests(void);
void invCipher128Tests(void);
void invCipher192Tests(void);
void invCipher256Tests(void);
void ECBcipherTests(void);
void CBCcipherTests(void);
void fileECBcipherTests(void);
void fileCBCcipherTests(void);
void bitmapECBcipherTests(void);
void bitmapCBCcipherTests(void);
void entropyTests(void);

int main(void)
{
  cipher128Tests();
  cipher192Tests();
  cipher256Tests();
  invCipher128Tests();
  invCipher192Tests();
  invCipher256Tests();
  ECBcipherTests();
  CBCcipherTests();
  fileECBcipherTests();
  fileCBCcipherTests();
  bitmapECBcipherTests();
  bitmapCBCcipherTests();
  entropyTests();
  return 0;
}

void cipher128Tests()
{
  byte plainText1[16] = {0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d, 0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34};

  byte key1[16] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};

  byte cipheredText1[16] = {0x39, 0x25, 0x84, 0x1d, 0x02, 0xdc, 0x09, 0xfb, 0xdc, 0x11, 0x85, 0x97, 0x19, 0x6a, 0x0b, 0x32};

  cipher(plainText1, plainText1, key1, 128);
  assert(compareArrays(plainText1, cipheredText1, 16));
  printf("- cipher 128 bits tests passed\n");
}

void cipher192Tests()
{
  byte plainText1[16] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};

  byte key1[24] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17};

  byte cipheredText1[16] = {0xdd, 0xa9, 0x7c, 0xa4, 0x86, 0x4c, 0xdf, 0xe0, 0x6e, 0xaf, 0x70, 0xa0, 0xec, 0x0d, 0x71, 0x91};

  cipher(plainText1, plainText1, key1, 192);
  assert(compareArrays(plainText1, cipheredText1, 16));
  printf("- cipher 192 bits tests passed\n");
}

void cipher256Tests()
{
  byte plainText1[16] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};

  byte key1[32] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f};

  byte cipheredText1[16] = {0x8e, 0xa2, 0xb7, 0xca, 0x51, 0x67, 0x45, 0xbf, 0xea, 0xfc, 0x49, 0x90, 0x4b, 0x49, 0x60, 0x89};

  cipher(plainText1, plainText1, key1, 256);
  assert(compareArrays(plainText1, cipheredText1, 16));
  printf("- cipher 256 bits tests passed\n");
}

void invCipher128Tests()
{
  byte cipheredText1[16] = {0x39, 0x25, 0x84, 0x1d, 0x02, 0xdc, 0x09, 0xfb, 0xdc, 0x11, 0x85, 0x97, 0x19, 0x6a, 0x0b, 0x32};

  byte key1[16] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};

  byte plainText1[16] = {0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d, 0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34};

  invCipher(cipheredText1, cipheredText1, key1, 128);
  assert(compareArrays(cipheredText1, plainText1, 16));
  printf("- invCipher 128 bits tests passed\n");
}

void invCipher192Tests()
{

  byte cipheredText1[16] = {0xdd, 0xa9, 0x7c, 0xa4, 0x86, 0x4c, 0xdf, 0xe0, 0x6e, 0xaf, 0x70, 0xa0, 0xec, 0x0d, 0x71, 0x91};

  byte key1[24] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17};

  byte plainText1[16] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};

  invCipher(cipheredText1, cipheredText1, key1, 192);
  assert(compareArrays(cipheredText1, plainText1, 16));
  printf("- invCipher 192 bits tests passed\n");
}

void invCipher256Tests()
{
  byte cipheredText1[16] = {0x8e, 0xa2, 0xb7, 0xca, 0x51, 0x67, 0x45, 0xbf, 0xea, 0xfc, 0x49, 0x90, 0x4b, 0x49, 0x60, 0x89};

  byte key1[32] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f};

  byte plainText1[16] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};

  invCipher(cipheredText1, cipheredText1, key1, 256);
  assert(compareArrays(cipheredText1, plainText1, 16));
  printf("- invCipher 256 bits tests passed\n");
}

void ECBcipherTests()
{
  byte key1[16] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
  byte plainText1[17] = {0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d, 0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34, 0xab};
  byte *cipheredText1 = cipherECB(plainText1, key1, 17, 128);
  byte expectedCipheredText1[32] = {0x39, 0x25, 0x84, 0x1d, 0x02, 0xdc, 0x09, 0xfb, 0xdc, 0x11, 0x85, 0x97, 0x19, 0x6a, 0x0b, 0x32, 0xbb, 0x2b, 0x45, 0xe1, 0x02, 0x53, 0x1e, 0x4d, 0xe4, 0xa3, 0xd4, 0x08, 0x96, 0xe7, 0x15, 0x88};
  assert(compareArrays(cipheredText1, expectedCipheredText1, 17));
  byte *decipheredText1 = invCipherECB(cipheredText1, key1, 17, 32, 128);
  assert(compareArrays(decipheredText1, plainText1, 17));
  free(cipheredText1);
  free(decipheredText1);

  byte key2[16] = {0x10, 0x2b, 0x15, 0x16, 0x28, 0xae, 0x7e, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0xda}; // 10 2b 15 16 28 ae 7e a6 ab f7 15 88 09 cf 4f da
  byte plainText2[16] = {0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d, 0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34};
  byte *cipheredText2 = cipherECB(plainText2, key2, 16, 128);
  byte expectedCipheredText2[16] = {0x63, 0x67, 0x01, 0x57, 0xf0, 0x37, 0x07, 0x9c, 0xc7, 0x89, 0xa9, 0xd8, 0xee, 0xf9, 0x04, 0xd2};
  assert(compareArrays(cipheredText2, expectedCipheredText2, 16));
  byte *decipheredText2 = invCipherECB(cipheredText2, key2, 16, 32, 128);
  assert(compareArrays(decipheredText2, plainText2, 16));
  free(cipheredText2);
  free(decipheredText2);

  printf("- ECBcipher & InvCipher tests passed\n");
}

void CBCcipherTests(void)
{
  byte key1[16] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
  byte plainText1[17] = {0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d, 0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34, 0xab};
  byte *cipheredText1 = cipherCBC(plainText1, key1, 17, 128);
  byte *decipheredText1 = invCipherCBC(cipheredText1, key1, 17, 32, 128);
  assert(compareArrays(decipheredText1, plainText1, 17));
  free(decipheredText1);
  free(cipheredText1);

  byte key2[16] = {0xaa, 0xff, 0x6e, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x5f, 0x8d};
  byte plainText2[16] = {0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d, 0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34};
  byte *cipheredText2 = cipherCBC(plainText2, key2, 16, 128);
  byte *decipheredText2 = invCipherCBC(cipheredText2, key2, 16, 32, 128);
  assert(compareArrays(decipheredText2, plainText2, 16));
  free(decipheredText2);
  free(cipheredText2);

  printf("- CBCcipher & InvCipher tests passed\n");
}

void fileECBcipherTests()
{
  byte key[16] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
  cipherFile("test.txt", "test_ciphered_ecb.txt", key, 128, 'e');
  invCipherFile("test_ciphered_ecb.txt", "test_deciphered_ecb.txt", key, 128, 'e');

  printf("- file ECBcipher & InvCipher tests passed\n");
}

void fileCBCcipherTests()
{
  byte key[16] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
  cipherFile("test.txt", "test_ciphered_cbc.txt", key, 128, 'c');
  invCipherFile("test_ciphered_cbc.txt", "test_deciphered_cbc.txt", key, 128, 'c');
  printf("- file CBCcipher & InvCipher tests passed\n");
}

void bitmapECBcipherTests()
{
  byte key[16] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
  bitmapCipher("cervin.bmp", "cervin_ciphered_ecb.bmp", key, 128, 'e');
  bitmapInvCipher("cervin_ciphered_ecb.bmp", "cervin_deciphered_ecb.bmp", key, 128, 'e');

  bitmapCipher("carre.bmp", "carre_ciphered_ecb.bmp", key, 128, 'e');
  bitmapInvCipher("carre_ciphered_ecb.bmp", "carre_deciphered_ecb.bmp", key, 128, 'e');

  printf("- bitmap ECBcipher & InvCipher tests passed\n");
}

void bitmapCBCcipherTests()
{
  byte key[16] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
  bitmapCipher("cervin.bmp", "cervin_ciphered_cbc.bmp", key, 128, 'c');
  bitmapInvCipher("cervin_ciphered_cbc.bmp", "cervin_deciphered_cbc.bmp", key, 128, 'c');

  bitmapCipher("carre.bmp", "carre_ciphered_cbc.bmp", key, 128, 'c');
  bitmapInvCipher("carre_ciphered_cbc.bmp", "carre_deciphered_cbc.bmp", key, 128, 'c');

  printf("- bitmap CBCcipher & InvCipher tests passed\n");
}

void entropyTests()
{
  printf("\nEntropie du texte non chiffré    : %f\n", entropy("test.txt"));
  printf("Entropie du texte chiffré en ECB : %f\n", entropy("test_ciphered_ecb.txt"));
  printf("Entropie du texte chiffré en CBC : %f\n\n", entropy("test_ciphered_cbc.txt"));

  printf("Entropie du Cervin non chiffré    : %f\n", entropy("cervin.bmp"));
  printf("Entropie du Cervin chiffré en ECB : %f\n", entropy("cervin_ciphered_ecb.bmp"));
  printf("Entropie du Cervin chiffré en CBC : %f\n\n", entropy("cervin_ciphered_cbc.bmp"));

  printf("Entropie du carré blanc non chiffré    : %f\n", entropy("carre.bmp"));
  printf("Entropie du carré blanc chiffré en ECB : %f\n", entropy("carre_ciphered_ecb.bmp"));
  printf("Entropie du carré blanc chiffré en CBC : %f\n\n", entropy("carre_ciphered_cbc.bmp"));
}