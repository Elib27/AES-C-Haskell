#include "aes_functions.h"

void printState(byte state[4][4]);
void printArray(byte array[], int arrSize);
void printIntArray(int array[], int arrSize);
int compareStates(byte state1[4][4], byte state2[4][4]);
int compareArrays(byte array1[], byte array2[], int arrSize);
void copyState(byte stateToCopy[4][4], byte copiedState[4][4]);
void transpose(byte state[4][4]);
byte xTime(byte a);
byte powX(byte a, int n);
void polyCoefGF28Add(byte a[4], byte b[4], byte result[4]);
byte byteMult(byte a, byte b);
void polyCoefGF28Mult(byte a[4], byte b[4], byte result[4]);
void getCipherParameters(int keySize, int *Nk, int *Nr);
int getUpper16multiple(int n);