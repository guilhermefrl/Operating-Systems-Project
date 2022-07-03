CC=cc
FLAGS=-c -Wall 
LIBS=-lm
OBS=main.o execute.o ler.o PCB.o lista.o stats.o memory.o processos.o

all : projeto

main.o : biblioteca.h main.c
	$(CC) $(FLAGS) main.c
execute.o : biblioteca.h execute.c
	$(CC) $(FLAGS) execute.c
ler.o : biblioteca.h ler.c
	$(CC) $(FLAGS) ler.c
PCB.o : biblioteca.h PCB.c
	$(CC) $(FLAGS) PCB.c
lista.o : biblioteca.h lista.c
	$(CC) $(FLAGS) lista.c
stats.o : biblioteca.h stats.c
	$(CC) $(FLAGS) stats.c
memory.o : biblioteca.h memory.c
	$(CC) $(FLAGS) memory.c
processos.o : biblioteca.h processos.c
	$(CC) $(FLAGS) processos.c	
projeto : $(OBS) biblioteca.h
	$(CC) -o projeto $(OBS) $(LIBS)

clean limpar:
	rm -f projeto *.o
	rm -f *~