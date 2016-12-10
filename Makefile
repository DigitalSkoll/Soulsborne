CC=g++
CFLAGS=-g -Wall -Wextra -Wpedantic -Werror -std=c++11
INCLUDE=-Iinclude
DEPS=src/main.cpp
OUT=bin/soulsborne

soulsborne: $(DEPS)
	$(CC) $(CFLAGS) $(INCLUDE) $(DEPS) -o $(OUT) 2> error.log

run: $(OUT)
	$(OUT)

debug: $(OUT)
	gdb $(OUT)
