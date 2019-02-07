# Nome do projeto
PROJ_NAME=Sistema
 
# Arquivos .c
C_SOURCE=$(wildcard ./src/*.c)
 
# Arquivos .h
H_SOURCE=$(wildcard ./includes/*.h)

# Libs
C_LIBS=./objects/sqlite3.o

DIR_LIB = ./lib/ 
DIR_SRC = ./src/ 
DIR_INC = ./includes/ 
# Arquivos Objetos
#OBJ=objects*.o
OBJ=$(subst .c,.o,$(subst src,objects,$(C_SOURCE)))

# Compilador e linker
CC=gcc
 
ifdef OS
	RM = del objects\\*.o Sistema.exe
	
  else
  	ifeq ($(shell uname), Linux)
      RM = rm -f ./objects/*.o $(PROJ_NAME) *~
	  
   	endif
endif

# Flags para compilador
CC_FLAGS=-c -W -Wall -pedantic -g -I includes/
 
# Compilação e vinculação

all: $(PROJ_NAME)
 
$(PROJ_NAME): $(OBJ) 
	$(CC) $^ -o $@ 


./objects/%.o: ./src/%.c
	$(CC) $< $(CC_FLAGS) -o $@

./objects/main.o: ./src/main.c
	$(CC) ./src/main.c $(CC_FLAGS)  -o $@

./objects/sqlite3.o: ./lib/sqlite3.c
	$(CC) ./lib/sqlite3.c $(CC_FLAGS) -o $@
clean:
	@ $(RM)
	
.PHONY: all clean