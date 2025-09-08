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

            // Escludi simboli se contengono caratteri in notIncludeThis
            for(int j = 0; j < strlen(notIncludeThis); j++){
                char charToExclude = notIncludeThis[j];
                
                // Controlla se il carattere è contenuto nel pattern regex
                if((charToExclude >= 'a' && charToExclude <= 'z' && strcmp(chosen, "[a-z]") == 0) ||
                   (charToExclude >= 'A' && charToExclude <= 'Z' && strcmp(chosen, "[A-Z]") == 0) ||
                   (charToExclude >= '0' && charToExclude <= '9' && (strcmp(chosen, "[0-9]") == 0 || strcmp(chosen, "\\d") == 0)) ||
                   (charToExclude == '+' && strcmp(chosen, "+") == 0) ||
                   (charToExclude == '*' && strcmp(chosen, "*") == 0) ||
                   (charToExclude == '?' && strcmp(chosen, "?") == 0) ||
                   (charToExclude == '|' && strcmp(chosen, "|") == 0) ||
                   (charToExclude == '(' && strcmp(chosen, "(") == 0) ||
                   (charToExclude == ')' && strcmp(chosen, ")") == 0) ||
                   (charToExclude == '^' && strcmp(chosen, "^") == 0) ||
                   (charToExclude == '$' && strcmp(chosen, "$") == 0) ||
                   (charToExclude == '.' && strcmp(chosen, ".") == 0) ||
                   // Caratteri alfanumerici (lettere e numeri)
                   (((charToExclude >= 'a' && charToExclude <= 'z') || 
                     (charToExclude >= 'A' && charToExclude <= 'Z') || 
                     (charToExclude >= '0' && charToExclude <= '9')) && strcmp(chosen, "\\w") == 0) ||
                   // Spazi bianchi
                   (((charToExclude == ' ' || charToExclude == '\t' || charToExclude == '\n' || charToExclude == '\r') && strcmp(chosen, "\\s") == 0)) ||
                   // Pattern di ripetizione
                   (((charToExclude >= '2' && charToExclude <= '5') && strcmp(chosen, "{2,5}") == 0))) {
                    valid = 0;
                    break;
                }
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
char* generateStrFromRegex(char* regex, int size, int repeatTheRegex){
	char *str = (char*)malloc(sizeof(char)*(size + 1)); 
	if(str == NULL)
	{
		fprintf(stderr, "generateStrFromRegex --> Malloc error\n");
		return NULL;
	}
	
	str[0] = '\0'; // Inizializza stringa vuota
	int str_pos = 0;
	
	for(int repeat = 0; repeat < repeatTheRegex && str_pos < size; repeat++)
	{
		for(int i = 0; i < strlen(regex) && str_pos < size; i++)
		{
			char current_char = regex[i];
			
			// Interpreta i pattern regex e genera caratteri appropriati
			if(current_char == '\\' && i + 1 < strlen(regex))
			{
				char next_char = regex[i + 1];
				if(next_char == 'd') // \d - cifra
				{
					str[str_pos++] = '0' + (rand() % 10);
					i++; // Salta il prossimo carattere
				}
				else if(next_char == 'w') // \w - carattere alfanumerico
				{
					char alphanumeric[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
					str[str_pos++] = alphanumeric[rand() % strlen(alphanumeric)];
					i++; // Salta il prossimo carattere
				}
				else if(next_char == 's') // \s - spazio bianco
				{
					char whitespace[] = " \t\n";
					str[str_pos++] = whitespace[rand() % strlen(whitespace)];
					i++; // Salta il prossimo carattere
				}
			}
			else if(current_char == '[' && i + 4 < strlen(regex) && regex[i + 4] == ']')
			{
				// Pattern [a-z], [A-Z], [0-9]
				if(regex[i + 1] == 'a' && regex[i + 2] == '-' && regex[i + 3] == 'z')
				{
					str[str_pos++] = 'a' + (rand() % 26);
				}
				else if(regex[i + 1] == 'A' && regex[i + 2] == '-' && regex[i + 3] == 'Z')
				{
					str[str_pos++] = 'A' + (rand() % 26);
				}
				else if(regex[i + 1] == '0' && regex[i + 2] == '-' && regex[i + 3] == '9')
				{
					str[str_pos++] = '0' + (rand() % 10);
				}
				i += 4; // Salta tutto il pattern [x-y]
			}
			else if(current_char == '.')
			{
				// . - qualsiasi carattere (escluso newline)
				char printable[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_+-=[]{}|;:,.<>?";
				str[str_pos++] = printable[rand() % strlen(printable)];
			}
			else if(current_char == '+' || current_char == '*' || current_char == '?')
			{
				// Quantificatori - per semplicità li ignoriamo nella generazione base
				continue;
			}
			else if(current_char == '{')
			{
				// Pattern {2,5} - salta tutto fino alla }
				while(i < strlen(regex) && regex[i] != '}') i++;
			}
			else if(current_char == '|' || current_char == '(' || current_char == ')')
			{
				// Operatori logici - per semplicità li ignoriamo
				continue;
			}
			else if(current_char == '^' || current_char == '$')
			{
				// Ancoraggi - li ignoriamo nella generazione
				continue;
			}
			else
			{
				// Carattere letterale
				str[str_pos++] = current_char;
			}
		}
	}
	
	str[str_pos] = '\0'; // Termina la stringa
	return str;
}

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

char* concatenateMultipleStringNewRegex(int size, char* notIncludeThis){
	if(notIncludeThis ==NULL)
	{
		printf("%s %d\n", __FILE__, __LINE__);
		return NULL; 
	}
	char* regFist = regexGenerator(size, notIncludeThis);
	char* strFirst = generateStrFromRegex(regFist, size, 1); 
	char* strTwo  = generateStrFromRegex(regFist, size, 1); 
	if(regFist == NULL || strFirst == NULL || strTwo ==NULL)
	{
		printf("%s %d\n", __FILE__, __LINE__);
		return NULL;
	}
	char* concatenate = (char*)malloc((sizeof(char) * (size *2))+1);
	if(concatenate == NULL){
		printf("%s %d\n", __FILE__, __LINE__); 
		return NULL;
	} 
	
	// Inizializza la stringa concatenate
	concatenate[0] = '\0';
	
	// Usa strcat per concatenare in modo sicuro
	strncat(concatenate, strFirst, size);
	strncat(concatenate, strTwo, size);
	#ifdef _Debug
		printf("\nDEBUG\t\n");
		printf("Concatenate string generated from %s and %s is %s\n",strFirst, strTwo, concatenate);
	#endif
	
	// Libera la memoria allocata
	erase_str(regFist);
	erase_str(strFirst);
	erase_str(strTwo);
	
	return concatenate;
	
}
char* concatenateExistesRegex(char* regex, char* regex2)
{
	if(regex == NULL || regex2 == NULL)
	{
		printf("%s %d\n", __FILE__, __LINE__);
		return NULL; 
	}
}

/*Deallocated the input string*/ 
int erase_str(char* str){
	free(str);
	return 0;
}
