# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g3 -std=c11 -I$(INCLUDE_DIR) -pedantic -I./src -MMD -MP

# Directories
SRC_DIR := src
INCLUDE_DIR := include
BUILD_DIR := build
TEXTFILES_DIR := textFiles
PDF_DIR := recipePDFs
RECIPE_DIR := recipeFiles

# Project name
TARGET := recipeConverter

# Source and object files
SOURCES := $(wildcard $(SRC_DIR)/*.c)
OBJECTS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SOURCES))
DEPS := $(OBJS:.o=.d)

# Default target
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJECTS) | $(PDF_DIR)
	$(CC) $(OBJECTS) -o $(TARGET)
	
#Create PDFs Output Directory
$(PDF_DIR):
	@mkdir -p $@

# Rule to compile source files to object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
	
# Include dependencies
-include $(DEPS)

# Clean build files
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Phony targets
.PHONY: all clean
