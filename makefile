
BIN = bin
OBJ = obj
SRC = src

all: prepare test clean

prepare:
	touch bin/*
	rm bin/*

test: $(BIN)/gio
	$(BIN)/gio

$(BIN)/gio: $(OBJ)/main.o $(OBJ)/graphs.o
	g++ $^ -o $@

$(OBJ)/main.o: $(SRC)/main.cpp
	g++ -c $< -o $@

$(OBJ)/graphs.o: $(SRC)/graphs.cpp
	g++ -c $< -o $@

clean:
	rm obj/*

.PHONY: prepare test clean
