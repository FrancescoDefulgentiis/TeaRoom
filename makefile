CC = gcc# The compiler to use
CFLAGS = -Wall# The compiler flags to use (-wall = all warnings)

# List of source files
SOURCES = main.c callMaker.c capture.c

# The target executable
TARGET = TeaRoom.exe

#from here on are the gates of uncertanty
all:	$(TARGET)

$(TARGET):	$(SOURCES)
		$(CC)	$(CFLAGS)	$(SOURCES)	-o	$(TARGET)

clean:
		rm -f $(TARGET)

.PHONY: all clean
