# makefile

all: test

test: gio
	./gio

gio: main.cpp remove
	g++ $< -o $@

remove:
	touch gio
	rm gio

.PHONY: test remove
