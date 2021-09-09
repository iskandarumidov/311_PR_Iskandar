#include <stdio.h>
#include <string.h>

#define DONE 0x13579BDF
#define DTWO -32768
#define DTHREE 100
#define GetLastDigit(isBin, isHex, num) (isHex) ? (num & 0x0f) : (num & 1)
//#define InsertDigit(dig, num) 

// will use this function to print a binary num
void print_bin(unsigned n)
{
    unsigned i;
    for (i = 1 << 31; i > 0; i = i / 2)
        (n & i) ? printf("1") : printf("0");
    printf("\n");
}

int main(int argc, char **argv)
{
  int num;
  int reversed = 0;
  // since strcmp return 0 for matching strings, negate it to get 1 if matched
  int isBin = !strcmp("-DBIN", argv[1]);
  int isHex = !strcmp("-DHEX", argv[1]);
  if(isBin != 1 & isHex != 1) { // if neither are 1, assume HEX
    isHex = 1;
  }

  // use argc-1 to get last argument, which is assumed to be the number
  if (strcmp("-DONE", argv[argc-1]) == 0){
    num = 0x13579BDF;
  }
  if (strcmp("-DTWO", argv[argc-1]) == 0){
    num = -32768;
  }
  if (strcmp("-DTHREE", argv[argc-1]) == 0){
    num = 100;
  }
  printf("%d %d %04x\n", isBin, isHex, num);
  if (isBin) {
    printf("Original number: ");
    print_bin(num);
  }else{
    printf("Original number: %04x\n", num);
  }

  // first reverse
  if (isBin){
    while (num > 0){
      int last = GetLastDigit(isBin, isHex, num);
      num = num >> 1;
      reversed = reversed << 1;
      reversed = reversed | last;
    }
    printf("Reversed number: ");
    print_bin(reversed);
  }else{
    while (num > 0){
      int last = GetLastDigit(isBin, isHex, num);
      num = num >> 4;
      reversed = reversed << 4;
      reversed = reversed | last;
    }
    printf("Reversed number: %04x\n", reversed);
  }

  num = reversed;
  reversed = 0;
  printf("TEST");
  printf("%04x, %d\n", num, reversed);
  //second reverse
    if (isBin){
      while (num != 0){
        int last = GetLastDigit(isBin, isHex, num);
        printf("%04x %04x %04x\n", last, num, reversed);
        num = num >> 1;
        reversed = reversed << 1;
        reversed = reversed | last;
      }
      printf("Second  reverse: ");
      print_bin(reversed);
    }else{
      while (num != 0){
        int last = GetLastDigit(isBin, isHex, num);
        printf("%04x %04x %04x\n", last, num, reversed);
        
        num = num >> 4;
        reversed = reversed << 4;
        reversed = reversed | last;
      }
      printf("Second  reverse: %04x\n", reversed);
    }
    printf("Reversing reversed number yields original number\n");
    return 0;
}

// clang-7 -pthread -lm -o main main.c
// ./main -DBIN -DONE



// Second reverse: 0x13579BDF
// Reversing reversed number yields original number