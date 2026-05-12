# Makefile for debug.h unit tests
# Author: GitHub Copilot
# Date: 2025-12-17
#
# Usage:
#   make          - Build all debug mode tests
#   make release  - Build all release (NDEBUG) mode tests
#   make test     - Run all tests
#   make clean    - Remove all build artifacts
#   make all      - Build everything (debug and release)

# Compiler settings
CC = gcc
CXX = g++
# Note: -Wpedantic removed because debug.h uses GCC extensions like __PRETTY_FUNCTION__
CFLAGS_DEBUG = -std=c2x -g -O0 -Wall -Wextra -rdynamic -fsanitize=address,undefined
CXXFLAGS_DEBUG = -std=c++23 -g -O0 -Wall -Wextra -rdynamic -fsanitize=address,undefined
CFLAGS_RELEASE = -std=c2x -O2 -DNDEBUG -Wall -Wextra
CXXFLAGS_RELEASE = -std=c++23 -O2 -DNDEBUG -Wall -Wextra
# Thread safety requires pthread (no sanitizer to avoid interference)
CFLAGS_THREADSAFE = -std=c2x -g -O0 -Wall -Wextra -rdynamic -pthread

# Sanitizer flags for linking
SANITIZE_FLAGS = -fsanitize=address,undefined

# Output directory
BUILD_DIR = build

# Test source files
C23_TEST_SRC = test_debug_c23.c
CPP23_TEST_SRC = test_debug_cpp23.cpp
C23_NDEBUG_SRC = test_debug_ndebug_c23.c
CPP23_NDEBUG_SRC = test_debug_ndebug_cpp23.cpp
C23_FEATURES_SRC = test_debug_features_c23.c
C23_THREADSAFE_SRC = test_debug_threadsafe_c23.c

# Test executables (debug mode)
C23_TEST_DEBUG = $(BUILD_DIR)/test_debug_c23_debug
CPP23_TEST_DEBUG = $(BUILD_DIR)/test_debug_cpp23_debug
C23_FEATURES_DEBUG = $(BUILD_DIR)/test_debug_features_c23
C23_THREADSAFE_DEBUG = $(BUILD_DIR)/test_debug_threadsafe_c23

# Test executables (release/NDEBUG mode)
C23_TEST_RELEASE = $(BUILD_DIR)/test_debug_c23_release
CPP23_TEST_RELEASE = $(BUILD_DIR)/test_debug_cpp23_release
C23_NDEBUG_TEST = $(BUILD_DIR)/test_debug_ndebug_c23
CPP23_NDEBUG_TEST = $(BUILD_DIR)/test_debug_ndebug_cpp23

# Default target: build debug mode tests
.PHONY: debug
debug: $(BUILD_DIR) $(C23_TEST_DEBUG) $(CPP23_TEST_DEBUG) $(C23_FEATURES_DEBUG) $(C23_THREADSAFE_DEBUG)
	@echo "Debug mode tests built successfully"

# Build release mode tests
.PHONY: release
release: $(BUILD_DIR) $(C23_TEST_RELEASE) $(CPP23_TEST_RELEASE) $(C23_NDEBUG_TEST) $(CPP23_NDEBUG_TEST)
	@echo "Release mode tests built successfully"

# Build everything
.PHONY: all
all: debug release
	@echo "All tests built successfully"

# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Debug mode builds (with sanitizers)
$(C23_TEST_DEBUG): $(C23_TEST_SRC) ../debug.h
	$(CC) $(CFLAGS_DEBUG) -o $@ $(C23_TEST_SRC)

$(CPP23_TEST_DEBUG): $(CPP23_TEST_SRC) ../debug.h
	$(CXX) $(CXXFLAGS_DEBUG) -o $@ $(CPP23_TEST_SRC)

# New features test (with timestamps and colors)
$(C23_FEATURES_DEBUG): $(C23_FEATURES_SRC) ../debug.h
	$(CC) $(CFLAGS_DEBUG) -o $@ $(C23_FEATURES_SRC)

# Thread safety test (requires pthread)
$(C23_THREADSAFE_DEBUG): $(C23_THREADSAFE_SRC) ../debug.h
	$(CC) $(CFLAGS_THREADSAFE) -o $@ $(C23_THREADSAFE_SRC)

# Release mode builds (without sanitizers)
$(C23_TEST_RELEASE): $(C23_TEST_SRC) ../debug.h
	$(CC) $(CFLAGS_RELEASE) -o $@ $(C23_TEST_SRC)

$(CPP23_TEST_RELEASE): $(CPP23_TEST_SRC) ../debug.h
	$(CXX) $(CXXFLAGS_RELEASE) -o $@ $(CPP23_TEST_SRC)

# NDEBUG specific tests
$(C23_NDEBUG_TEST): $(C23_NDEBUG_SRC) ../debug.h
	$(CC) $(CFLAGS_RELEASE) -o $@ $(C23_NDEBUG_SRC)

$(CPP23_NDEBUG_TEST): $(CPP23_NDEBUG_SRC) ../debug.h
	$(CXX) $(CXXFLAGS_RELEASE) -o $@ $(CPP23_NDEBUG_SRC)

# Run tests
.PHONY: test
test: all
	@echo ""
	@echo "========================================"
	@echo "Running debug.h Unit Tests"
	@echo "========================================"
	@echo ""
	@echo "=== C23 Debug Mode Tests ==="
	@$(C23_TEST_DEBUG) || exit 1
	@echo ""
	@echo "=== C++23 Debug Mode Tests ==="
	@$(CPP23_TEST_DEBUG) || exit 1
	@echo ""
	@echo "=== C23 New Features Tests ==="
	@$(C23_FEATURES_DEBUG) || exit 1
	@echo ""
	@echo "=== C23 Thread Safety Tests ==="
	@$(C23_THREADSAFE_DEBUG) || exit 1
	@echo ""
	@echo "=== C23 Release Mode Tests ==="
	@$(C23_TEST_RELEASE) || exit 1
	@echo ""
	@echo "=== C++23 Release Mode Tests ==="
	@$(CPP23_TEST_RELEASE) || exit 1
	@echo ""
	@echo "=== C23 NDEBUG Mode Tests ==="
	@$(C23_NDEBUG_TEST) || exit 1
	@echo ""
	@echo "=== C++23 NDEBUG Mode Tests ==="
	@$(CPP23_NDEBUG_TEST) || exit 1
	@echo ""
	@echo "========================================"
	@echo "ALL TESTS PASSED"
	@echo "========================================"

# Run only debug mode tests (useful for quick testing)
.PHONY: test-debug
test-debug: debug
	@echo ""
	@echo "=== C23 Debug Mode Tests ==="
	@$(C23_TEST_DEBUG)
	@echo ""
	@echo "=== C++23 Debug Mode Tests ==="
	@$(CPP23_TEST_DEBUG)
	@echo ""
	@echo "=== C23 New Features Tests ==="
	@$(C23_FEATURES_DEBUG)
	@echo ""
	@echo "=== C23 Thread Safety Tests ==="
	@$(C23_THREADSAFE_DEBUG)

# Run only release mode tests
.PHONY: test-release
test-release: release
	@echo ""
	@echo "=== C23 Release Mode Tests ==="
	@$(C23_TEST_RELEASE)
	@echo ""
	@echo "=== C++23 Release Mode Tests ==="
	@$(CPP23_TEST_RELEASE)
	@echo ""
	@echo "=== C23 NDEBUG Mode Tests ==="
	@$(C23_NDEBUG_TEST)
	@echo ""
	@echo "=== C++23 NDEBUG Mode Tests ==="
	@$(CPP23_NDEBUG_TEST)

# Run only new features tests
.PHONY: test-features
test-features: $(BUILD_DIR) $(C23_FEATURES_DEBUG) $(C23_THREADSAFE_DEBUG)
	@echo ""
	@echo "=== C23 New Features Tests ==="
	@$(C23_FEATURES_DEBUG)
	@echo ""
	@echo "=== C23 Thread Safety Tests ==="
	@$(C23_THREADSAFE_DEBUG)

# Clean build artifacts
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
	@echo "Build artifacts cleaned"

# Show help
.PHONY: help
help:
	@echo "debug.h Unit Tests Makefile"
	@echo ""
	@echo "Targets:"
	@echo "  make          - Build debug mode tests (default)"
	@echo "  make release  - Build release (NDEBUG) mode tests"
	@echo "  make all      - Build all tests (debug and release)"
	@echo "  make test     - Build and run all tests"
	@echo "  make test-debug   - Build and run debug mode tests only"
	@echo "  make test-release - Build and run release mode tests only"
	@echo "  make test-features - Build and run new features tests only"
	@echo "  make clean    - Remove all build artifacts"
	@echo "  make help     - Show this help message"
	@echo ""
	@echo "Compiler flags:"
	@echo "  Debug:       $(CFLAGS_DEBUG)"
	@echo "  Release:     $(CFLAGS_RELEASE)"
	@echo "  ThreadSafe:  $(CFLAGS_THREADSAFE)"
