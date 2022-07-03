#include "biblioteca.h"

int incPID(){
    static int PID=0;
    PID = PID +1;
    return PID;
}

int maxPCBStart(PCB *PCBTabela,int PCBsize){
    int i,max=-1,curr;
    if(PCBTabela== NULL)
        return max;
    max = PCBTabela[0].start + PCBTabela[0].tam;
    for(i=0;i<PCBsize;i++){
        if(max < (curr=PCBTabela[i].start + PCBTabela[i].tam)){
            max = curr;
        }
    }
    return max;
}

PCB PCBCopy(PCB *PCB_a_copiar){
    PCB copia;
    copia.nome = (char*)malloc(20*sizeof(char));
    copia = *PCB_a_copiar;
    strcpy(copia.nome,PCB_a_copiar->nome);
    copia.start_time = getPC() + 1;
    copia.PC = PCB_a_copiar->PC+1;
    copia.PID = incPID();
    copia.PPID = PCB_a_copiar->PID;
    copia.TCPU = 0;
    copia.Estado = 0;
    return copia;
}

PCB *insertPCB(PCB *PCBTabela,int *PCBsize,PCB PCB_a_inserir){
    if(PCBTabela == NULL){
        PCBTabela = (PCB*)malloc(sizeof(PCB));
        *PCBsize = 1;
    }else{
        *PCBsize += 1;
        PCBTabela = (PCB*)realloc(PCBTabela,(*PCBsize)*sizeof(PCB));
    }
    PCBTabela[*PCBsize-1].nome = (char*)malloc(20*sizeof(char));
    strcpy(PCBTabela[*PCBsize-1].nome, PCB_a_inserir.nome);
    PCBTabela[*PCBsize-1].Estado = PCB_a_inserir.Estado;
    PCBTabela[*PCBsize-1].PC = PCB_a_inserir.PC;
    PCBTabela[*PCBsize-1].PID = PCB_a_inserir.PID;
    PCBTabela[*PCBsize-1].PPID = PCB_a_inserir.PPID;
    PCBTabela[*PCBsize-1].Prioridade = PCB_a_inserir.Prioridade;
    PCBTabela[*PCBsize-1].start = PCB_a_inserir.start;
    PCBTabela[*PCBsize-1].tam = PCB_a_inserir.tam;
    PCBTabela[*PCBsize-1].TCPU = PCB_a_inserir.TCPU;
    PCBTabela[*PCBsize-1].start_time = PCB_a_inserir.start_time;
    PCBTabela[*PCBsize-1].end_time = PCB_a_inserir.end_time;
    PCBTabela[*PCBsize-1].var = PCB_a_inserir.var;
    return PCBTabela;
}

PCB *newPCB(PCB *PCBTabela,int *PCBsize,char *nome, int time, int Prioridade){//criar um novo PCB, à medida em que é pedida a criação de novos processos temos que criar um novo PCB, aqui o PCB já lê a memória e armazena o tamanho que o Processo ocupa em memória
    if(PCBTabela == NULL){
        PCBTabela = (PCB*)malloc(sizeof(PCB));
        *PCBsize= 1;
    }else{
        *PCBsize +=1;
        PCBTabela = (PCB*)realloc(PCBTabela,(*PCBsize)*sizeof(PCB));
    }
    PCBTabela[*PCBsize-1].nome = (char*)malloc(20*sizeof(char));
    PCBTabela[*PCBsize-1].nome = nome;
    if(PCBsize-1 == 0){
        PCBTabela[*PCBsize-1].start = 0;
    }else{
        PCBTabela[*PCBsize-1].start = PCBTabela[*PCBsize-1-1].start + PCBTabela[*PCBsize-1-1].tam;
    }
    PCBTabela[*PCBsize-1].PID = incPID();
    PCBTabela[*PCBsize-1].PPID = 0;
    PCBTabela[*PCBsize-1].PC = 0;
    PCBTabela[*PCBsize-1].Prioridade = Prioridade;
    PCBTabela[*PCBsize-1].Estado = 0; //ready
    PCBTabela[*PCBsize-1].TCPU = 0;
    PCBTabela[*PCBsize-1].var = 0;
    PCBTabela[*PCBsize-1].start_time = time;
    PCBTabela[*PCBsize-1].end_time = 0;
    PCBTabela[*PCBsize-1].tam = LerFicheiro(nome, PCBTabela[*PCBsize-1].start);
    if(PCBTabela[*PCBsize-1].tam == 0)
        perror("Ficheiro não lido.");
    return PCBTabela;
}

void imprimirPCB(PCB *PCBTabela,int PCBsize){//para debug, imprimimos o PCB para descobrirmos possíveis erros no PCB
    for(int i=0;i<PCBsize;i++){
        printf("PCB[%d] = {nome = %s variavel= %d start=%d PID=%d PPID=%d PC=%d Prioridade=%d Estado=%d Tamanho=%d }\n",i,PCBTabela[i].nome,PCBTabela[i].var,PCBTabela[i].start,PCBTabela[i].PID,PCBTabela[i].PPID,PCBTabela[i].PC,PCBTabela[i].Prioridade,PCBTabela[i].Estado,PCBTabela[i].tam);
    }
}

