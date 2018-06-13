
BIN= bin
OBJ= obj
SRC= src
INC= include

all: prepare test clean

prepare:
	mkdir -p bin obj
	touch bin/*
	rm bin/*

test: $(BIN)/gio
	$(BIN)/gio

$(BIN)/gio: $(OBJ)/main.o $(OBJ)/graphs.o
	g++ $^ -o $@

$(OBJ)/main.o: $(SRC)/main.cpp
	g++ -I $(INC) -c $< -o $@

$(OBJ)/graphs.o: $(SRC)/graphs.cpp
	g++ -I $(INC) -c $< -o $@

clean:
	rm obj/*

.PHONY: prepare test clean
