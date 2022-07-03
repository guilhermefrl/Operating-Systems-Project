#include "biblioteca.h"

int LerFicheiro (char *nome, int inicio)
{				//lê o ficheiro de programa para memória e retorna o tamanho de memória ocupado
  FILE *f;
  char nomecat[15];
  strcpy (nomecat, nome);
  char *file = strcat (nomecat, ".prg");
  f = fopen (file, "r");
  char ch;
  int i = inicio;

  if (f == NULL)
    {
      printf ("Erro ao abrir o ficheiro.\n");
      return -1;
    }
  while (1)
    {
      ch = fgetc (f);
      if (ch == EOF)
        {
            break;
        }
      if (ch == 'L')
        {
            fseek (f, -sizeof (char), SEEK_CUR);
            fscanf (f, "%c %s\n", &Memory[i].ins, Memory[i].nome);
            i++;
            continue;
        }
      fseek (f, -sizeof (char), SEEK_CUR);
      fscanf (f, "%c %d", &Memory[i].ins, &Memory[i].n);
      strcpy (Memory[i].nome, "Null");
      fseek (f, sizeof (char), SEEK_CUR);
      i++;
    }
  return i-inicio;
}

int lerControl (char *controlo)
{
  FILE *f;
  f = fopen ("control.txt", "r");
  if (f == NULL)
    {
      return 0;
    }
  int i = 0;
  while ((fscanf (f, "%c\n", &controlo[i])) != EOF)
    {
      i++;
    }
  fclose(f);
  return i;
}


SPlan *lerPlan (int *i)
{
  FILE *f;
  SPlan *Leitura;
  *i=0;
  char c;
  f = fopen ("plan.txt", "r");
  if (f == NULL)
    {
      return 0;
    }
  Leitura = (SPlan *) malloc(sizeof(SPlan));
  int j=0;
  char *nome;
  nome = malloc(sizeof(char));
  while ((c=fgetc(f)) != EOF)
    {
        if(c == '.'){
            fseek(f,4,SEEK_CUR);
            fscanf(f,"%d",&Leitura[*i].time);
            if((c=fgetc(f)) == EOF || c == '\n'){
              srand((time(NULL)*(*i)));
              Leitura[*i].priority = rand()%10 + 1;
            }else{
              fscanf(f,"%d\n",&Leitura[*i].priority);
            }
            strcpy(Leitura[*i].nome,nome);
            *i=*i+1;
            Leitura = (SPlan *)realloc(Leitura,sizeof(SPlan)*(*i+1));
            j=0;
            free(nome);
            nome = malloc(sizeof(char));
            continue;
        }
        nome = realloc(nome, sizeof(char)*(j+2));
        nome[j] = c;
        j++;
    }
    fclose(f);
  return Leitura;
}


SPlan *FCFS(SPlan *Leitura, int j){
  int i, k;

  for(i=1;i<j;i++)
  {
    for(k=0;k<j-i;k++)
    {
      if(Leitura[k].time > Leitura[k+1].time)
      {
        SPlan temp = Leitura[k];
        Leitura[k] = Leitura[k+1];
        Leitura[k+1] = temp;
      }
    }
  }

  return Leitura;
}


//DEBUG
void ImprimirMemoria ()
{				// para debug, imprimimos a memória para encontrar possíveis erros.
  for (int i = 0; i < 1000; i++)
    {
      if (Memory[i].ins == -1)
	{
	  continue;
	}
      printf ("%c %d %s\n", Memory[i].ins, Memory[i].n, Memory[i].nome);
    }
  return;
}

void mostrarPlan(SPlan *Leitura,int j){
    for(int i=0;i<j;i++){
        printf("%s\t%d\t%d\n",Leitura[i].nome,Leitura[i].time,Leitura[i].priority);
    }
    return;
}

void mostrarControl (char *controlo)
{
  for (int i = 0; i < 5; i++)
    {
      printf ("%c\n", controlo[i]);
    }
    return;
}