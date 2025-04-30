TARGET = lab
CC = gcc
CFLAGS = -g -Iinclude

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

LLRB_DIR = $(SRC_DIR)/llrb
CMD_DIR = $(SRC_DIR)/cmd/app
DIALOGUE_DIR = $(SRC_DIR)/dialogue
LOGIC_DIR = $(SRC_DIR)/logic

ifeq ($(lib-type), s)
    LIB_EXTENSION = .a
    COMP = 
else
    LIB_EXTENSION = .so
    COMP = -Wl,-rpath,../$(OBJ_DIR)
endif

LIBRARY = $(OBJ_DIR)/lib$(TARGET)$(LIB_EXTENSION)

OBJ = $(OBJ_DIR)/main.o $(OBJ_DIR)/dialogue.o $(OBJ_DIR)/logic.o
LIB_OBJ = $(OBJ_DIR)/llrbtree.o

all: dirs $(BIN_DIR)/$(TARGET)

dirs:
	mkdir -p $(OBJ_DIR)
	mkdir -p $(BIN_DIR)

$(BIN_DIR)/$(TARGET): $(LIBRARY) $(OBJ)
	$(CC) $(OBJ) -L$(OBJ_DIR) -l$(TARGET) -o $@ $(COMP) $(CFLAGS)

$(LIBRARY): $(LIB_OBJ)
ifeq ($(lib-type), d)
	$(CC) -shared -o $@ $^
else
	ar rcs $@ $^
endif

$(OBJ_DIR)/main.o: $(CMD_DIR)/main.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJ_DIR)/dialogue.o: $(DIALOGUE_DIR)/dialogue.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJ_DIR)/logic.o: $(LOGIC_DIR)/logic.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJ_DIR)/llrbtree.o: $(LLRB_DIR)/llrbtree.c
ifeq ($(lib-type), d)
	$(CC) -c -fPIC $< -o $@ $(CFLAGS)
else
	$(CC) -c $< -o $@ $(CFLAGS)
endif

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
