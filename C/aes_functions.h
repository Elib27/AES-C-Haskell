typedef unsigned char byte;

void subBytes(byte state[4][4]);
void invSubBytes(byte state[4][4]);
void shiftRows(byte state[4][4]);
void shiftRow(byte row[4], int shiftIndex);
void invShiftRows(byte state[4][4]);
void invShiftRow(byte row[4], int shiftIndex);
void mixColumns(byte state[4][4]);
void invMixColumns(byte state[4][4]);
void addRoundKey(byte state[4][4], byte expandedKey[16]);
void subWord(byte w[4]);
void rotWord(byte w[4]);
byte *keyExpansion(byte key[], int Nk, int Nr);
void inputToState(byte in[16], byte state[4][4]);
void stateToOutput(byte state[4][4], byte out[16]);