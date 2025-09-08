#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


#define MIN_LEN_OF_STR 1

// Dichiarazione esterna del dizionario dei simboli regex
extern const char *regex_dict[];

/*Allocated an empty string with a specified size */ 
char* init_str(int size);

/*Generate a random regex with a spefied size, and specified witch character not include in to the regex */
char* regexGenerator(int size, const char* notIncludeThis); 

/*Generate a string from a regex previously generated, with a specific size, and how many time the regex are repeated to created the string */ 
char* generateStrFromRegex(char* regex, int size, int repeatTheRegex); 

/*check is the input string is empty or not*/ 
int strIsEmpty(char*str);

char* concatenateMultipleStringNewRegex(int size, char* notIncludeThis);

/*Deallocated the input string*/ 
int erase_str(char* str); 
