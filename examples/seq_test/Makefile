.PHONY: all clean

TARGET=seq_test

all: $(TARGET)

$(TARGET): $(TARGET).c
	gcc -g -O0 $(TARGET).c -o $(TARGET)

clean:
	rm -rf $(TARGET)
