#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main(int argc, char *argv[]) {
    int b=0,c,niz[10],niz1[10],greska,i=-1,j=0;         // deklariramo i inicijaliziramo varijable koje koristimo
    FILE *tokpod,*tokpod1,*tokpod2;                     // deklariramo tokove podataka
    tokpod=fopen(argv[1],"r");                          // otvaramo ulazni tok podataka tokpod
    
    if (tokpod == NULL){
               printf("Gre�ka pri otvaranju\n");        // u slu�aju nemogu�nosti otvaranja javljamo gre�ku
               exit(-99);
               }
    tokpod2=fopen(argv[2],"w");                         // otvaramo ulazni tok podataka tokpod2
    if (tokpod2 == NULL){
               printf("Gre�ka pri otvaranju\n");        // u slu�aju nemogu�nosti otvaranja javljamo gre�ku
               exit(-99);
               }                    
   
    
    while ((c=fgetc(tokpod)) != EOF){                   // u�itavamo jedan po jedan znak do kraja ulazne datoteke
    i++;
    niz[i]=c;                                           // u�itavamo sedam znakova u niz jedan po jedan
    
    if (i==6){                                          // nakon �to u�itamo sedam znakova ra�unamo sindrom da otkrijemo gre�ku
       greska=((niz[3]-48+niz[4]-48+niz[5]-48+niz[6]-48)%2)*4+((niz[1]-48+niz[2]-48+niz[5]-48+niz[6]-48)%2)*2+(niz[0]-48+niz[2]-48+niz[4]-48+niz[6]-48)%2;
       if (greska!=0){                                  // ukoliko nema gre�ke varijabla gre�ka poprima vrijednost 0                                                                                                                                                                                                                                                            
          if (niz[greska-1]==49)                        // ukolika ima gre�ke na mjestu (gre�ka -1) ispravljamo bit
              niz[greska-1]=48;
          else if (niz[greska-1]==48)
              niz[greska-1]=49;
              }                                         // nakon �to ispravimo gre�ko ako je postojala spremamo podatkovne bitove u novi niz
           niz1[0]=niz[2];                              // Prvi podatkovni bit
           niz1[1]=niz[4];                              // Drugi podatkovni bit
           niz1[2]=niz[5];                              // Tre�i podatkovni bit
           niz1[3]=niz[6];                              // �etvrti podatkovni bit
       for (j=0;j<4;j++)                                // set od �etiri znaka zapisujemo u izlaznu datoteku
           fputc(niz1[j],tokpod2);
        i=-1;                                           // inicijaliziramo broja�
       }
       
       }
       
    fclose(tokpod);                                     // zatvaramo ulazni tok podataka tokpod
    fclose(tokpod2);                                    // zatvaramo izlazni tok podataka tokpod2
    return 0;
}
