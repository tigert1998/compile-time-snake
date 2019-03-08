CC = clang++
STD_FLAG = -std=c++11
SRC_DIR = ../src
BIN_DIR = ../bin

init: $(SRC_DIR)/generator.cpp
	if [ ! -d "$(BIN_DIR)" ]; then mkdir "$(BIN_DIR)"; fi
	$(CC) $(STD_FLAG) $< -o $(BIN_DIR)/generator

run:
	python run.py
