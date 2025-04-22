OUT = replc

OBJS = replace.o test-client.o

LDFLAGS=-lcares
CFLAGS= -g

$(OUT): $(OBJS)
	$(CC) -o $(OUT) $(OBJS) $(LDFLAGS)

clean:
	rm -f $(OUT) $(OBJS) *~

