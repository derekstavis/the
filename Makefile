CFLAGS = -W -Wall -Werror
SOURCE = the.c main.c
BINARY = the_poc

all: $(BINARY)

$(BINARY):
	CC $(CFLAGS) $(SOURCE) -o $(BINARY)

clean:
	rm -rf $(BINARY)