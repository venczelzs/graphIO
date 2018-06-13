
BIN= bin
OBJ= obj
SRC= src
INC= include
TST= tests

all: prepare test main clean

prepare:
	mkdir -p bin obj
	touch bin/gio
	rm bin/*

main: $(BIN)/gio

test: $(TST)/$(BIN)/tests
	$(TST)/$(BIN)/tests

# Removing *.o files
clean:
	rm $(OBJ)/*.o
	rm $(TST)/$(OBJ)/*.o

# Executable for testing
$(TST)/$(BIN)/tests: $(OBJ)/graphs.o $(TST)/$(OBJ)/tests.o
	g++ $^ -o $@

# Object files for testing
$(TST)/$(OBJ)/tests.o: $(TST)/$(SRC)/tests.cpp
	g++ -I $(INC) -c $< -o $@

# Main executable
$(BIN)/gio: $(OBJ)/main.o $(OBJ)/graphs.o
	g++ $^ -o $@

# Object files for main executable
$(OBJ)/main.o: $(SRC)/main.cpp
	g++ -I $(INC) -c $< -o $@

$(OBJ)/graphs.o: $(SRC)/graphs.cpp
	g++ -I $(INC) -c $< -o $@

.PHONY: prepare test main clean
