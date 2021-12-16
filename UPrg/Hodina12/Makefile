CFLAGS=-Wall -O2

SOURCE=$(wildcard *.c)
TARGET=$(patsubst %.c,%, $(SOURCE))

all: $(TARGET) build run

$(TARGET):
	$(CC) $(CFLAGS) $(SOURCE) -o $@

build: $(TARGET)

run:
	./$(TARGET)

.PHONY: $(TARGET)