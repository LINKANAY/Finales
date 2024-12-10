CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99 -g
SOURCES = stack.c check_balance.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = check_balance

SOURCES_TEST = stack.c test-stack.c
OBJECTS_TEST = $(SOURCES_TEST:.c=.o) 
TARGET_TEST = test


.PHONY: clean

all: $(TARGET)

valgrind: $(TARGET)
	valgrind --error-exitcode=2 --leak-check=full ./$(TARGET)

gdb-test: $(TARGET)
	@echo "run" > gdb_commands.txt
	@echo "backtrace" >> gdb_commands.txt
	@echo "quit" >> gdb_commands.txt
	gdb -x gdb_commands.txt ./$(TARGET)
	rm gdb_commands.txt

$(TARGET_TEST): $(OBJECTS_TEST)
	$(CC) $(CFLAGS) -o $(TARGET_TEST) $(OBJECTS_TEST) $(LFLAGS) $(LIBS)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) $(LFLAGS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJECTS) $(OBJECTS_TEST) $(TARGET) $(TARGET_TEST)
