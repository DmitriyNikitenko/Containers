CC = clang++
CFLAGS = -pedantic-errors -gdwarf-4 -std=c++17 -Wall -Wextra \
  -Wno-unused-variable -Wno-self-assign -Wno-deprecated-copy -Wno-reorder -Wno-unused-result \
  -Wno-unused-comparison -Wno-self-move -Wno-sign-compare
LDFLAGS =

SOURCES = main.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = containers_app

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

.PHONY: all clean
