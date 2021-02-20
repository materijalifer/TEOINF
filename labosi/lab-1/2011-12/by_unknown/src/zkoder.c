#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main(int argc, char *argv[]) {
    int b=0,c,niz[10],niz1[10],i=-1,j=0;            // deklariramo i inicijaliziramo varijable koje koristimo
    FILE *tokpod,*tokpod1,*tokpod2;                 // deklariramo tokove podataka
    tokpod=fopen(argv[1],"r");                      // otvaramo ulazni tok podataka tokpod
    if (tokpod == NULL){
               perror("Gre�ka pri otvaranju\n");
               exit(-99);                           // u slu�aju nemogu�nosti otvaranja javljamo gre�ku
               }
    tokpod2=fopen(argv[2],"w");                     // otvaramo izlazni tok podataka tokpod2
    if (tokpod2 == NULL){
               printf("Gre�ka pri otvaranju\n");
               exit(-99);                           // u slu�aju nemogu�nosti otvaranja javljamo gre�ku
               }                   
               
    while ((c=fgetc(tokpod)) != EOF)                // u�itavamo jedan po jedan znak do kraja ulazne datoteke
          b++;                                      // brojimo koliko ima znakova u datoteci
          fclose(tokpod);                           // zatvaramo ulazni tok podataka tokpod
                                                    // postoje tri slu�aja u kojima je potrebno dodati nule kako bi koder mogao izvr�iti kodiranje
          if (b%4==3){                              // u slu�aju kada nedostaje jedan znak dodajemo jednu nulu
          tokpod1=fopen(argv[1],"a");               // otvaramo tok podataka tokpod1    
             fputc('0',tokpod1);                    // dodajemo znak koji nedostaje
          fclose(tokpod1);                          // zatvaramo tok podataka tokpod1
          }  
          if (b%4==2){                              // u slu�aju kada nedostaju dva znaka dodajemo dvije nule
          tokpod1=fopen(argv[1],"a");               // otvaramo tok podataka tokpod1
             fputc('0',tokpod1);fputc('0',tokpod1); // dodajemo znakove  koji nedostaju
          fclose(tokpod1);                          // zatvaramo tok podataka tokpod1
          }  
          if (b%4==1){                              // u slu�aju kada nedostaju tri znaka dodajemo tri nule
          tokpod1=fopen(argv[1],"a");               // otvaramo tok podataka tokpod1
             fputc('0',tokpod1);fputc('0',tokpod1);fputc('0',tokpod1);// dodajemo znakove  koji nedostaju
          fclose(tokpod1);                          // zatvaramo tok podataka tokpod1
          }  
          
          
     tokpod=fopen(argv[1],"r");                     // otvaramo tok podataka tokpod
         
    while ((c=fgetc(tokpod)) != EOF){               // u�itavamo jedan po jedan znak do kraja ulazne datoteke
    i++;                                            
    niz[i]=c;                                       // u�itavamo �etiri znaka u niz jedan po jedan
    
    if (i==3){                                      // nakon �to u�itamo �etiri znaka vr�imo kodiranje
       niz1[0]=(niz[0]+niz[1]+niz[3]-144)%2+48;     // ra�unamo prvi za�titni bit ( ra�unamo na na�in da u�itavamo ascii vrijednosti znakova te ih zbrojimo i dijelimo s ostatkom)
       niz1[1]=(niz[0]+niz[2]+niz[3]-144)%2+48;     // ra�unamo drugi za�titni bit
       niz1[2]=niz[0];                              // prvi podatkovni bit
       niz1[3]=(niz[1]+niz[2]+niz[3]-144)%2+48;     // ra�unamo tre�i za�titni bit
       niz1[4]=niz[1];                              // drugi podatkovni bit
       niz1[5]=niz[2];                              // tre�i podatkovni bit
       niz1[6]=niz[3];                              // �etvrti podatkovni bit
       
       for (j=0;j<7;j++)                            // set od sedam znakova zapisujemo u izlaznu datoteku
           fputc(niz1[j],tokpod2);
        i=-1;                                       // inicijaliziramo broja�
       }
       
       }
       
    fclose(tokpod);                                 // zatvaramo ulazni tok podataka tokpod
    fclose(tokpod2);                                // zatvaramo izlazni tok podataka tokpod2
    return 0;
}
