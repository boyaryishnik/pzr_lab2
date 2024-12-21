CC = gcc
CFLAGS = -Wall -g
OBJ = main.o sed_operations.o
TARGET = sed_simplified

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJ) $(TARGET)

test:
	./$(TARGET) input.txt 's/old_text/new_text/'
	./$(TARGET) input.txt '/regex/d'
	./$(TARGET) input.txt 's/^/prefix/'
	./$(TARGET) input.txt 's/$/suffix/'
