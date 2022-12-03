CC=g++
CFLAGS=-c -Wall -std=c++2a -g
LDFLAGS=
SOURCES=string_compressor_test.cpp string_compressor.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=string_compressor

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o string_compressor