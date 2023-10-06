CXX = g++ # The C++ compiler to use
CXXFLAGS = -Wall # The compiler flags to use (-Wall = all warnings)
LDFLAGS = -lcurl # Linker flags for libcurl

# List of source files
SOURCES = main.cpp callMaker.cpp capture.cpp getIp.cpp

# The target executable
TARGET = TeaRoom.exe

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)

.PHONY: all clean
