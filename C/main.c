#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "aes.h"
#include "utils.h"

#define ENCRYPTIONS 10

int main(void)
{
  byte key[16] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};

  unsigned long int totalTime = 0;

  for (int i = 0; i < ENCRYPTIONS; i++)
  {
    clock_t begin = clock();
    bitmapCipher("cervin.bmp", "cervin_ciphered_ecb.bmp", key, 128, 'e');
    // bitmapInvCipher("cervin_ciphered_ecb.bmp", "cervin_deciphered_ecb.bmp", key, 128, 'e');
    clock_t end = clock();

    unsigned long time = (end - begin);
    totalTime += time;
    printf("Encryption %d / %d done in : %lu\n", i + 1, ENCRYPTIONS, time);
  }

  unsigned long averageTime = totalTime / ENCRYPTIONS;
  printf("\n\n Average encryption duration : %lu\n", averageTime);

  return 0;
}