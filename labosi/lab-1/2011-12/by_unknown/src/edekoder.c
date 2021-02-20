#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
void append(char* s, char c)                                   // napisana funkcija omogu�uje spajanje pojedina�nih znakova u string
{                                                              // �to nam je olak�ava rad
        int len = strlen(s);
        s[len] = c;
        s[len+1] = '\0';
}
int main(int argc, char *argv[]) {
    int b=0,niz[10],hell=0,niz1[10],i=-1,j=0,k=0,max=0,Max;    // deklariramo i inicijaliziramo varijable
        FILE *tokpod3,*tokpod1,*tokpod2;                       // deklariramo tokove podataka
   
    struct TipStructa                                          // deklariramo potrebnu strukturu
{   
    char znak;
    char kod[256];

}ArrayStructChar[256];
struct TipStructa znakovi[256] = {{0}};
char s[256],c;s[0]='\0';
    tokpod1=fopen(argv[2],"r");
    if (tokpod1 == NULL){                                   // otvaramo ulazni tok podataka tokpod1 koji sadr�i simbole i njihove kodove
               printf("Gre�ka pri otvaranju\n");            // u slu�aju nemogu�nosti otvaranja javljamo gre�ku
               exit(-99);
               }
    tokpod2=fopen(argv[1],"r");
    if (tokpod2 == NULL){                                   // otvaramo ulazni tok podataka tokpod2 koji sadr�i kodiranu poruku
               printf("Gre�ka pri otvaranju\n");            // u slu�aju nemogu�nosti otvaranja javljamo gre�ku
               exit(-99);
               }        
    tokpod3=fopen(argv[3],"w");              
    if (tokpod3 == NULL){                                   // otvaramo izlazni tok podataka 
               printf("Gre�ka pri otvaranju\n");            // u slu�aju nemogu�nosti otvaranja javljamo gre�ku
               exit(-99);
               }         
    while ((c=fgetc(tokpod1)) != EOF){                      // u�itavamo jedan po jedan znak do kraja datoteke
          
          znakovi[j].znak=c;                                // spremamo simbol na njegovo odgovaraju�e mjesto u strukturi
          k=0;
          while ((c=fgetc(tokpod1)) != '\n'){               // nakon spremljenog simbola 
                if (c!='=') {
                            append(znakovi[j].kod,c);       // u�itavamo kod simbola 
                            k++;                            // brojimo duljinu koda
                }
                }
                if (k>=max) max=k;                          // spremamo najve�u duljinu koda
                j++;
          }   
     k=0; 
    while ((c=fgetc(tokpod2)) != EOF){                      // u�itavamo jedan po jedan znak iz tokpod2(kodiranu poruku)
          append(s,c);                                      // u�itani znak stavljamo u string
          if (k<=max){                                      // provjeravamo dali je broj znakova u stringu prekora�io maksimalnu duljinu koda
          for (i=0;i<j;i++)   {                             // prolazimo kroz niz struktura
              int res = strncmp(s, znakovi[i].kod, 100);    // i uspore�ujemo u�itani niz sa kodom
              if(res == 0)                         {
                 fputc(znakovi[i].znak,tokpod3);            // ukoliko prona�emo odgovaraju�i niz koda simbol tog koda spremamo u odredi�nu datoteku
                 s[0]='\0';                                 // inicijaliziramo string i duljinu koda
                 k=0;
                                                   }
                 
                              }
                              k++;                          // ukoliko nismo prona�li odgovaraju�i kodni niz pova�avamo broj u�itanih znakova
                   }
                  else {fputc('#',tokpod3); s[0]='\0';}     // ako prema�imo maksimalnu duljinu koda stavljamo #
                                     }     
     if (k!=0) fputc('#',tokpod3);                          // ako po izvr�enju petlje je preostao niz znakova manji od maksimalne duljine koda, ali nije prona�en u nizu struktura tako�er stavljamo #
                                                            // ali nije prona�en u nizu struktura tako�er stavljamo #
    fclose(tokpod1);                                        // zatvaramo tokove podataka
    fclose(tokpod2);
    fclose(tokpod3);
    return 0;
}
