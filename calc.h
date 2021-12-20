#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TEXT 1024
#define WORD 30
#define A ((char)65)
#define Z ((char)90)
#define a ((char)97)
#define z ((char)122)
#define TEXT_OVERFLOW(in_size) ((in_size + textWrPtr) > TEXT)
#define IS_VALID(c) (((c >= A) && (c <= Z)) || ((c >= a) && (c <= z)))

static char text[TEXT] = "";
static char word[WORD] = "";
static char wordAtbash[WORD] = "";
static int textWrPtr = 0;
static int wordGematriaCnt = 0;
static int wordAtbashCnt = 0;
static char upperAtbCnt[26] = {0};
static char lowerAtbCnt[26] = {0};
static char upperCnt[26] = {0};
static char lowerCnt[26] = {0};


void getInput();
void printGematria();
void printAtbash();
void printAnagram();
