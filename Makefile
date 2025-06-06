# Define the C++ compiler
CXX = g++

# Compiler flags:
# -Wall -Wextra: Enable common warnings
# -std=c++17: Use C++17 standard (adjust as needed, e.g., c++20)
# -MMD: Generate dependency files (.d files) listing all included headers
# -MP: Add phony targets for each header file in the .d file (prevents errors if a header is deleted)
# -Isrc: Add the src directory to the include path so headers like "foo.h" are found
CXXFLAGS = -std=c++20 -Wall -O3 -MMD -MP -Isrc

# Linker flags (add any libraries here, e.g., -lm, -lpthread)
LDFLAGS = -lSDL2main -lSDL2 -lSDL2_image

# --- Define the build directory and source directory ---
BUILD_DIR = build
SRC_DIR = src
# Define the source directory

# Define the source files: Find all .cpp files within the SRC_DIR
# Example: SRCS might become "src/main.cpp src/foo.cpp"
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
$(info DEBUG: SRCS = $(SRCS))

# Automatically derive object files (.o) and dependency files (.d)
# These will be in the BUILD_DIR, but their names correspond to the source file names.
# $(notdir $(SRCS:.cpp=.o)) will first change "src/main.cpp" to "src/main.o",
# then $(notdir ...) will strip "src/" resulting in "main.o".
# Finally, $(addprefix build/, ...) will make it "build/main.o". This is correct.
OBJS = $(addprefix $(BUILD_DIR)/, $(notdir $(SRCS:.cpp=.o)))
DEPS = $(addprefix $(BUILD_DIR)/, $(notdir $(SRCS:.cpp=.d)))
$(info DEBUG: OBJS = $(OBJS))
$(info DEBUG: DEPS = $(DEPS))

# Define the name of the final executable, placed in BUILD_DIR
TARGET = $(BUILD_DIR)/DrawingProgram.out
$(info DEBUG: TARGET = $(TARGET))

# Define the command to remove files (cross-platform way)
RM = rm -f
MKDIR_P = mkdir -p # Command to create directories, -p means "parents" and "no error if exists"

# .PHONY targets are not actual files; they are commands that make can run
.PHONY: all clean

# Default target: builds the program
all: $(TARGET)

# Rule to ensure the build directory exists before building anything.
# This rule makes sure $(BUILD_DIR) is created before $(TARGET) is built.
$(BUILD_DIR):
	$(MKDIR_P) $(BUILD_DIR)

# Rule to build the final executable from object files
# It depends on the BUILD_DIR existing before it links.
$(TARGET): $(OBJS) $(BUILD_DIR)
	$(CXX) $(OBJS) $(LDFLAGS) -o $(TARGET)

# Rule to compile each .cpp file into a .o file within the BUILD_DIR.
# The target is $(BUILD_DIR)/%.o, meaning the object file goes into build/.
# The prerequisite is $(SRC_DIR)/%.cpp, meaning the source file comes from src/.
# The order-only prerequisite on $(BUILD_DIR) ensures the directory exists.
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Include the automatically generated dependency files (.d files)
# These files are now expected to be in the BUILD_DIR
# The `-include` makes it so that if a .d file doesn't exist yet, it's not an error.
-include $(DEPS)

# Clean target: removes all generated files from the BUILD_DIR
clean:
	$(RM) $(OBJS) $(TARGET) $(DEPS)
	# Optional: remove the build directory itself if it's empty
	-rmdir $(BUILD_DIR) 2>/dev/null || true