CXX = g++ # The C++ compiler to use
CXXFLAGS = -g -Wall -pthread # The compiler flags to use (-Wall = all warnings)
LDFLAGS = -lcurl -pthread -lsqlite3 # Linker flags for libcurl and sqlite3

# Project directories
SRC_DIR = .
INCLUDE_DIR = $(SRC_DIR)
OUTPUT = TeaRoom.exe  # Specify the output file name

# Find all .cpp files in the project and its subdirectories
SRC_FILES := $(shell find $(SRC_DIR) -name '*.cpp')

# Find all .h files in the project and its subdirectories
HDR_FILES := $(shell find $(INCLUDE_DIR) -name '*.h')

# Libraries to link (add -lcurl to link with libcurl)
LIBS = -lcurl -lsqlite3

# Build rule
$(OUTPUT): $(SRC_FILES) $(HDR_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $(SRC_FILES) $(LIBS)

.PHONY: clean run

clean:
	rm -f $(OUTPUT)

run: $(OUTPUT)
	./$(OUTPUT)

