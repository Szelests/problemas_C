CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -D_POSIX_C_SOURCE=200809L
TARGET = get_customer

$(TARGET): get_customer.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGET) *.o