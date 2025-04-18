# Name of executable
EXEC = calc

# Default target: just compile, don't run
all: $(EXEC)

# Build the executable
$(EXEC): main.o calculator.o
	g++ -std=c++11 -o $(EXEC) main.o calculator.o

# Compile object files
main.o: main.cpp calculator.hpp
	g++ -std=c++11 -c main.cpp

calculator.o: calculator.cpp calculator.hpp
	g++ -std=c++11 -c calculator.cpp

# Clean build files
clean:
	rm -f *.o $(EXEC)
