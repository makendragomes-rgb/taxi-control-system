CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Iinclude
SRCDIR = src
OBJDIR = build
BIN = taxi-control-system

SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	./$(BIN)

demo: all
	./$(BIN) --demo

clean:
	rm -rf $(OBJDIR) $(BIN) $(BIN).exe

.PHONY: all run demo clean
