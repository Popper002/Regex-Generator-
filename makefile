CC = gcc
CFLAGS = -g -D MAC_OS
DEST_LIB = lib
DEST_BIN = bin
RM_ALL_FILE = rm
MAC = -D MAC_OS
# Target principale per creare tutto
all: libregex.a main

# Creazione della libreria statica
libregex.a: out/regex.o
	ar rcs $(DEST_LIB)/libregex.a out/regex.o

# Compilazione del file oggetto per la libreria
out/regex.o: src/regex.c
	$(CC) $(CFLAGS) -fPIC -c src/regex.c -o out/regex.o

# Compilazione del programma principale che utilizza la libreria
main: src/main.c libregex.a
	$(CC) $(CFLAGS) src/main.c -o $(DEST_BIN)/main $(DEST_LIB)/libregex.a

# Pulizia dei file generati
clean:
	$(RM_ALL_FILE) $(DEST_LIB)/*.a $(DEST_BIN)/* out/*.o

#Dinamy lib compilation
libregex.so: out/regex.o
	$(CC) -shared -o $(DEST_LIB)/libregex.so out/regex.o

# Compilazione del programma principale che utilizza la libreria dinamica
main_dynamic: src/main.c libregex.so
	$(CC) $(CFLAGS) src/main.c -o $(DEST_BIN)/main_dynamic -L$(DEST_LIB) -lregex
# Esecuzione del programma principale con la libreria dinamica
run_dynamic: main_dynamic
	LD_LIBRARY_PATH=$(DEST_LIB):$$LD_LIBRARY_PATH ./$(DEST_BIN)/main_dynamic logfile.txt DEBUG
