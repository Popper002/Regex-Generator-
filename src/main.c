#include "regex.h"
#include <time.h>




int main(int argc, char const *argv[])
{
    srand(time(NULL));
    char* regex = regexGenerator(atoi(argv[1]), (const char*)argv[2]);
    printf("Generated regex: %s\n", regex);
    char* str = generateStrFromRegex(regex, atoi(argv[1]), atoi(argv[3])); // Ripete la regex 1 volta
    printf("Generated string: %s\n", str);
    char* concatenate_new = concatenateMultipleStringNewRegex(atoi(argv[1]), (char*)argv[2]);
    printf("\n%s\n", concatenate_new); 
    erase_str(concatenate_new); 
    erase_str(str);
    erase_str(regex);
    return 0;
}
