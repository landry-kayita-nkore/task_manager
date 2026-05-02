CC     = gcc
CFLAGS = -Wall -Wextra -g
TARGET = task_manager
SRCS   = main.c task.c utils.c
OBJS   = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) tasks.dat tasks.json

.PHONY: all clean
