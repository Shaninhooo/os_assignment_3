# Compiler Flags
COMPILER = gcc
FLAGS = -Werror -Wall -Wpointer-arith -Wstrict-prototypes -std=gnu89 -fPIC -MMD -MP -lpthread

# Build Info
SOURCE_DIR = src
BUILD_DIR = build
TARGET = test-mergesort
EXECUTABLE = $(BUILD_DIR)/$(TARGET)
OBJ = mergesort.o $(TARGET).o
OBJ_FILES = $(addprefix $(BUILD_DIR)/, $(OBJ))
DEP_FILES = $(patsubst %.o,%.d,$(OBJ_FILES))

# Build all executables
all: $(EXECUTABLE)
	@echo "Build complete. Run with: ./$(EXECUTABLE) <input size> <cutoff level> <seed>"

# Rule for building the executable: src/build/test-mergesort
$(EXECUTABLE): $(OBJ_FILES)
	@echo "--------------------------------------------------------"
	@echo "=> LINKING: Creating executable '$@' from object files $^"
	@$(CC) $(CFLAGS) -o $@ $^
	@echo "--------------------------------------------------------"

# Pattern rule for compiling C files from src/ into object files in src/build/
$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c
	@echo "=> COMPILING: $< to object file $@"
	@# Ensure the build directory exists
	@mkdir -p $(BUILD_DIR)
	@# Compile, place .o file at $@, and generate .d file in the same directory
	@$(COMPILER) $(CFLAGS) -c $< -o $@

# Run the test-mergesort algorithm
run: $(EXECUTABLE)
	@echo "-> RUNNING: $(EXECUTABLE) $(ARGS)"
	./$(EXECUTABLE) $(ARGS)

# Run the test-mergesort algorithm
run_default: $(EXECUTABLE)
	@echo "-> RUNNING: $(EXECUTABLE) 100000000 2 1234"
	./$(EXECUTABLE) 100000000 2 1234

# Include the automatically generated dependency files.
# This ensures that if a header file changes, the corresponding C file is recompiled.
-include $(DEP_FILES)

.PHONY: all clean run

clean:
	@echo "=> CLEAN: Removing generated files..."
	@/bin/rm -f $(OBJ_FILES) $(DEP_FILES) $(EXECUTABLE)
	@echo "   - Removed object (.o) files, dependency (.d) files, and executable."
	@# Attempt to remove the build directory if it's empty, ignore error if it fails
	-@/bin/rmdir $(BUILD_DIR) 2>/dev/null || true
	@echo "   - Removed build directory '$(BUILD_DIR)' (if empty)."
	@echo "Clean complete."
