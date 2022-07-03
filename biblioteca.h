#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>
#include <time.h>
#include <sys/wait.h>
#include <signal.h>
#define TQ 20

typedef struct{
    char ins;//instrução
    int n; //numero
    char nome[15]; //nome (para o caso de ser a instrução L)
} Instruction;

Instruction Memory[1000];
int memoryLast;

typedef struct{
    char *nome; //qual o nome do processo
    int start; //qual o começo das instruções
    int PID; //qual o PID do processo
    int PPID; //qual o PID do pai
    int PC; //qual o seu program counter
    int TCPU; //Tempo Gasto pela CPU
    int Prioridade; //qual a sua prioridade
    int Estado; //qual o seu estado
    int tam; //quantas instruções tem
    int start_time; //quando começa (tempo)
    int end_time; //quando começa (tempo)
    int var; //qual o valor da variável do processo
}PCB;

typedef struct nodo{
    int PID1;
    int PID2;
    int PID3;
    int tam;
    int tam1;
    int tam2;
    int tam3;
    int count;
    struct nodo *nseg;
} Nodo;

typedef struct{
	char nome[20]; //nome do programa
	int time; //tempo de inicio
    int priority;//prioridade
}SPlan;

typedef struct{
    int i;
    int PID;
    int PC;
}RunningState;

static int PC = 0;

int incPID();

void incPC();

int getPC();

void setPC(int set);

void GestaoProcessos();

int LerFicheiro(char* nome,int inicio);  //lê do ficheiro para um array do tipo memory

PCB *execute(PCB *PCBTabela,int *PCBsize,RunningState *Executar,int **Prontos,int *Prontossize,int **Bloqueados,int *Bloqueadossize,int *T);  //realiza as ações lidas do ficheiro. apartir do array memory

int aExecutar(PCB *PCBTabela, int PCBsize); //Verifica se existe algum programa a executar

Instruction *makeInstruction(Instruction *I); //Cria uma struct com a Instrução

PCB *newPCB(PCB *PCBTabela,int *PCBsize,char *nome, int time, int Prioridade);  //cria um espaço com a informação do processo em memória
PCB *insertPCB(PCB *PCBTabela,int *PCBsize,PCB PCB_a_inserir); //Insere um PCB no PCBTabela
PCB PCBCopy(PCB *PCB_a_copiar); //Copia um processo (simula o fork)
int maxPCBStart(PCB *PCBTabela,int PCBsize); //percorre a tabela de PCB e retorna o último tamanho de memória utilizado.

SPlan *lerPlan(int *i);

int lerControl(char *controlo);

//Estatísticas
void report(PCB *PCBTabela,int PCBsize,int *Bloqueados,int Bloqueadossize,int *Prontos,int Prontossize,RunningState *Executar);
void printProcess(PCB process);
void globalStats(PCB *PCBTabela,int PCBsize);

//Para criarmos filas facilmente
int *insereFila (int *fila, int *itemCount, int data);
int removeFila (int *fila, int *itemCount);
int *removeAleatorio(int *fila,int *itemCount,int *aleatorio);
//Para o algoritmo de prioridade
int maiorPrioridade(PCB *PCBTabela,int *prontos,int psize, int maior);
int *removePrioridade(PCB *PCBTabela,int *fila,int *itemCount,int *removido);
//Para o algoritmo SJF
int menorTamanho(PCB *PCBTabela,int *prontos,int psize, int current);
int *removeTamanho(PCB *PCBTabela,int *fila,int *itemCount,int *removido);

//Para o algoritmo de FCFS
SPlan *FCFS(SPlan *Leitura, int j);
//Para debugg
void ImprimirMemoria();

void imprimirPCB(PCB *PCBTabela,int PCBsize);

void mostrarControl(char *controlo);

void mostrarPlan(SPlan *Leitura,int j);

void printFila (int *fila,int itemCount);

//Funções de Gestão de Memoria
Nodo *MakeNodo(int count);

Nodo *InsertLast(Nodo *L,Nodo *nv);

Nodo *CriaLista(Nodo *Lista,int tam);

int alocate_mem_FIRST(int PID, int tam, Nodo *ListaFirst);

int alocate_mem_NEXT(int PID, int tam, Nodo *ListaNext);

int alocate_mem_BEST(int PID, int tam1, Nodo *ListaBest);

int alocate_mem_WORST(int PID, int tam1, Nodo *ListaWorst);

int de_alocate_mem(int c4,Nodo *Lista);

int fragment_count(Nodo *Lista);

void estatisticas(int TAMLISTA,int nmrnostotalF,int nmrnostotalN, int nmrnostotalW, int nmrnostotalB,int N1,int N2,int N3,int N4,int PNF,int PNN,int PNB,int PNW, Nodo *ListaBest,Nodo *ListaFirst,Nodo *ListaNext,Nodo *ListaWorst,int aux1);

void GestaoMemoria();


//O objetivo inicial passa por ler instruções de um ficheiro ,então devemos usar a função LeFicheiro para esse feito, para conseguir realizar a ação temos que nessa função
// chamar a função makeInstruction para criar uma instrução com a linha que acabei de ler do ficheiro e depois de ter a struct devemos chamar a função juntamemory, para juntar
// essa instrução no array de memory, e devemos repetir o processo até ao fim do ficheiro.
