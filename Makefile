APP_NAME=digit-ai
APP_VERSION=0.1.0

CC=gcc
CFLAGS=-Iinclude -Wall -Wextra -Werror
LDFLAGS=-lraylib -lm

SRC_DIR=src
APP_DIR=$(SRC_DIR)/app
SRCS=$(wildcard $(SRC_DIR)/*.c) $(wildcard $(APP_DIR)/*.c)
OBJS=$(SRCS:.c=.o)
EXEC=$(APP_NAME)

.PHONY: all clean run

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)

run: $(EXEC)
	./$(EXEC)
