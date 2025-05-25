CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -D_POSIX_C_SOURCE=200809L
TARGET = programa_math

$(TARGET): 1_math_expressions.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGET) *.o