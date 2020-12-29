CXX      := g++
CXXFLAGS := -w -std=c++17

LDFLAGS  := -L./lib/32
LIB_F = -lglew32s -lglew32 -lglfw3 -lopengl32 -lfreetype
BUILD    := ./build
OBJ_DIR  := $(BUILD)/objects
APP_DIR  := ./bin/64
TARGET   := main
INCLUDE  := -I./include
SRC_DIR := src/
SRC := $(wildcard $(SRC_DIR)/*.cpp)
SRC += $(wildcard $(SRC_DIR)/*.h)
SRC += $(wildcard $(SRC_DIR)/*.hpp)

OBJECTS := $(SOURCEDIR:%=$(OBJ_DIR)/%.o)

all: build $(APP_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: %.cpp 
	@echo "Compiling: " $@
	@mkdir -p; $(@D)
	$(CXX) $(INCLUDE) -o $@ -c $<

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(INCLUDE) $(LDFLAGS) -g ./src/main.cpp ./src/Common.cpp -o $(APP_DIR)/$(TARGET) ./lib/64/libglfw3dll.a $(OBJECTS) $(LIB_F) $(CXXFLAGS)

.PHONY: all build clean debug release

build:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(APP_DIR)
	

debug: CXXFLAGS += -DDEBUG -g
debug: all

release: all

clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(APP_DIR)/*