#include "biblioteca.h"

void printProcess(PCB process){
    printf("nome=%s,pid = %d, ppid = %d, prioridade = %d, valor = %d, tempo-inicio = %d, tempo-fim = %d,tempoCPU = %d\n",process.nome,process.PID,process.PPID,process.Prioridade,process.var,process.start_time,process.end_time,process.TCPU);
}
void report(PCB *PCBTabela,int PCBsize,int *Bloqueados,int Bloqueadossize,int *Prontos,int Prontossize,RunningState *Executar){
    int i;
    printf("\nTEMPO ATUAL: %d\n",getPC());
    printf("PROCESSO EM EXECUÇÃO:\n");
    if(Executar != NULL){
        if(PCBTabela[Executar->i].Estado == 1)
            printProcess(PCBTabela[Executar->i]);
    }
        
    printf("PROCESSOS BLOQUEADOS:\n");
    for(i = 0; i < Bloqueadossize; i++){
        printProcess(PCBTabela[Bloqueados[i]]);
    }
    printf("PROCESSOS PRONTOS A EXECUTAR:\n");
    for(i=0;i<Prontossize;i++){
        printProcess(PCBTabela[Prontos[i]]);
    }
    printf("PROCESSOS TERMINADOS:\n");
    for(i = 0;i<PCBsize;i++){
        if(PCBTabela[i].Estado == 3) // terminados
        {  
            printProcess(PCBTabela[i]);
        }
    }
    printf("\n");
}

int *getTTimes(PCB *PCBTabela,int PCBsize){
    int *Ttimes = (int*)malloc(PCBsize*sizeof(int));
    for(int i=0;i<PCBsize;i++){
        Ttimes[i] = PCBTabela[i].end_time - PCBTabela[i].start_time;
    }
    return Ttimes;
}

float getATurnarround(int *Ttimes,int PCBsize){
    float processCount = 0;
    float times = 0;
    for(int i=0;i<PCBsize;i++){
        if(Ttimes[i]>0){
            times += Ttimes[i];
            processCount++;
        }
    }
    return (processCount>0?(times/processCount):0);
}

float getWaitingTime(int *Ttimes,PCB *PCBTabela,int PCBsize){
    float processCount = 0;
    float times = 0;
    for(int i=0;i<PCBsize;i++){
        if(Ttimes[i]>0){
            times += (Ttimes[i] - PCBTabela[i].TCPU);
            processCount++;
        }
    }
    return (processCount>0?(times/processCount):0);
}

void getNotFinished(PCB *PCBTabela,int PCBsize){
    int i;
    for(i=0;i<PCBsize;i++){
        if(PCBTabela[i].Estado != 3){
            printf("Processo = %s\tPID = %d\tPPID = %d\t",PCBTabela[i].nome,PCBTabela[i].PID,PCBTabela[i].PPID);
            printf("\n");
        }
    }
    return;
}

void getFinished(PCB *PCBTabela,int PCBsize){
    int i;
    for(i=0;i<PCBsize;i++){
        if(PCBTabela[i].Estado == 3){
            printf("Processo = %s\tPID = %d\tPPID = %d\t",PCBTabela[i].nome,PCBTabela[i].PID,PCBTabela[i].PPID);
            printf("\n");
        }
    }
    return;
}

void globalStats(PCB *PCBTabela,int PCBsize){
    printf("\n\nCPU TOTAL TIME:\n%d\n",getPC());
    int *Ttimes = getTTimes(PCBTabela,PCBsize);
    printf("TEMPO MÉDIO DE TURNARROUND:\n%.2f\n",getATurnarround(Ttimes,PCBsize));
    printf("TEMPO MÉDIO DE ESPERA:\n%.2f\n",getWaitingTime(Ttimes,PCBTabela,PCBsize));
    printf("PROCESSOS NÃO TERMINADOS:\n");
    getNotFinished(PCBTabela,PCBsize);
    printf("PROCESSOS TERMINADOS:\n");
    getFinished(PCBTabela,PCBsize);
    printf("\n\nGUILHERME LACÃO\nNUNO PEDRO\nTIAGO ALMEIDA\nGRUPO 09\n");
}