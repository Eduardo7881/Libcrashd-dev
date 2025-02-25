# Compiler
CXX = g++

# Flags
CXXFLAGS = -Wall -Wextra -std=c++17
GTKFLAGS = $(shell pkg-config --cflags --libs gtk+-3.0)

# Paths
SRC_DIR = src
BUILD_DIR = build
LIB_NAME = libcrashd.a

# Source and object files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Check GTK+3 installation
CHECK_GTK = $(shell pkg-config --exists gtk+-3.0 && echo 1 || echo 0)

# Default target
all: check_gtk $(LIB_NAME)

# Verify if GTK is installed
check_gtk:
	@if [ "$(CHECK_GTK)" -eq "0" ]; then \
		echo "Error: GTK+3 is not installed. Please install it first."; \
		exit 1; \
	fi

# Create build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Compile source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(GTKFLAGS) -c $< -o $@

# Create static library
$(LIB_NAME): $(OBJS)
	ar rcs $@ $^

# Clean build files
clean:
	rm -rf $(BUILD_DIR) $(LIB_NAME)
