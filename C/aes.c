#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "aes.h"
#include "utils.h"

void cipher(byte in[16], byte out[16], byte key[], int keySize)
{
  int Nk, Nr;
  getCipherParameters(keySize, &Nk, &Nr);

  byte *expandedKey = keyExpansion(key, Nk, Nr);
  byte state[4][4];
  inputToState(in, state);
  addRoundKey(state, expandedKey);
  for (int i = 1; i < Nr; i++)
  {
    subBytes(state);
    shiftRows(state);
    mixColumns(state);
    addRoundKey(state, expandedKey + 16 * i);
  }
  subBytes(state);
  shiftRows(state);
  addRoundKey(state, expandedKey + 16 * Nr);

  stateToOutput(state, out);
  free(expandedKey);
}

void invCipher(byte in[16], byte out[16], byte key[], int keySize)
{
  int Nk, Nr;
  getCipherParameters(keySize, &Nk, &Nr);

  byte *expandedKey = keyExpansion(key, Nk, Nr);
  byte state[4][4];
  inputToState(in, state);
  addRoundKey(state, expandedKey + 16 * Nr);
  for (int i = Nr - 1; i > 0; i--)
  {
    invShiftRows(state);
    invSubBytes(state);
    addRoundKey(state, expandedKey + 16 * i);
    invMixColumns(state);
  }
  invShiftRows(state);
  invSubBytes(state);
  addRoundKey(state, expandedKey);

  stateToOutput(state, out);
  free(expandedKey);
}

byte *cipherECB(byte in[], byte key[], int inSize, int keySize)
{
  int resultSize = getUpper16multiple(inSize);

  byte *result = malloc(resultSize);
  memcpy(result, in, inSize);

  for (int i = inSize; i < resultSize; i++) // padding : on ajoute des 0 à la fin pour que la taille de result soit un multiple de 16
    result[i] = 0x00;

  int blocsCount = resultSize / 16;
  for (int i = 0; i < blocsCount; i++) // chiffrement des blocs
    cipher(result + 16 * i, result + 16 * i, key, keySize);

  return result;
}

byte *invCipherECB(byte in[], byte key[], int originalSize, int inSize, int keySize)
{
  byte *result = malloc(originalSize);
  byte *temp = malloc(inSize);
  memcpy(temp, in, inSize);

  int blocsCount = inSize / 16;
  for (int i = 0; i < blocsCount; i++) // déchiffrement des blocs
    invCipher(temp + 16 * i, temp + 16 * i, key, keySize);

  memcpy(result, temp, originalSize);
  free(temp);
  return result;
}

void xorBloc(byte bloc1[16], byte bloc2[16], byte result[16])
{
  for (int i = 0; i < 16; i++)
    result[i] = bloc1[i] ^ bloc2[i];
}

byte *cipherCBC(byte in[], byte key[], int inSize, int keySize)
{
  int resultSize; // resultSize doit être un multiple de 16
  if (inSize % 16 == 0)
    resultSize = inSize;
  else
    resultSize = inSize + (16 - inSize % 16);

  byte *result = malloc(resultSize);
  memcpy(result, in, inSize);

  for (int i = inSize; i < resultSize; i++) // padding : on ajoute des 0 à la fin pour que la taille de result soit un multiple de 16
    result[i] = 0x00;

  for (int i = 0; i < resultSize / 16; i++) // chiffrement des blocs
  {
    if (i == 0)
    {
      byte initVector[16] = {0}; // vecteur utilisé pour le premier bloc
      xorBloc(result, initVector, result);
    }
    else
    {
      xorBloc(result + 16 * i, result + 16 * (i - 1), result + 16 * i);
    }
    cipher(result + 16 * i, result + 16 * i, key, keySize);
  }
  return result;
}

byte *invCipherCBC(byte in[], byte key[], int originalSize, int inSize, int keySize)
{
  byte *result = malloc(originalSize);
  byte *temp = malloc(inSize);
  memcpy(temp, in, inSize);

  for (int i = 0; i < inSize / 16; i++) // déchiffrement des blocs
  {
    invCipher(in + 16 * i, temp + 16 * i, key, keySize);
    if (i == 0)
    {
      byte initVector[16] = {0}; // vecteur utilisé pour le premier bloc
      xorBloc(temp, initVector, temp);
    }
    else
    {
      xorBloc(in + 16 * (i - 1), temp + 16 * i, temp + 16 * i);
    }
  }

  memcpy(result, temp, originalSize);
  free(temp);
  return result;
}

void cipherFile(char fileName[], char cipheredFileName[], byte key[], int keySize, char cipherType)
{
  FILE *file = fopen(fileName, "rb");
  FILE *cipheredFile = fopen(cipheredFileName, "wb");
  if (file == NULL || cipheredFile == NULL)
  {
    printf("Erreur d'ouverture du fichier\n");
    exit(1);
  }

  // On récupère la taille du fichier
  fseek(file, 0, SEEK_END);
  int fileSize = ftell(file);
  fseek(file, 0, SEEK_SET);

  // Création du buffer contenant la taille du fichier et le contenu du fichier
  int sizeLength = 4;
  int fileWithSizeLength = fileSize + sizeLength;
  byte *inputBuffer = malloc(fileWithSizeLength);
  memcpy(inputBuffer, &fileSize, sizeLength);
  fread(inputBuffer + sizeLength, 1, fileSize, file);

  // Chiffrement du fichier
  byte *cipheredBuffer;
  switch (cipherType)
  {
  case 'e':
    cipheredBuffer = cipherECB(inputBuffer, key, fileWithSizeLength, keySize);
    break;
  case 'c':
    cipheredBuffer = cipherCBC(inputBuffer, key, fileWithSizeLength, keySize);
    break;
  default:
    printf("Type de chiffrement/dechiffrement inconnu\n");
    exit(1);
    break;
  }
  int newFileSize = getUpper16multiple(fileWithSizeLength);
  fwrite(cipheredBuffer, 1, newFileSize, cipheredFile);

  free(inputBuffer);
  free(cipheredBuffer);
  fclose(file);
  fclose(cipheredFile);
}

void invCipherFile(char fileName[], char decipheredFileName[], byte key[], int keySize, char cipherType)
{
  FILE *file = fopen(fileName, "rb");
  FILE *decipheredFile = fopen(decipheredFileName, "wb");
  if (file == NULL || decipheredFile == NULL)
  {
    printf("Erreur d'ouverture du fichier\n");
    exit(1);
  }

  // On récupère la taille du fichier
  fseek(file, 0, SEEK_END);
  int fileSize = ftell(file);
  fseek(file, 0, SEEK_SET);

  // Déchiffrement
  byte firstBlock[16];
  fread(firstBlock, 1, 16, file);
  byte *decipheredFirstBlock;
  int originalFileSize;
  int sizeLength = 4;

  byte *inputBuffer = malloc(fileSize);
  fseek(file, 0, SEEK_SET);
  fread(inputBuffer, 1, fileSize, file);
  byte *decipheredBuffer;

  switch (cipherType)
  {
  case 'e':
    // Déchiffrement du premier bloc pour récupérer la taille du fichier
    decipheredFirstBlock = invCipherECB(firstBlock, key, 16, 16, keySize);
    memcpy(&originalFileSize, decipheredFirstBlock, sizeLength);
    // Déchiffrement du fichier
    decipheredBuffer = invCipherECB(inputBuffer, key, originalFileSize + sizeLength, fileSize, keySize);
    break;
  case 'c':
    // Déchiffrement du premier bloc pour récupérer la taille du fichier
    decipheredFirstBlock = invCipherCBC(firstBlock, key, 16, 16, keySize);
    memcpy(&originalFileSize, decipheredFirstBlock, sizeLength);
    // Déchiffrement du fichier
    decipheredBuffer = invCipherCBC(inputBuffer, key, originalFileSize + sizeLength, fileSize, keySize);
    break;
  default:
    printf("Type de chiffrement/dechiffrement inconnu\n");
    exit(1);
    break;
  }
  fwrite(decipheredBuffer + sizeLength, 1, originalFileSize, decipheredFile);

  free(inputBuffer);
  free(decipheredBuffer);
  fclose(file);
  fclose(decipheredFile);
}

void bitmapCipher(char fileName[], char invCipheredFileName[], byte key[], int keySize, char cipherType)
{
  FILE *file = fopen(fileName, "rb");
  FILE *invCipheredFile = fopen(invCipheredFileName, "wb");
  if (file == NULL || invCipheredFile == NULL)
  {
    printf("Erreur d'ouverture du fichier\n");
    exit(1);
  }

  // Obtention des informations du header
  int imageSize, dataOffset;

  int sizeAddr = 0x02;
  fseek(file, sizeAddr, SEEK_SET);
  fread(&imageSize, 1, 4, file);

  int offsetAddr = 0x0A;
  fseek(file, offsetAddr, SEEK_SET);
  fread(&dataOffset, 1, 4, file);

  // On copie le header sans le chiffrer
  int sizeLength = 4;
  byte header[dataOffset];
  fseek(file, 0x00, SEEK_SET);
  fread(header, 1, dataOffset, file);
  int originalDataImageSize = imageSize - dataOffset;        // taille de l'image sans le header
  int newDataImageSize = originalDataImageSize + sizeLength; // taille de l'image sans le header avec la taille originale ajoutée
  int paddingSize = getUpper16multiple(newDataImageSize) - newDataImageSize;
  int newImageSize = imageSize + sizeLength + paddingSize;
  header[0x02] = newImageSize;
  fwrite(header, 1, dataOffset, invCipheredFile);

  // Chiffrement Image
  byte *data = malloc(newDataImageSize);
  memcpy(data, &originalDataImageSize, sizeLength); // ajout de la taille en début de données, après le header
  fseek(file, dataOffset, SEEK_SET);
  fread(data + sizeLength, 1, originalDataImageSize, file);
  byte *cipheredData;
  switch (cipherType)
  {
  case 'e':
    cipheredData = cipherECB(data, key, newDataImageSize, keySize);
    break;
  case 'c':
    cipheredData = cipherCBC(data, key, newDataImageSize, keySize);
    break;
  default:
    printf("Type de chiffrement/dechiffrement inconnu\n");
    exit(1);
    break;
  }

  fwrite(cipheredData, 1, newDataImageSize + paddingSize, invCipheredFile);

  fclose(file);
  fclose(invCipheredFile);
  free(data);
  free(cipheredData);
}

void bitmapInvCipher(char fileName[], char invCipheredFileName[], byte key[], int keySize, char cipherType)
{
  FILE *file = fopen(fileName, "rb");
  FILE *invCipheredFile = fopen(invCipheredFileName, "wb");
  if (file == NULL || invCipheredFile == NULL)
  {
    printf("Erreur d'ouverture du fichier\n");
    exit(1);
  }

  int imageSize, dataOffset;

  int sizeAddr = 0x02;
  fseek(file, sizeAddr, SEEK_SET);
  fread(&imageSize, 1, 4, file);

  int offsetAddr = 0x0A;
  fseek(file, offsetAddr, SEEK_SET);
  fread(&dataOffset, 1, 4, file);

  int sizeLength = 4;

  // Dechiffrement premier bloc pour récupérer la taille originale du fichier
  byte firstBlock[16];
  fseek(file, dataOffset, SEEK_SET);
  fread(firstBlock, 1, 16, file);
  byte *decipheredFirstBlock;
  int originalSize;
  switch (cipherType)
  {
  case 'e':
    decipheredFirstBlock = invCipherECB(firstBlock, key, 16, 16, keySize);
    memcpy(&originalSize, decipheredFirstBlock, sizeLength);
    break;
  case 'c':
    decipheredFirstBlock = invCipherCBC(firstBlock, key, 16, 16, keySize);
    memcpy(&originalSize, decipheredFirstBlock, sizeLength);
    break;
  default:
    printf("Type de chiffrement/dechiffrement inconnu\n");
    exit(1);
    break;
  }

  // On copie le header sans le chiffrer
  byte header[dataOffset];
  fseek(file, 0x00, SEEK_SET);
  fread(header, 1, dataOffset, file);
  int dataImageSize = imageSize - dataOffset;
  int padding = dataImageSize - originalSize - sizeLength;
  header[0x02] = imageSize - sizeLength - padding;
  fwrite(header, 1, dataOffset, invCipheredFile);

  // Dechiffrement Image
  fseek(file, dataOffset, SEEK_SET);
  byte *data = malloc(dataImageSize);
  fread(data, 1, dataImageSize, file);
  byte *cipheredData;
  switch (cipherType)
  {
  case 'e':
    cipheredData = invCipherECB(data, key, originalSize + sizeLength, dataImageSize, keySize);
    break;
  case 'c':
    cipheredData = invCipherCBC(data, key, originalSize + sizeLength, dataImageSize, keySize);
    break;
  default:
    printf("Type de chiffrement/dechiffrement inconnu\n");
    exit(1);
    break;
  }

  fwrite(cipheredData + sizeLength, 1, originalSize, invCipheredFile);

  fclose(file);
  fclose(invCipheredFile);
  free(data);
  free(cipheredData);
}

double entropy(char fileName[])
{
  int counts[256] = {0};
  double total = 0;
  double entropyResult = 0;
  FILE *file = fopen(fileName, "rb");
  if (file == NULL)
  {
    printf("Erreur d'ouverture du fichier\n");
    exit(1);
  }
  int val;
  while ((val = fgetc(file)) != EOF)
  {
    counts[val]++;
  }
  for (int i = 0; i < 256; i++)
    total += counts[i];
  for (int i = 0; i < 256; i++)
  {
    if (counts[i] != 0 && total != 0)
      entropyResult -= (counts[i] / total) * log2(counts[i] / total);
  }
  fclose(file);
  return entropyResult;
}