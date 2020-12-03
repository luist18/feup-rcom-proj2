CC = gcc

BIN_DIR = bin
SRC_DIR = src

COMPILATION_EXTENSIONS = -Wall -lm -o

SRC_FILES = ${SRC_DIR}/main.c ${SRC_DIR}/util.c ${SRC_DIR}/connection.c

make: ${SRC_FILES}
	@mkdir -p $(BIN_DIR)
	@$(CC) -o $(BIN_DIR)/download ${SRC_FILES}

clean:
	@rm -f {BIN_DIR}/*