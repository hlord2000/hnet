CC = gcc
CFLAGS = -Isrc/inc
SOURCES = $(wildcard src/*.c)
OBJECTS = $(patsubst src/%.c, build/%.o, $(SOURCES))
EXECUTABLE = hnet

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECUTABLE)

build/%.o: src/%.c
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build $(EXECUTABLE)
