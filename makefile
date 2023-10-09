CXX = g++ # The C++ compiler to use
CXXFLAGS = -g -Wall -pthread # The compiler flags to use (-Wall = all warnings)
LDFLAGS = -lcurl -pthread -lsqlite3 # Linker flags for libcurl

# List of source files
SOURCES = main.cpp audioNvideo/capture.cpp networking/getIp.cpp phonebook/phoneBook.cpp

# The target executable
TARGET = TeaRoom.exe

# The GDB file
GDB_FILE = $(TARGET).gdb

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET) $(LDFLAGS)

gdb: $(TARGET)
	gdb -ex "file $(TARGET)" -ex "run"

clean:
	rm -f $(TARGET) $(GDB_FILE)

.PHONY: all gdb clean