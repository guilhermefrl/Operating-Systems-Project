#include"biblioteca.h"

void GestaoProcessos(){
//**************** DECLARAR VARIÁVEIS AQUI *****************
  memoryLast=0;
  int *Prontos = NULL;
  int Prontossize = 0;
  
  int *Bloqueados = NULL;
  int Bloqueadossize = 0;
  
  PCB *PCBTabela = NULL;
  int  PCBsize=0;
  
  RunningState *Executar= (RunningState*)malloc(sizeof(RunningState));
  Executar->i = -1;
  Executar->PC = -1;
  Executar->PID = -1;
  
  SPlan *Leitura = NULL;
  int PlanIndex = 0;
  
  char control[50];
  int controlTam = 0;

  int j, T, i, c, escal, index; // escal - Escalonamento 1 = FCFS 2 = Priority 3 = SJFS
  char c1, c2;
  //*************** CÓDIGO PARA INICIAR O PROGRAMA AQUI ***************
  //ler do ficheiro plan.txt e armazenar as variáveis
  Leitura = lerPlan (&j);
  Leitura = FCFS (Leitura, j);
  // mostrarPlan (Leitura, j);
 

  
  //************** CÓDIGO PARA CORRER O PROGRAMA AQUI *****************
  do{
  printf ("DEFINA O TIME QUANTUM:");
  scanf ("%d", &T);
  }while(T<0);
  do{
  printf("Escolha o método de escalonamento\n");
  printf("1. FCFS\n2. Priority\n3. SJFS\n");
  scanf("%d",&escal);
  }while(escal<0 || escal>3);
  fflush(stdin);
  if ((controlTam = lerControl(control)) != 0)
    {
      for (i = 0; i < controlTam; i++)
	{
	  c1 = control[i];
	  	for(int iter=PlanIndex;iter<j;iter++){
			if(Leitura[iter].time == getPC()){
				PCBTabela = newPCB(PCBTabela,&PCBsize,Leitura[iter].nome,Leitura[iter].time,Leitura[iter].priority);
				Prontos = insereFila(Prontos,&Prontossize,PCBsize-1);PlanIndex++;
			}
		}
	  switch (c1)
	    {
	    case 'E':
	      /* Executa um programa para o limite maximo de tempo */
			c=T;
			do{
				for(int iter=PlanIndex;iter<j;iter++){
					if(Leitura[iter].time < getPC() + 1){
						PCBTabela = newPCB(PCBTabela,&PCBsize,Leitura[iter].nome,Leitura[iter].time,Leitura[iter].priority);
						Prontos = insereFila(Prontos,&Prontossize,PCBsize-1);PlanIndex++;
					}
				}
				if(escal == 1){
					if(Executar->i!= -1){
						if(PCBTabela[Executar->i].Estado == 1){
							PCBTabela = execute(PCBTabela,&PCBsize,Executar,&Prontos,&Prontossize,&Bloqueados,&Bloqueadossize,&c);
							if(c<=0){ break; }else{	continue; }
						}
					}
				}else if(escal == 2){
					if(Executar->i != -1){
						if(PCBTabela[Executar->i].Estado == 1){
							if(maiorPrioridade(PCBTabela,Prontos,Prontossize,Executar->i) == 0){
								index = -1;
								Prontos = removePrioridade(PCBTabela,Prontos,&Prontossize,&index);
								if(index == -1) break;
								//context switch
								PCBTabela[Executar->i].Estado = 0; //ready
								Prontos = insereFila(Prontos,&Prontossize,Executar->i);
								Executar->i = index;
								Executar->PC = PCBTabela[Executar->i].PC;
								Executar->PID = PCBTabela[Executar->i].PID;
							}
							PCBTabela = execute(PCBTabela,&PCBsize,Executar,&Prontos,&Prontossize,&Bloqueados,&Bloqueadossize,&c);
							if(c<=0){ break; }else{ continue; }
						}
					}
				}else if(escal == 3){
					if(Executar->i != -1){
						if(PCBTabela[Executar->i].Estado == 1){
							if(menorTamanho(PCBTabela,Prontos,Prontossize,Executar->i) == 0){
								index = -1;
								Prontos = removeTamanho(PCBTabela,Prontos,&Prontossize,&index);
								if(index == -1) break;
								//context switch
								PCBTabela[Executar->i].Estado = 0;
								Prontos = insereFila(Prontos,&Prontossize,Executar->i);
								Executar->i = index;
								Executar->PC = PCBTabela[Executar->i].PC;
								Executar->PID = PCBTabela[Executar->i].PID;
							}
							PCBTabela = execute(PCBTabela,&PCBsize,Executar,&Prontos,&Prontossize,&Bloqueados,&Bloqueadossize,&c);
							if(c<=0){ break; }else{ continue; }
						}
					}
				}
				
				if(Prontossize == 0){
					if(PlanIndex >= j){
						printf("Não Existem mais processos para executar no plano.\n");
						break;
					}
					PCBTabela = newPCB(PCBTabela,&PCBsize,Leitura[PlanIndex].nome,Leitura[PlanIndex].time,Leitura[PlanIndex].priority);
					Executar->i = PCBsize-1;
					Executar->PC = 0;
					Executar->PID = PCBTabela[PCBsize-1].PID;
					PlanIndex++;
					Prontos = insereFila(Prontos,&Prontossize,Executar->i);
				}
				

				if(escal == 1){
					Executar->i = removeFila(Prontos,&Prontossize);
					Executar->PID = PCBTabela[Executar->i].PID;
					Executar->PC = PCBTabela[Executar->i].PC;
					PCBTabela = execute(PCBTabela,&PCBsize,Executar,&Prontos,&Prontossize,&Bloqueados,&Bloqueadossize,&c);
				}else if(escal == 2){
					index = -1;
					Prontos = removePrioridade(PCBTabela,Prontos,&Prontossize,&index);
					if(index == -1) break;
					Executar->i = index;
					Executar->PC = PCBTabela[Executar->i].PC + 1;
					Executar->PID = PCBTabela[Executar->i].PID;
					PCBTabela = execute(PCBTabela,&PCBsize,Executar,&Prontos,&Prontossize,&Bloqueados,&Bloqueadossize,&c);
				}else if(escal == 3){
					index = -1;
					Prontos = removeTamanho(PCBTabela,Prontos,&Prontossize,&index);
					if(index == -1) break;
					Executar->i = index;
					Executar->PC = PCBTabela[Executar->i].PC + 1;
					Executar->PID = PCBTabela[Executar->i].PID;
					PCBTabela = execute(PCBTabela,&PCBsize,Executar,&Prontos,&Prontossize,&Bloqueados,&Bloqueadossize,&c);
				}
			}while(c>0);
			
	    break;/**/
		case 'I':
	        // Interrompe o processo e bloqueia-o 
				if(PCBTabela[Executar->i].Estado == 1){
					PCBTabela[Executar->i].Estado = 2;
					Bloqueados = insereFila(Bloqueados,&Bloqueadossize,(Executar->i));
					Executar->i = -1;
					Executar->PC = -1;
					Executar->PID = -1;
				}
	        break;
	    case 'R':
	      /* Chama a função de reportagem */
	      report(PCBTabela,PCBsize,Bloqueados,Bloqueadossize,Prontos,Prontossize,Executar);
	      break;
	    case 'D':
	      /* chama o escalonador de longo prazo*/
		  	if(Bloqueadossize != 0){
				int i;
				Bloqueados = removeAleatorio(Bloqueados,&Bloqueadossize,&i);
				if(i>=0)
					Prontos = insereFila(Prontos,&Prontossize,i);
			}else{
				printf("Não existem processos bloqueados.\n");
			}
	      break;
	    case 'T':
	      /* Terminar o simulador e imprime estatisticas globais */
		  globalStats(PCBTabela,PCBsize);
	    default:
		break;
	    }
	}
    }
  else
    {
      printf ("Insira uma instrução válida para o controlo:\n");
      do
	{
	  scanf ("%c", &c2);
	  	for(int iter=PlanIndex;iter<j;iter++){
			if(Leitura[iter].time == getPC()){
				PCBTabela = newPCB(PCBTabela,&PCBsize,Leitura[iter].nome,Leitura[iter].time,Leitura[iter].priority);
				Prontos = insereFila(Prontos,&Prontossize,PCBsize-1);PlanIndex++;
			}
		}
	  switch (c2)
	    {
	    case 'E':
	      /* Executa um programa para o limite maximo de tempo */
			c=T;
			do{
				for(int iter=PlanIndex;iter<j;iter++){
					if(Leitura[iter].time < getPC() + 1){
						PCBTabela = newPCB(PCBTabela,&PCBsize,Leitura[iter].nome,Leitura[iter].time,Leitura[iter].priority);
						Prontos = insereFila(Prontos,&Prontossize,PCBsize-1);PlanIndex++;
					}
				}
				if(escal == 1){
					if(Executar->i!= -1){
						if(PCBTabela[Executar->i].Estado == 1){
							PCBTabela = execute(PCBTabela,&PCBsize,Executar,&Prontos,&Prontossize,&Bloqueados,&Bloqueadossize,&c);
							if(c<=0){ break; }else{	continue; }
						}
					}
				}else if(escal == 2){
					if(Executar->i != -1){
						if(PCBTabela[Executar->i].Estado == 1){
							if(maiorPrioridade(PCBTabela,Prontos,Prontossize,Executar->i) == 0){
								index = -1;
								Prontos = removePrioridade(PCBTabela,Prontos,&Prontossize,&index);
								if(index == -1) break;
								//context switch
								PCBTabela[Executar->i].Estado = 0; //ready
								Prontos = insereFila(Prontos,&Prontossize,Executar->i);
								Executar->i = index;
								Executar->PC = PCBTabela[Executar->i].PC;
								Executar->PID = PCBTabela[Executar->i].PID;
							}
							PCBTabela = execute(PCBTabela,&PCBsize,Executar,&Prontos,&Prontossize,&Bloqueados,&Bloqueadossize,&c);
							if(c<=0){ break; }else{ continue; }
						}
					}
				}else if(escal == 3){
					if(Executar->i != -1){
						if(PCBTabela[Executar->i].Estado == 1){
							if(menorTamanho(PCBTabela,Prontos,Prontossize,Executar->i) == 0){
								index = -1;
								Prontos = removeTamanho(PCBTabela,Prontos,&Prontossize,&index);
								if(index == -1) break;
								//context switch
								PCBTabela[Executar->i].Estado = 0;
								Prontos = insereFila(Prontos,&Prontossize,Executar->i);
								Executar->i = index;
								Executar->PC = PCBTabela[Executar->i].PC;
								Executar->PID = PCBTabela[Executar->i].PID;
							}
							PCBTabela = execute(PCBTabela,&PCBsize,Executar,&Prontos,&Prontossize,&Bloqueados,&Bloqueadossize,&c);
							if(c<=0){ break; }else{ continue; }
						}
					}
				}
				
				if(Prontossize == 0){
					if(PlanIndex >= j){
						printf("Não Existem mais processos para executar no plano.\n");
						break;
					}
					PCBTabela = newPCB(PCBTabela,&PCBsize,Leitura[PlanIndex].nome,Leitura[PlanIndex].time,Leitura[PlanIndex].priority);
					Executar->i = PCBsize-1;
					Executar->PC = 0;
					Executar->PID = PCBTabela[PCBsize-1].PID;
					PlanIndex++;
					Prontos = insereFila(Prontos,&Prontossize,Executar->i);
				}
				

				if(escal == 1){
					Executar->i = removeFila(Prontos,&Prontossize);
					Executar->PID = PCBTabela[Executar->i].PID;
					Executar->PC = PCBTabela[Executar->i].PC;
					PCBTabela = execute(PCBTabela,&PCBsize,Executar,&Prontos,&Prontossize,&Bloqueados,&Bloqueadossize,&c);
				}else if(escal == 2){
					index = -1;
					Prontos = removePrioridade(PCBTabela,Prontos,&Prontossize,&index);
					if(index == -1) break;
					Executar->i = index;
					Executar->PC = PCBTabela[Executar->i].PC + 1;
					Executar->PID = PCBTabela[Executar->i].PID;
					PCBTabela = execute(PCBTabela,&PCBsize,Executar,&Prontos,&Prontossize,&Bloqueados,&Bloqueadossize,&c);
				}else if(escal == 3){
					index = -1;
					Prontos = removeTamanho(PCBTabela,Prontos,&Prontossize,&index);
					if(index == -1) break;
					Executar->i = index;
					Executar->PC = PCBTabela[Executar->i].PC + 1;
					Executar->PID = PCBTabela[Executar->i].PID;
					PCBTabela = execute(PCBTabela,&PCBsize,Executar,&Prontos,&Prontossize,&Bloqueados,&Bloqueadossize,&c);
				}
			}while(c>0);
			
	    break;/**/
		case 'I':
	        // Interrompe o processo e bloqueia-o 
				if(PCBTabela[Executar->i].Estado == 1){
					PCBTabela[Executar->i].Estado = 2;
					Bloqueados = insereFila(Bloqueados,&Bloqueadossize,(Executar->i));
					Executar->i = -1;
					Executar->PC = -1;
					Executar->PID = -1;
				}
	        break;
	    case 'R':
	      /* Chama a função de reportagem */
	      report(PCBTabela,PCBsize,Bloqueados,Bloqueadossize,Prontos,Prontossize,Executar);
	      break;
	    case 'D':
	      /* chama o escalonador de longo prazo*/
		  	if(Bloqueadossize != 0){
				int i;
				Bloqueados = removeAleatorio(Bloqueados,&Bloqueadossize,&i);
				if(i>=0)
					Prontos = insereFila(Prontos,&Prontossize,i);
			}else{
				printf("Não existem processos bloqueados.\n");
			}
	      break;
	    case 'T':
	      /* Terminar o simulador e imprime estatisticas globais */
		  globalStats(PCBTabela,PCBsize);
	    default:
		break;
	    }
	}
      while (c2 != 'T');

    }
  //ImprimirMemoria ();
  //imprimirPCB (PCBTabela);
  free(PCBTabela);
  free(Bloqueados);
  free(Prontos);
  free(Leitura);
  return 0;
}