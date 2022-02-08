#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main(int argc, char *argv[]) {
    int b=0,c,r=0;                         // deklariramo i inicijaliziramo varijable koje koristimo
    FILE *ulazkanala,*izlazkanala;         // deklariramo tokove podataka
    
    izlazkanala=fopen(argv[2],"w");        // otvaramo izlazni tok podataka
    if (izlazkanala == NULL){
               printf("Gre�ka pri otvaranju\n");
               getchar();                  // u slu�aju nemogu�nosti otvaranja javljamo gre�ku
               exit(-99);
               }
    ulazkanala=fopen(argv[1],"r");         // otvaramo ulazni tok podataka
    if (ulazkanala == NULL){
               printf("Gre�ka pri otvaranju\n");
               getchar();                  // u slu�aju nemogu�nosti otvaranja javljamo gre�ku
               exit(-99);
               }
   
    srand( time(NULL));                    // inicijaliziramo  generator slu�ajnih brojeva
    while ((c=fgetc(ulazkanala)) != EOF) { // u�itavamo jedan po jedan znak do kraja ulazne datoteke
         b=(b+1)%1000;                     // brojimo broj u�itanih znakova u setovima po tisu�u.
         r=rand()%1000;                    // generiramo gre�ku na na mjestu r s vjerojatno��u 1/1000
                                           // ukoliko se mjesto gre�ke r poklapa s mjestom trenutno u�itanog bita b, radimo zamjenu bita
           if (b==r){                      
            if (c=='1')                    // iz 1 u 0
               c='0';
            else if (c=='0')               // iz 0 u 1
                 c='1';
                 }
                 
         fputc(c,izlazkanala);             // spremamo jedan po jedan znak u izlaznu datoteku
         }
    fclose(ulazkanala);                    // zatvaramo ulazni tok podataka
    fclose(izlazkanala);                   // zatvaramo izlazni tok podataka
    return 0;
}

