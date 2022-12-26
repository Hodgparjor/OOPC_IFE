# List your *.h files (if you do not have them in your project then leave the variable "headers" empty):
#headers = Employee.h Map.h
headers = Bookshelf.h Map.h

# List your *.cpp files:
#sources = TestMap.cpp
sources = TestBookshelf.cpp

# Specify name of your program:
#executable = testMap
executable = testBookshelf

$(executable): $(headers) $(sources)
	g++ -g -Wall -pedantic $(sources) -o $(executable)

.PHONY: clean
clean:
	rm $(executable)

.PHONY: check
check: $(executable)
	valgrind --leak-check=full --track-origins=yes ./$(executable)
