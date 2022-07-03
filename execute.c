#include "biblioteca.h"

PCB *execute(PCB *PCBTabela,int *PCBsize,RunningState *Executar,int **Prontos,int *Prontossize,int **Bloqueados,int *Bloqueadossize,int *T){				//executar o Programa Executar, para o limite de tempo T
  int j;
  PCBTabela[Executar->i].Estado = 1;
  Executar->PC=PCBTabela[Executar->i].PC;
  PCB copia;
		if(PCBTabela[Executar->i].Estado!=1){
        Executar->i = -1;
        Executar->PC = -1;
        Executar->PID = -1;
			return PCBTabela;
		}
    if(getPC() < PCBTabela[Executar->i].start_time){
      setPC(PCBTabela[Executar->i].start_time);
    }
    j= PCBTabela[Executar->i].start + PCBTabela[Executar->i].PC;
	  switch (Memory[j].ins)
	    {
	    case 'M':
        //Muda o Valor da Variável para o Valor n
            PCBTabela[Executar->i].var=Memory[j].n;
	    break;

	    case 'A':
        //Adiciona n á variavel
	          PCBTabela[Executar->i].var += Memory[j].n;
	    break;

	    case 'S':
        //Subtrai n á variável
        PCBTabela[Executar->i].var-=Memory[j].n;
	    break;

	    case 'B':
        //Bloqueia Este Processo
        PCBTabela[Executar->i].Estado=2; //Com o estado a 2 o processo é bloqueado
        *Bloqueados = insereFila(*Bloqueados,Bloqueadossize,Executar->i);
        
	    break;

      case 'C': 
          copia = PCBCopy(&PCBTabela[Executar->i]);
          Executar->PC += Memory[j].n-1;
          PCBTabela[Executar->i].PC = Executar->PC;
          PCBTabela = insertPCB(PCBTabela,PCBsize,copia);
          *Prontos = insereFila(*Prontos,Prontossize,(*PCBsize)-1);
      break;

      case 'L':
        //FileName Alterar
           PCBTabela[Executar->i].nome=Memory[j].nome;
           PCBTabela[Executar->i].start = maxPCBStart(PCBTabela,*PCBsize);
           PCBTabela[Executar->i].tam = LerFicheiro(PCBTabela[Executar->i].nome,PCBTabela[Executar->i].start);
           PCBTabela[Executar->i].PC=0;
           Executar->PC=-1;
           PCBTabela[Executar->i].TCPU = 0;
           PCBTabela[Executar->i].var = 0;
      break;

	    case 'T':
	      //Termina Este processo
          PCBTabela[Executar->i].Estado=3;// Com o estado a 3 o Processo é dado como Terminado
          PCBTabela[Executar->i].end_time = getPC() + 1;
          PCBTabela[Executar->i].TCPU += 1;
          PCBTabela[Executar->i].PC = ++Executar->PC;
          Executar->i = -1;
          Executar->PC = 0;
          Executar->PID = 0;
          incPC();
          (*T)--;
          return PCBTabela;
      break;
	    default:
        printf("Instrução não reconhecida.\n");
        return PCBTabela;
	      break;
	    }
    PCBTabela[Executar->i].PC = ++Executar->PC;
    PCBTabela[Executar->i].TCPU += 1;
    incPC();
    (*T)--;
    return PCBTabela;
}

int aExecutar(PCB *PCBTabela,int PCBsize){
    //Se houver algum Programa com estado == 1,
    //ele está a executar então devolve a posiçao desse,
    //senao devolve -1
    for(int i=0;i<PCBsize;i++){
      if(PCBTabela[i].Estado==1)
        return i;
    }
    return -1;
}