# the compiler to use
CC = clang++
  
# target name for input and output
TARGET = main

# build taget directory and src directory
BUILD_FOLDER = bin
SOURCE_FOLDER = src

# all include directories
INCLUDES = -I/Library/Frameworks/SDL2.framework/Headers -I/Library/Frameworks/SDL2_image.framework/Headers -I./include

# framework path
FRAMEWORKS_PATH = /Library/Frameworks
FRAMEWORKS = -framework SDL2 -framework SDL2_image

all: output $(TARGET)

# create build directory if it does not exist
output:
	mkdir -p $(BUILD_FOLDER)

# compile program
$(TARGET): $(SOURCE_FOLDER)/$(/$(TARGET).cpp
	$(CC) ./$(SOURCE_FOLDER)/*.cpp $(INCLUDES) -F$(FRAMEWORKS_PATH) $(FRAMEWORKS) -o ./$(BUILD_FOLDER)/$(TARGET)