CC=g++
CFLAGS=-g -Wall -Wextra -Wpedantic -Werror
INCLUDE=-Iinclude
DEPS=src/main.cpp
OUT=bin/soulsborne

soulsborne: $(DEPS)
	$(CC) $(CFLAGS) $(INCLUDE) $(DEPS) -o $(OUT)

run: $(OUT)
	$(OUT)