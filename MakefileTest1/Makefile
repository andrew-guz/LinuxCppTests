CPP = g++

CPPFLAGS = -g -Wall

HEADER_DIR := ./include

SOURCE_DIR := ./source

OBJ_DIR := ./obj

BIN_DIR := ./bin

TARGET := Test

BUILD = $(CPP) $(CPPFLAGS) -I$(HEADER_DIR)

SRC_FILES := $(wildcard $(SOURCE_DIR)/*.cpp)

OBJ_FILES := $(patsubst $(SOURCE_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

all: clean makedirs $(TARGET)

build: makedirs $(TARGET)

makedirs:
	mkdir -p $(OBJ_DIR)
	mkdir -p $(BIN_DIR)	

$(TARGET): $(OBJ_FILES)
	$(BUILD) main.cpp -o $(BIN_DIR)/$@ $^
	
$(OBJ_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	$(BUILD) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(BIN_DIR)

.PHONY: all makedirs clean
