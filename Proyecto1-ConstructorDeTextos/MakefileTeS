CC=clang
CFLAGS=-g -Wall
OBJS=manage.o dataTypes.o dataManage.o
EXE=creator.elf 

all: $(EXE)

%.elf: %.o $(OBJS)
	$(CC) $(CFLAGS) $< $(OBJS) -o $@

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.dSYM *.o $(EXE)