#include <stdlib.h>
#include <stdio.h>

int digits(unsigned int x) {
  if (x >= 1000000000) return 10;
  if (x >= 100000000)  return 9;
  if (x >= 10000000)   return 8;
  if (x >= 1000000)    return 7;
  if (x >= 100000)     return 6;
  if (x >= 10000)      return 5;
  if (x >= 1000)       return 4;
  if (x >= 100)        return 3;
  if (x >= 10)         return 2;
  return 1;
}

unsigned char* uint2string(unsigned int n) {
  int d = digits(n);
  unsigned char *buf = malloc(d * sizeof *buf);

  for (uint8_t i = d; i > 0; i--) {
    // printf("I: %d\n", i);
  // do {
    buf[i-1] = 0x30 + (n % 10);
    n = n / 10;
  // } while(n);
  }

  return buf;
}

int main(void) {
  printf("Test code\n");

  int n = 12560;
  int d = digits(n);
  printf("Len: %d\n", d);

  // unsigned char buf[d];
  // unsigned char *buf = malloc(d * sizeof *buf);

  // do {
  //   printf("n= %d\n", (0x30 + (n % 10)));
  //   // buf[--d] = 0x30 + (n % 10);
  //   n /= 10;
  // } while(n);

  // printf("Result: %s.\n", buf);
  printf("Result2: %s.\n", uint2string(12560));

  return 0;
}
