CXX = g++
CXXFLAGS = -std=c++17 -Wno-everything

TARGET = tests_runner

SOURCES = $(shell find tests -name "*.cpp")

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

test: clean run