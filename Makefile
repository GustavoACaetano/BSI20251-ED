# Compiler
CC = gcc-11

# Compiler flags
CFLAGS = -Wall

# Source files
SRCS = main.c paciente/paciente.c paciente/paciente.h paciente/bdPaciente.c paciente/bdPaciente.h  utils/strings.c utils/strings.h 

# Object files
OBJS = $(SRCS:.c=.o)

# Executable name
TARGET = test_stack

# Phony targets
.PHONY: all compile run clean

# Default target (compile and run)
all: compile run

# Explicit compile target (produces the target program)
compile: $(TARGET)

# Run the executable
run: $(TARGET)
	./$(TARGET)

# Clean up
clean:
	rm -f $(OBJS) $(TARGET)

# Compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)