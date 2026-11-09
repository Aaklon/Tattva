CXX ?= g++
CXXFLAGS ?= -std=c++17 -O2 -Wall -Wextra
TARGET ?= parser
SRC ?= compiler/parser.cpp
DIR ?= .
OUT ?= .

.PHONY: all build compile run clean

all: $(TARGET)
	./$(TARGET) $(DIR) $(OUT)

build: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

compile: $(TARGET)
	./$(TARGET) $(DIR) $(OUT)

run: $(TARGET)
	./$(TARGET) $(DIR) $(OUT)

clean:
	rm -f $(TARGET) index.html style.css app.js
