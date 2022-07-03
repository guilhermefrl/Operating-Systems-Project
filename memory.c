#include "biblioteca.h"


Nodo *MakeNodo(int count){
    Nodo *nv;
    nv=(Nodo*)malloc(sizeof(Nodo));
    nv->PID1=-1;
    nv->PID2=-1;
    nv->PID3=-1;
    nv->tam=3+(rand() % 8);;
    nv->count=count;
    nv->tam1=0;
    nv->tam2=0;
    nv->tam3=0;
   nv->nseg=NULL;
   return nv; 
}

Nodo *InsertLast(Nodo *L,Nodo *nv){
    Nodo *aux=L;
    if(L==NULL)
        return nv;
    while(aux->nseg!=NULL){
    aux=aux->nseg;
    }
    aux->nseg=nv;
    return L;
}

Nodo *CriaLista(Nodo *Lista,int tam){
   Nodo *nv;
    int i=0;
    int count=0;

   while(i<tam){
       nv=MakeNodo(count);
       Lista=InsertLast(Lista,nv);
            i++;
            count++;
         
   }
    return Lista;
    }

int alocate_mem_FIRST(int PID, int tam, Nodo *ListaFirst){

    int count=0;

    while(ListaFirst->nseg != NULL){
        if(ListaFirst->tam >= tam){
            ListaFirst->tam=ListaFirst->tam-tam;
            if(ListaFirst->PID1==-1){
            ListaFirst->PID1=PID;
            ListaFirst->tam1=tam;}
              if(ListaFirst->PID2==-1){
            ListaFirst->PID2=PID;
              ListaFirst->tam2=tam;}
              if(ListaFirst->PID3==-1){
                ListaFirst->PID3=PID;
                   ListaFirst->tam3=tam;}
            return count;
            break;
        }
        
        count++;
        ListaFirst=ListaFirst->nseg;
    }

    return -1;
}

int alocate_mem_NEXT(int PID, int tam, Nodo *ListaNext){

    int count=0;
 
    int mem=-1;
        Nodo *aux=ListaNext;
    while(aux->nseg!=NULL){
        if(aux->PID1!=-1 ||aux->PID1!=-1 ||aux->PID1!=-1 ){
            mem=aux->count;
        }
        aux=aux->nseg;
    }
    while(mem>0){
        ListaNext=ListaNext->nseg;
        mem--;
    }
  while(ListaNext->nseg != NULL){
        if(ListaNext->tam >= tam){
            ListaNext->tam=ListaNext->tam-tam;
            if(ListaNext->PID1==-1){
            ListaNext->PID1=PID;
            ListaNext->tam1=tam;}
              if(ListaNext->PID2==-1){
            ListaNext->PID2=PID;
              ListaNext->tam2=tam;}
              if(ListaNext->PID3==-1){
                ListaNext->PID3=PID;
                   ListaNext->tam3=tam;}
            return count;
            break;
        }
        
        count++;
        ListaNext=ListaNext->nseg;
    }

    return -1;
}
int alocate_mem_BEST(int PID, int tam1, Nodo *ListaBest){

    int count=0, count1=0;
    int t=0;
    int aux=0;
    Nodo *Lista=ListaBest;
    while(Lista->nseg != NULL){
        if(Lista->tam >= tam1){
    
            if(aux==0){
                aux=Lista->tam;
                t=count;
            }
            else
            {
                if(Lista->tam<aux){
                    aux=Lista->tam;
                    t=count; 
                }
            }
            

        }
        count++;
        Lista=Lista->nseg;
    }
    while(ListaBest->nseg != NULL){
        if(ListaBest->tam==aux && ListaBest->count==t){
            ListaBest->tam=ListaBest->tam-tam1;

            if(ListaBest->PID1==-1){
            ListaBest->PID1=PID;
            ListaBest->tam1=tam1;
                            }
              if(ListaBest->PID2==-1){
            ListaBest->PID2=PID;
              ListaBest->tam2=tam1;
                            }
              if(ListaBest->PID3==-1){
                ListaBest->PID3=PID;
                   ListaBest->tam3=tam1;
                                    }
            return count1;
            break;
          
        }
        count1++;
        ListaBest=ListaBest->nseg;
    }

    return -1;

}
int alocate_mem_WORST(int PID, int tam1, Nodo *ListaWorst){

    int count=0, count1=0;
    int t=0;
    int aux=0;
 Nodo *Lista=ListaWorst;
    while(Lista->nseg != NULL){
        if(Lista->tam >= tam1){
    
            if(aux==0){
                aux=Lista->tam;
                t=count;
            }
            else
            {
                if(Lista->tam>aux){
                    aux=Lista->tam;
                    t=count; 
                }
            }
            

        }
        count++;
        Lista=Lista->nseg;
    }
    while(ListaWorst->nseg != NULL){
        if(ListaWorst->tam==aux && ListaWorst->count==t){
            ListaWorst->tam=ListaWorst->tam-tam1;

            if(ListaWorst->PID1==-1){
            ListaWorst->PID1=PID;
            ListaWorst->tam1=tam1;
                            }
              if(ListaWorst->PID2==-1){
            ListaWorst->PID2=PID;
              ListaWorst->tam2=tam1;
                            }
              if(ListaWorst->PID3==-1){
                ListaWorst->PID3=PID;
                   ListaWorst->tam3=tam1;
                                    }
            return count1;
            break;
          
        }
        count1++;
        ListaWorst=ListaWorst->nseg;
    }

    return -1;

}
  int de_alocate_mem(int c4,Nodo *Lista){
     
            while(Lista->nseg!=NULL){
                if(Lista->PID1==c4){
                    Lista->PID1=-1;
                    Lista->tam=Lista->tam+Lista->tam1;
                    Lista->tam1=0;
                        return 1;
                        }
                if(Lista->PID2==c4){
                    Lista->PID2=-1;
                     Lista->tam=Lista->tam+Lista->tam2;
                    Lista->tam2=0;
                    return 1;
                    }
                 if(Lista->PID3==c4){
                    Lista->PID3=-1;
                     Lista->tam=Lista->tam+Lista->tam3;
                    Lista->tam3=0;
                    return 1;
                    }

                Lista=Lista->nseg;
            }
            return -1;

  }
  int fragment_count(Nodo *Lista){
    int count=0;

    while(Lista->nseg != NULL){
        if((Lista->tam == 2) || (Lista->tam == 1)){
            count++;
        }
        Lista=Lista->nseg;
    }

    return count++;
}
 
 void estatisticas(int TAMLISTA,int nmrnostotalF,int nmrnostotalN, int nmrnostotalW, int nmrnostotalB,int N1,int N2,int N3,int N4,int PNF,int PNN,int PNB,int PNW, Nodo *ListaBest,Nodo *ListaFirst,Nodo *ListaNext,Nodo *ListaWorst,int aux1){
float externosB=0,externosF=0,externosN=0,externosW=0;
  float externosBF,externosFF,externosNF,externosWF;
        float t1,t2,t3,t4,a1,a2,a3,a4;
                t1=nmrnostotalF/N1;
                 t2=nmrnostotalN/N2;
                 t3=nmrnostotalB/N3;
                 t4=nmrnostotalW/N4;
                 a1=((PNF*100)/aux1);
                 a2=((PNN*100)/aux1);
                 a3=((PNB*100)/aux1);
                 a4=((PNW*100)/aux1);
                  externosB=fragment_count(ListaBest);
                 externosF=fragment_count(ListaFirst);
                externosN=fragment_count(ListaNext);
                externosW=fragment_count(ListaWorst);
               
                externosBF=externosB/TAMLISTA;
                 externosFF=externosF/TAMLISTA;
                 externosNF=externosN/TAMLISTA;
                externosWF=externosW/TAMLISTA;
                 printf("Numero Medio de Fragmentos externos para o FIRST: %f\n",externosFF );
                 printf("Numero Medio de Fragmentos externos para o BEST: %f\n",externosBF );
                printf("Numero Medio de Fragmentos externos para o NEXT: %f\n",externosNF );
                printf("Numero Medio de Fragmentos externos para o WORST: %f\n",externosWF );
                 printf("\n");
                 printf("Tempo médio de alocação para o FIRST: %f\n", t1);
                 printf("Tempo médio de alocação para o NEXT: %f\n", t2);
                 printf("Tempo médio de alocação para o BEST: %f\n", t3);
                 printf("Tempo médio de alocação para o WORST: %f\n", t4);
                 printf("\n");
                 printf("Percentagem de solicitações negadas para o FIRST: %f%%\n", a1);
                 printf("Percentagem de solicitações negadas para o NEXT: %f%%\n", a2);
                 printf("Percentagem de solicitações negadas para o BEST: %f%%\n", a3);
                 printf("Percentagem de solicitações negadas para o WORST: %f%%\n", a4);
                 printf("\n\nGUILHERME LACÃO\nNUNO PEDRO\nTIAGO ALMEIDA\nGRUPO 09\n");
 }
 
    void GestaoMemoria(){
        int c1,c2,PID=0,tam,nmr,c4,c3;
        float externosB=0,externosF=0,externosN=0,externosW=0;
        
        int nmrnosB=0,nmrnosN=0,nmrnosW=0,nmrnosF=0;
        int nmrnostotalN=0,nmrnostotalB=0,nmrnostotalW=0,nmrnostotalF=0;
        int valores[11] = {1,1,2,3,1,2,1,3,1,2,-1};
        int i=0;
        int N1=0, N2=0, N3=0, N4=0;
        int TESTE1,TESTE2,TESTE3,TESTE4;
        int aux1;
        
        int TAMLISTA;
        Nodo *ListaBest=NULL;
        Nodo *ListaFirst=NULL;
        Nodo *ListaNext=NULL;
        Nodo *ListaWorst=NULL;
        int PNF=0;
        int PNN=0;
        int PNB=0;
        int PNW=0;
       
        printf("Insira o tamanho da Lista::");
        scanf("%d",&TAMLISTA);
         ListaBest=CriaLista(ListaBest,TAMLISTA);
        ListaFirst=CriaLista(ListaFirst,TAMLISTA);
        ListaNext=CriaLista(ListaNext,TAMLISTA);
        ListaWorst=CriaLista(ListaWorst,TAMLISTA);
        printf("Insira a opção das solicitações:\n -- 1-Aleatóriamente\n -- 2-Memória estática(Pouco Numero de Processos)\n -- 3-Trace de Memoria Pré-Definida\n");
        scanf("%d",&c1);
          switch (c1)
	    {
	    case 1:
        printf("Insira quantas solicitações deseja gerar\n");
        scanf("%d",&nmr);
        aux1=nmr;
            while(nmr>0){
                     c3=1+(rand() % 3);
               switch (c3)
	                 { 
                       case 1:
                               tam=3+(rand() % 8);

                              TESTE1=alocate_mem_FIRST(PID,tam,ListaFirst);
                       
                           if(TESTE1==-1){
                                 PNF++;
                             
                                 }
                                 else{
                                    nmrnosF=TESTE1;
                                    nmrnostotalF=nmrnosF+nmrnostotalF;
                                    N1++;
                                 }

                      TESTE2=alocate_mem_NEXT(PID,tam,ListaNext); 
                    if(TESTE2==-1){
                                 PNN++;
                                 }
                                 else{
                                    nmrnosN=TESTE2;
                                    nmrnostotalN=nmrnosN+nmrnostotalN;
                                    N2++;
                                 }
                    TESTE3=alocate_mem_BEST(PID,tam,ListaBest);         
                   if(TESTE3==-1){
                                 PNB++;
                                 }
                                 else{
                                    nmrnosB=TESTE3;
                                    nmrnostotalB=nmrnosB+nmrnostotalB;
                                    N3++;
                                 }
                      TESTE4=alocate_mem_WORST(PID,tam,ListaWorst);         
                    if(TESTE4==-1){
                                 PNW++;
                                 }
                                 else{
                                    nmrnosW=TESTE4;
                                    nmrnostotalW=nmrnosW+nmrnostotalW;
                                    N4++;
                                 }
                                PID++;   
                         break;
                    case 2:
                      c4=1+(rand() % PID-1);
                        if(de_alocate_mem(c4,ListaBest)==-1){
                                    PNB++;
                                    }
                         if(de_alocate_mem(c4,ListaNext)==-1){
                                    PNN++;
                                    }
                          if(de_alocate_mem(c4,ListaFirst)==-1){
                                    PNF++;
                                    }
                          if(de_alocate_mem(c4,ListaWorst)==-1){
                                    PNW++;
                                    }

                         break;
                     case 3:
                                externosB=fragment_count(ListaBest)+externosB;
                                externosF=fragment_count(ListaFirst)+externosF;
                                externosN=fragment_count(ListaNext)+externosN;
                                externosW=fragment_count(ListaWorst)+externosW;
                     break;
              
                 }
               
                   nmr--;
            }
               estatisticas(TAMLISTA,nmrnostotalF,nmrnostotalN,nmrnostotalW, nmrnostotalB,N1,N2,N3,N4,PNF,PNN,PNB,PNW, ListaBest,ListaFirst,ListaNext,ListaWorst,aux1);
        
             
             break;
         case 2:
                 printf("Insira o numero das solicitações, (Entre 0 e 30) ");
                 scanf("%d",&c2);
                aux1=c2;
                 while(c2>0){
                      tam=3+(rand() % 8);

                        TESTE1=alocate_mem_FIRST(PID,tam,ListaFirst);
                       
                           if(TESTE1==-1){
                                 PNF++;
                             
                                 }
                                 else{
                                    nmrnosF=TESTE1;
                                    nmrnostotalF=nmrnosF+nmrnostotalF;
                                    N1++;
                                 }

                      TESTE2=alocate_mem_NEXT(PID,tam,ListaNext); 
                    if(TESTE2==-1){
                                 PNN++;
                                 }
                                 else{
                                    nmrnosN=TESTE2;
                                    nmrnostotalN=nmrnosN+nmrnostotalN;
                                    N2++;
                                 }
                    TESTE3=alocate_mem_BEST(PID,tam,ListaBest);         
                   if(TESTE3==-1){
                                 PNB++;
                                 }
                                 else{
                                    nmrnosB=TESTE3;
                                    nmrnostotalB=nmrnosB+nmrnostotalB;
                                    N3++;
                                 }
                      TESTE4=alocate_mem_WORST(PID,tam,ListaWorst);         
                    if(TESTE4==-1){
                                 PNW++;
                                 }
                                 else{
                                    nmrnosW=TESTE4;
                                    nmrnostotalW=nmrnosW+nmrnostotalW;
                                    N4++;
                                 }
                      c2--;
                      PID++;           
                 }
                  estatisticas(TAMLISTA,nmrnostotalF,nmrnostotalN,nmrnostotalW, nmrnostotalB,N1,N2,N3,N4,PNF,PNN,PNB,PNW, ListaBest,ListaFirst,ListaNext,ListaWorst,aux1);
                 
            break;
        case 3:
        PID=0;
        while(valores[i]!=-1){
            aux1=10;
               switch (valores[i])
	                 { 
                       case 1:
                        tam=3+(rand() % 8);
                              TESTE1=alocate_mem_FIRST(PID,tam,ListaFirst);
                           if(TESTE1==-1){
                                 PNF++;
                                 }
                                 else{
                                    nmrnosF=TESTE1;
                                    nmrnostotalF=nmrnosF+nmrnostotalF;
                                    N1++;
                                 }
                      TESTE2=alocate_mem_NEXT(PID,tam,ListaNext); 
                    if(TESTE2==-1){
                                 PNN++;
                                 }
                                 else{
                                    nmrnosN=TESTE2;
                                    nmrnostotalN=nmrnosN+nmrnostotalN;
                                    N2++;
                                 }
                    TESTE3=alocate_mem_BEST(PID,tam,ListaBest);             
                   if(TESTE3==-1){
                                 PNB++;
                                 
                                 }
                                 else{
                                    nmrnosB=TESTE3;
                                    nmrnostotalB=nmrnosB+nmrnostotalB;
                                    N3++;
                                 }
                      TESTE4=alocate_mem_WORST(PID,tam,ListaWorst);        
                    if(TESTE4==-1){
                                 PNW++;
                                 }
                                 else{
                                    nmrnosW=TESTE4;
                                    nmrnostotalW=nmrnosW+nmrnostotalW;
                                    N4++;
                                 }
                PID++;  
                         break;
                    case 2:
                      c4=1+(rand() % PID-1);
                        if(de_alocate_mem(c4,ListaBest)==-1){
                                    PNB++;
                                    }
                         if(de_alocate_mem(c4,ListaNext)==-1){
                                    PNN++;
                                    
                                    }
                          if(de_alocate_mem(c4,ListaFirst)==-1){
                                    PNF++;
                                    }
                          if(de_alocate_mem(c4,ListaWorst)==-1){
                                    PNW++;
                                    
                                    }

                         break;
                     case 3:
                                externosB=fragment_count(ListaBest)+externosB;
                                externosF=fragment_count(ListaFirst)+externosF;
                                externosN=fragment_count(ListaNext)+externosN;
                                externosW=fragment_count(ListaWorst)+externosW;
                     break;
                     default:
                     break;
               
                 }

                  i++;
                 
            }
             
                estatisticas(TAMLISTA,nmrnostotalF,nmrnostotalN,nmrnostotalW, nmrnostotalB,N1,N2,N3,N4,PNF,PNN,PNB,PNW, ListaBest,ListaFirst,ListaNext,ListaWorst,aux1);
             break;
             default:
                printf("Fim");
            }

    }
