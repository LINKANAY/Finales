TARGET  = main
SOURCES = $(wildcard *.c)
HEADERS = $(wildcard *.h)
OBJECTS = $(SOURCES:.c=.o)
LIBS =


CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99 -g

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(LIBS) -o $@ $(OBJECTS)

clean:
	rm -f $(TARGET) $(OBJECTS)

gdb: $(TARGET)
	@echo "run" > gdb_commands.txt
	@echo "backtrace" >> gdb_commands.txt
	@echo "quit" >> gdb_commands.txt
	gdb -x gdb_commands.txt ./$(TARGET)
	rm gdb_commands.txt


valgrind: $(TARGET)
	valgrind --leak-check=full --show-reachable=yes ./$(TARGET) -vf input/*.in