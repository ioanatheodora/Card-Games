CC = gcc
CFLAG = -Wall -Wextra
EXE = games
OBJ = games.o


build: $(EXE)

%.o: %.c list.h $(DEPS)
	$(CC) -c -o $@ $< $(CFLAG)

$(EXE): $(OBJ)
	$(CC) $^ $(CFLAG) $(LDFLAGS) list.h -o $(EXE)

run:
	./$(EXE)

.PHONY: clean

clean:
	rm -f *.o $(EXE) in out

