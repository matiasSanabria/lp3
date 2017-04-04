CC = cc
COPS =
LOPS = -x -u
LINT = lint

all: ring1 ring2 ring3 ring4 ring5 ringtopology

ring1: ring1.c
	$(CC) $(COPS) -o ring1 ring1.c

ring2: ring2.c
	$(CC) $(COPS) -o ring2 ring2.c

ring3: ring3.c
	$(CC) $(COPS) -o ring3 ring3.c

ring4: ring4.c
	$(CC) $(COPS) -o ring4 ring4.c

ring5: ring5.c
	$(CC) $(COPS) -o ring5 ring5.c
	
ringtopology: ringtopology.c
	$(CC) $(COPS) -o ringtopology ringtopology.c

clean:
	rm -f *.o core ring1 ring2 ring3 ring4 ring5 ringtopology


