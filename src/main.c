#include "regex.h"
#include <time.h>




int main(int argc, char const *argv[])
{
    srand(time(NULL));
    char* regex = init_str(atoi(argv[1]));
    int res = strIsEmpty(regex);     
    regex = regexGenerator(atoi(argv[1]), (const char*)argv[2]);
    printf("%s\n", regex);
    erase_str(regex);
    return 0;
}
