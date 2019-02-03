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
 
# Flags para compilador
CC_FLAGS=-c         \
         -W         \
         -Wall      \
         -g      \
         -pedantic
 
# Comando usado no alvo limpo
RM = rm -rf
 
#
# Compilação e vinculação
#
all: objFolder $(PROJ_NAME)
 
$(PROJ_NAME): $(OBJ)
	@ echo 'Construindo binários usando o linker GCC: $@'
	$(CC) $^ -o $@
	@ echo 'Termidado construção de binario: $@'
	@ echo ' '
 
./objects/%.o: ./source/%.c ./source/%.h
	@ echo 'Construindo o alvo usando o compilador GCC: $<'
	$(CC) $< $(CC_FLAGS) -o $@
	@ echo ' '
 
./objects/main.o: ./source/main.c $(H_SOURCE)
	@ echo 'Construindo o alvo usando o compilador GCC: $<'
	$(CC) $< $(CC_FLAGS) -o $@
	@ echo ' '
 
objFolder:
	@ mkdir objects
 
.PHONY: all clean

clean:
	rm -rf ./objects/*.o 
 