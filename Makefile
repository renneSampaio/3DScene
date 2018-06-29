CXX := g++
SRC_DIR  := ./src
BUILD_DIR := build
TARGET := bin/main

SOURCE_EXT := cpp
SOURCES := $(shell find $(SRC_DIR) -type f -name *.$(SOURCE_EXT))
OBJECTS := $(patsubst $(SRC_DIR)/%,$(BUILD_DIR)/%,$(SOURCES:.$(SOURCE_EXT)=.o))

CXXFLAGS = -g -Wall -std=c++11
LIBS := -lGL -lGLU -static -lglut -lGLEW
INC := -Iinclude

$(TARGET): $(OBJECTS)
	@mkdir -p bin
	$(CXX) $^ -o $(TARGET) $(LIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.$(SOURCE_EXT)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(INC) -c -o $@ $<

.PHONY: clean run
clean:
	rm -r $(BUILD_DIR) bin
run: $(TARGET)
	./$<
