# Name of executable and input file
EXEC = calc
INPUT = test.txt

# Default target
all: $(EXEC)
	@echo "Running with input file: $(INPUT)"
	@./$(EXEC) $(INPUT)

# Compile target
$(EXEC): main.o calculator.o
	g++ -o $(EXEC) main.o calculator.o

main.o: main.cpp calculator.hpp
	g++ -c main.cpp

calculator.o: calculator.cpp calculator.hpp
	g++ -c calculator.cpp

# Clean build files
clean:
	rm -f *.o $(EXEC)
