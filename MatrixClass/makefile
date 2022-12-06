# List your *.h files (if you do not have them in your project then leave the variable "headers" empty):
headers = Poly.h

# List your *.cpp files:
sources = Poly.cpp testPoly.cpp

# Specify name of your program:
executable = testPoly

$(executable): $(headers) $(sources)
	g++ -g -Wall -pedantic $(sources) -o $(executable)

.PHONY: clean
clean:
	rm $(executable)

.PHONY: check
check: $(executable)
	valgrind --leak-check=full --track-origins=yes ./$(executable)
