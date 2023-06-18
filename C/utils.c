#include "utils.h"
#include "stdio.h"
#include "stdlib.h"

void printState(byte state[4][4])
{
  printf("\n");
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      printf("%x ", state[i][j]);
    }
    printf("\n");
  }
}

void printArray(byte array[], int arrSize)
{
  for (int i = 0; i < arrSize; i++)
  {
    printf("%x ", array[i]);
  }
  printf("\n");
}

void printIntArray(int array[], int arrSize)
{
  for (int i = 0; i < arrSize; i++)
  {
    printf("%d ", array[i]);
  }
  printf("\n");
}

int compareStates(byte state1[4][4], byte state2[4][4])
{
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      if (state1[i][j] != state2[i][j])
        return 0;
  return 1;
}

int compareArrays(byte array1[], byte array2[], int arrSize)
{
  for (int i = 0; i < arrSize; i++)
    if (array1[i] != array2[i])
      return 0;
  return 1;
}

void copyState(byte stateToCopy[4][4], byte copiedState[4][4])
{
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      copiedState[i][j] = stateToCopy[i][j];
}

void transpose(byte state[4][4])
{
  byte transposedState[4][4];
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      transposedState[i][j] = state[j][i];
  copyState(transposedState, state);
}

// Bytes operations

byte xTime(byte a)
{
  byte result = a << 1;
  if (a & 0x80)     // verifie si le bit de poids fort de a est 1
    result ^= 0x1b; // modulo x^8 + x^4 + x^3 + x + 1
  return result;
}

byte powX(byte a, int n)
{
  byte result = a;
  for (int i = 0; i < n; i++)
    result = xTime(result);
  return result;
}

byte byteMult(byte a, byte b)
{
  byte result = 0;
  for (int i = 0; i < 8; i++)
  {
    if (b & 0x01) // verifie si le bit de poids faible de b est 1
      result ^= a;
    a = xTime(a);
    b >>= 1;
  }
  return result;
}

void polyCoefGF28Add(byte a[4], byte b[4], byte result[4])
{
  for (int i = 0; i < 4; i++)
    result[i] = a[i] ^ b[i];
}

// polynômes dont le coefficient du plus haut degré est le dernier élément du tableau
void polyCoefGF28Mult(byte a[4], byte b[4], byte result[4])
{
  result[0] = byteMult(a[0], b[0]) ^ byteMult(a[3], b[1]) ^ byteMult(a[2], b[2]) ^ byteMult(a[1], b[3]);
  result[1] = byteMult(a[1], b[0]) ^ byteMult(a[0], b[1]) ^ byteMult(a[3], b[2]) ^ byteMult(a[2], b[3]);
  result[2] = byteMult(a[2], b[0]) ^ byteMult(a[1], b[1]) ^ byteMult(a[0], b[2]) ^ byteMult(a[3], b[3]);
  result[3] = byteMult(a[3], b[0]) ^ byteMult(a[2], b[1]) ^ byteMult(a[1], b[2]) ^ byteMult(a[0], b[3]);
}

void getCipherParameters(int keySize, int *Nk, int *Nr)
{
  switch (keySize)
  {
  case 128:
    *Nk = 4;
    *Nr = 10;
    break;
  case 192:
    *Nk = 6;
    *Nr = 12;
    break;
  case 256:
    *Nk = 8;
    *Nr = 14;
    break;
  default:
    printf("Invalid key size\n");
    exit(1);
  }
}

int getUpper16multiple(int n)
{
  int result;
  if (n % 16 == 0)
    result = n;
  else
    result = n + (16 - n % 16);
  return result;
}