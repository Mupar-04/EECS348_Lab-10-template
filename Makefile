# Name of executable and input file
EXEC = calc
INPUT = test.txt


# Default target
all: $(EXEC)
	@./$(EXEC)


# Compile target
$(EXEC): main.o calculator.o
	g++ -std=c++11 -o $(EXEC) main.o calculator.o

main.o: main.cpp calculator.hpp
	g++ -std=c++11 -c main.cpp

calculator.o: calculator.cpp calculator.hpp
	g++ -std=c++11 -c calculator.cpp

# Clean build files
clean:
	rm -f *.o $(EXEC)
