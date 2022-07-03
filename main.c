#include "biblioteca.h"

//funções para o PC (tempo)
void incPC ()
{
  PC++;
}

int getPC ()
{
  return PC;
}

void setPC(int set){
	PC = set;
}

int main ()
{
	int simulador;
	
	 printf("Insira o Simulador que deseja:\n 1--Gestão de Memória \n 2--Gestão de Processos\n 3--Qualquer valor para sair\n");
  scanf("%d",&simulador);
  		if(simulador==1)
		GestaoMemoria();
		
		if(simulador==2){
		GestaoProcessos();	
		
		}
		else{
			printf("FIM\n");
			
		}
		
}


