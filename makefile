# Nome do projeto
PROJ_NAME=Sistema
 
# Arquivos .c
C_SOURCE=$(wildcard ./source/*.c)
 
# Arquivos .h
H_SOURCE=$(wildcard ./source/*.h)
 
# Arquivos Objetos
OBJ=$(subst .c,.o,$(subst source,objects,$(C_SOURCE)))
 
# Compilador e linker
CC=gcc
 
ifdef OS
	RM = del objects\\*.o Sistema.exe
	ICO=ico.o -o
  else
  	ifeq ($(shell uname), Linux)
      RM = rm -f ./objects/*.o $(PROJ_NAME) *~
	  ICO=-o
   	endif
endif

# Flags para compilador
CC_FLAGS=-c         \
         -W         \
         -Wall      \
         -g      \
         -pedantic
 
# Comando usado no alvo limpo

 
#
# Compilação e vinculação
#
all: $(PROJ_NAME)
 
$(PROJ_NAME): $(OBJ)
	@ echo 'Construindo binários usando o linker GCC: $@'
	$(CC) $^ $(ICO) $@
	@ echo 'Termidado construção de binario: $@'
	@ echo ' '

./objects/%.o: ./source/%.c ./source/%.h
	@ echo 'Construindo os objetos .o com GCC: $<'
	$(CC) $< $(CC_FLAGS) -o $@
	@ echo ' '

./objects/main.o: ./source/main.c $(H_SOURCE)
	@ echo 'Construindo o main.o com GCC: $<'
	$(CC) $< $(CC_FLAGS) -o $@
	@ echo ' '

objFolder:
	@ mkdir objects


clean:
	@ $(RM)
	
.PHONY: all clean