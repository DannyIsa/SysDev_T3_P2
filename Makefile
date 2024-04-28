CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS = -lm

TARGET = RUDP_Sender
SRC = RUDP_Sender.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(TARGET)