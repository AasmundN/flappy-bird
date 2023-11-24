# the compiler to use
CC = clang++
  
# target name for input and output
TARGET = main

# build taget directory and src directory
BUILD_FOLDER = build
SOURCE_FOLDER = src

# all include directories
INCLUDES = -I/Library/Frameworks/SDL2.framework/Headers -I./include

# framework path
FRAMEWORKS_PATH = /Library/Frameworks
FRAMEWORK = SDL2

all: output $(TARGET)

# create build directory if it does not exist
output:
	mkdir -p $(BUILD_FOLDER)

# compile program
$(TARGET): $(SOURCE_FOLDER)/$(/$(TARGET).cpp
	$(CC) ./$(SOURCE_FOLDER)/*.cpp $(INCLUDES) -F$(FRAMEWORKS_PATH) -framework $(FRAMEWORK) -o ./$(BUILD_FOLDER)/$(TARGET)