#include <stdio.h>
#include <assert.h>
#include "utils.h"

void byteMultTests(void);
void polyCoefGF28MultTests(void);

int main(void)
{
  byteMultTests();
  polyCoefGF28MultTests();
  return 0;
}

void byteMultTests()
{
  assert(byteMult(0x57, 0x13) == 0xfe);
  assert(byteMult(0xca, 0x53) == 0x01);
  assert(byteMult(0x57, 0x08) == 0x8e);
  assert(byteMult(0x57, 0x83) == 0xc1);
  assert(byteMult(0x29, 0x00) == 0x00);

  printf("- byteMult tests passed\n");
}

void polyCoefGF28MultTests()
{
  byte a1[4] = {0xe0, 0xb4, 0x52, 0xae};
  byte b1[4] = {0x02, 0x01, 0x01, 0x03};
  byte result1[4];
  polyCoefGF28Mult(a1, b1, result1);
  byte expectedResult1[4] = {0xe0, 0xcb, 0x19, 0x9a};
  assert(compareArrays(result1, expectedResult1, 4));

  byte a2[4] = {0x09, 0x1f, 0x01, 0x04};
  byte b2[4] = {0x1b, 0x10, 0x0e, 0x0b};
  byte result2[4];
  polyCoefGF28Mult(a2, b2, result2);
  byte expectedResult2[4] = {0x54, 0x91, 0xa2, 0x95};
  assert(compareArrays(result2, expectedResult2, 4));

  byte a3[4] = {0xd4, 0xbf, 0x5d, 0x30};
  byte b3[4] = {0x02, 0x01, 0x01, 0x03};
  byte result3[4];
  polyCoefGF28Mult(a3, b3, result3);
  byte expectedResult3[4] = {0x04, 0x66, 0x81, 0xe5};
  assert(compareArrays(result3, expectedResult3, 4));

  printf("- polyCoefGF28Mult tests passed\n");
}