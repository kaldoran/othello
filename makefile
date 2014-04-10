
DEBUG=YES

# Dossier pour la compilation

DEST_SRC = SRC
DEST_INC = INC
DEST_OBJ = OBJ

#El Compilator
CC = gcc

# Flags de compilation
CFLAGS = -Wall

ifeq ($(DEBUG), YES)
	CFLAGS += -g -DDEBUG
endif

SRC = $(foreach dir, $(DEST_SRC), $(wildcard $(dir)/*.c))
OBJ = $(addsuffix .o, $(basename $(subst ${DEST_SRC}, ${DEST_OBJ}, ${SRC})))


#nom de l'executable
BIN = projet

# Make

all: creatdir $(BIN)

creatdir:
	@mkdir -p $(DEST_OBJ)

install: $(BIN)

$(BIN): $(OBJ)
	@$(CC) $(CFLAGS) -I$(DEST_INC) -o ${BIN} $(OBJ)
	@echo "\n\t"Création de $@
	@echo Pour lancer le programme utiliser : ./$@

$(DEST_OBJ)/%.o: $(DEST_SRC)/%.c
	@$(CC) $(CFLAGS) -I$(DEST_INC) -c $< -o $@
	@echo Creation de $@

# Clean
uninstall: clean

clean:
	@rm -f $(DEST_OBJ)/*.o
	@rm -rf $(DEST_OBJ)
	@rm -f $(BIN)
	@find . -name \*~ -exec rm \-fv {} \;
	@echo  "\t"Le programme $(BIN) a bien été supprimé

rebuild: uninstall creatdir install
