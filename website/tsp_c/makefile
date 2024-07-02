# Define the compiler
CC = gcc

# Define any compile-time flags
CFLAGS = -Wall -g

# Define any directories containing header files other than /usr/include
INCLUDES =

# Define library paths in addition to /usr/lib
LFLAGS =

# Define any libraries to link into executable
LIBS = -lm

# Define the source files for the 'main' target
MAIN_SRCS = main.c 

# Define the source files for the 'test' target
TEST_SRCS = test.c 

# Define the object files for the 'main' target
MAIN_OBJS = $(MAIN_SRCS:.c=.o)

# Define the object files for the 'test' target
TEST_OBJS = $(TEST_SRCS:.c=.o)

# Define the executable file for the 'main' target
MAIN = main

# Define the executable file for the 'test' target
TEST = test

.PHONY: all clean

# Default to build both targets
all: $(MAIN) $(TEST)

# Rule for building the 'main' executable
$(MAIN): $(MAIN_OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(MAIN_OBJS) $(LFLAGS) $(LIBS)

# Rule for building the 'test' executable
$(TEST): $(TEST_OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TEST) $(TEST_OBJS) $(LFLAGS) $(LIBS)

# To obtain object files
.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Cleaning old files before new make
clean:
	$(RM) *.o *~ $(MAIN) $(TEST)
