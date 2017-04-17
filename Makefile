CC=gcc
EXECUTABLE=tm
SOURCES=main.c

default:
	$(CC) $(SOURCES) -DTRIM_OUTPUT -o $(EXECUTABLE)

notrim:
	$(CC) $(SOURCES) -o $(EXECUTABLE)

debug:
	$(CC) $(SOURCES) -DTM_DEBUG -o $(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE)
