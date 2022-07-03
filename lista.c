#include "biblioteca.h"
//visto e adaptado de https://www.tutorialspoint.com/data_structures_algorithms/priority_queue.htm
int *insereFila (int * fila, int *itemCount, int data)
{
  int i = 0;
  if (*itemCount == 0)
    {
      fila = (int *) malloc (sizeof (int));
      fila[(*itemCount)] = data;
      (*itemCount)++;
    }
  else
    {
      (*itemCount)++;
      fila = (int *) realloc (fila, (*itemCount) * sizeof (int));
      for (i = *itemCount - 2; i >= 0; i--)
      {			
        fila[i+1] = fila[i];
      }
      fila[0] = data;
    }
  return fila;
}
//FIFO Scheduling
int removeFila (int * fila, int *itemCount)
{
  *itemCount-=1;
  int item = fila[(*itemCount)];
  fila = (int *) realloc (fila, (*itemCount) * sizeof (int));
  return item;
}

//Priority Scheduling
int maiorPrioridade(PCB *PCBTabela,int *prontos,int psize, int maior){
  
  for(int i=0;i<psize;i++){
    if(((PCBTabela[maior].Prioridade > PCBTabela[prontos[i]].Prioridade) ||
    (PCBTabela[maior].Prioridade == PCBTabela[prontos[i]].Prioridade && PCBTabela[maior].start_time > PCBTabela[prontos[i]].start_time)) && (PCBTabela[prontos[i]].start_time >= getPC()))
      return 0;
  }
  return 1;
}

int *removePrioridade(PCB *PCBTabela,int *fila,int *itemCount,int *removido)
{
  if(*itemCount == 0){
    *removido=-1;
    return fila;
  }
  int min = 0;
  for(int i=0;i<(*itemCount);i++){
    if(((PCBTabela[fila[min]].Prioridade > PCBTabela[fila[i]].Prioridade) ||
    (PCBTabela[fila[min]].Prioridade == PCBTabela[fila[i]].Prioridade && PCBTabela[fila[min]].start_time > PCBTabela[fila[i]].start_time)) && PCBTabela[fila[i]].start_time >= getPC())
      min = i;
  }
  *removido = fila[min];*itemCount -=1;
  for(int i = min;i<(*itemCount);i++){
    fila[i]=fila[i+1];
  }
  fila = (int *)realloc(fila,(*itemCount)*sizeof(int));
  return fila;
}

//Shortest Job First Scheduling
int menorTamanho(PCB *PCBTabela,int *prontos,int psize, int current){
  
  for(int i=0;i<psize;i++){
    if(((PCBTabela[current].tam - PCBTabela[current].PC > PCBTabela[prontos[i]].tam - PCBTabela[prontos[i]].PC ) ||
    (PCBTabela[current].tam - PCBTabela[current].PC == PCBTabela[prontos[i]].tam - PCBTabela[prontos[i]].PC && PCBTabela[current].start_time > PCBTabela[prontos[i]].start_time)) && (PCBTabela[prontos[i]].start_time >= getPC()))
      return 0;
  }
  return 1;
}
int *removeTamanho(PCB *PCBTabela,int *fila,int *itemCount,int *removido)
{
  if(*itemCount == 0){
    *removido=-1;
    return fila;
  }
  int min = 0;
  for(int i=0;i<(*itemCount);i++){
    if(((PCBTabela[fila[min]].tam - PCBTabela[fila[min]].PC > PCBTabela[fila[i]].tam - PCBTabela[fila[i]].PC) ||
    (PCBTabela[fila[min]].tam - PCBTabela[fila[min]].PC == PCBTabela[fila[i]].tam - PCBTabela[fila[i]].PC && PCBTabela[fila[min]].start_time > PCBTabela[fila[i]].start_time)) && PCBTabela[fila[i]].start_time >= getPC())
      min = i;
  }
  *removido = fila[min];*itemCount -=1;
  for(int i = min;i<(*itemCount);i++){
    fila[i]=fila[i+1];
  }
  fila = (int *)realloc(fila,(*itemCount)*sizeof(int));
  return fila;
}

//Escalonador de longo prazo
int *removeAleatorio(int *fila,int *itemCount,int *aleatorio)
{
  if(itemCount == 0){
    *aleatorio = -1;
    return fila;
  }
  int randindex = rand() % ((*itemCount));
  *aleatorio = fila[randindex];
  *itemCount -=1;
  for(int i = randindex;i<(*itemCount);i++){
    fila[i]=fila[i+1];
  }
  fila = (int *)realloc(fila,(*itemCount)*sizeof(int));
  return fila;
}

//Debugging
void printFila (int *fila,int itemCount){
  int i;
  printf("Fila =");
  for(i=0;i<itemCount;i++)
    printf("%d\t",fila[i]);
  printf("\n");
}