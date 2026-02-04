# Compiler settings
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++20 -O2

# Default target
# Usage: make run file=solution.cpp
run: compile
	@echo "--- Running $(basename $(file)) ---"
	@./$(basename $(file))
	@rm -f $(basename $(file))

compile:
	@echo "--- Compiling $(file) ---"
	@$(CXX) $(CXXFLAGS) $(file) -o $(basename $(file))
