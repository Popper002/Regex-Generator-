#include "regex.h"




int main(int argc, char const *argv[])
{
    char* regex = init_str(atoi(argv[1]));
    int res = strIsEmpty(regex);     
    return 0;
}
