CC=gcc
CFLAGS=-c -Wall
LDFLAGS=
SOURCES= data.c data.h main.c io.h io.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=myApp.exe
RM=del

all: $(SOURCES) $(EXECUTABLE)
$(EXECUTABLE) : $(OBJECTS)
	@echo Last step: linking everything into $@
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
%.o : %.c
	@echo compiling $< to $@
	$(CC) $(CFLAGS) $< -o $@
.PHONY: clean
clean:
	rm *.exe
