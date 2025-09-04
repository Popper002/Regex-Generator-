#include "regex.h"

// Definizione del dizionario dei simboli regex
const char *regex_dict[] = {
    ".",     // qualsiasi carattere
    "\\d",   // cifra
    "\\w",   // carattere alfanumerico
    "\\s",   // spazio bianco
    "[a-z]", // lettere minuscole
    "[A-Z]", // lettere maiuscole
    "[0-9]", // cifre
    "+",     // uno o più
    "*",     // zero o più
    "?",     // zero o uno
    "{2,5}", // ripetizione da 2 a 5
    "|",     // OR
    "(",     // parentesi aperta
    ")",     // parentesi chiusa
    "^",     // inizio stringa
    "$"      // fine stringa
};

/*Allocated an empty string with a specified size */ 
char* init_str(int size){
	char* str = (char*)calloc(size, sizeof(char)*size); 
	if(str == NULL){
		fprintf(stderr, "%s %d init_str --> Error allocated str", __FILE__ ,__LINE__); 
		return NULL; 
	}	
	return str; 
}

/*Generate a random regex with a spefied size, and specified witch character not include in to the regex */
char* regexGenerator(int size, const char* notIncludeThis){
    if(notIncludeThis == NULL){ 
        fprintf(stderr, "%s %d regexGenerator --> this param cannot be NULL, use empty string \"\"\n", 
                __FILE__, __LINE__); 		  
        return NULL;
    }

    int dict_size = sizeof(regex_dict) / sizeof(regex_dict[0]);

    // Alloca spazio per la regex finale
    char* regex = malloc(size * 10 + 1); // 10 per sicurezza (alcuni simboli tipo "[a-z]" sono lunghi)
    if(regex == NULL) { 
        fprintf(stderr, "%s %d regexGenerator --> error allocating regex string\n", 
                __FILE__, __LINE__);
        return NULL; 
    }
    regex[0] = '\0';

    const char *last_chosen = NULL;

    for(int i = 0; i < size; i++){
        const char *chosen;
        int valid;

        do {
            int index = rand() % dict_size;
            chosen = regex_dict[index];
            valid = 1;

            // Escludi simboli se sono in notIncludeThis
            if(strstr(notIncludeThis, chosen) != NULL){
                valid = 0;
            }

            // Evita simboli consecutivi vietati
            if(last_chosen != NULL) {
                if((strcmp(last_chosen, "+") == 0 && strcmp(chosen, "+") == 0) ||
                   (strcmp(last_chosen, "|") == 0 && strcmp(chosen, "|") == 0) ||
                   (strcmp(last_chosen, "$") == 0 && strcmp(chosen, "$") == 0)) {
                    valid = 0;
                }
            }

            // Evita che regex inizi con certi simboli
            if(i == 0 &&
              (strcmp(chosen, "|") == 0 ||
               strcmp(chosen, "$") == 0 ||
               strcmp(chosen, "+") == 0)) {
                valid = 0;
            }

        } while(!valid);

        strcat(regex, chosen);
        last_chosen = chosen;
    }

    return regex;
}


/*Generate a string from a regex previously generated, with a specific size, and how many time the regex are repeated to created the string */ 
char* generateStrFromRegex(char* regex, int size, int repeatTheRegex);

/*check is the input string is empty or not*/ 
int strIsEmpty(char*str){
	int len = strlen(str);
	if(len ==0){
		printf("IS Empty\n");
		return 1;
	}
	for(int i =0 ; i < len; i++){
		if(str[i]!='0'){
			printf("Not empty\n");
			return 1; 
		}
	}
	if(len> 0){
		printf("Not empty\n");
		return 1; 
	}
}

/*Deallocated the input string*/ 
int erase_str(char* str){
	free(str);
	return 0;
}
