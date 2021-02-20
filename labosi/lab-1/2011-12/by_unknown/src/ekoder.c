#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <math.h>
 struct cvor
{                                                               // definiramo strukturu podataka koja nam omogu�uje u�itavanje znakova i ra�unanja njihovih vjerojatnosti
 char simbol[1];
 float vjerojatnost;
 int brojponavljanja;
 int niz[20];
 int top;
}s[1000];


typedef struct slovo slovo;
typedef struct cvor cvor;
void append(char* s, char c)                                   // napisana funkcija omogu�uje spajanje pojedina�nih znakova u string
{                                                              // �to nam je olak�ava rad
        int len = strlen(s);
        s[len] = c;
        s[len+1] = '\0';
}
void shannon(int l,int h,cvor s[])                             // Shannon-Fano kodiranje niza znakova
{
 float sum1=0,sum2=0,raz1=0,raz2=0;                            // definiramo pomo�ne varijable
 int i,d,granica,j;
 if((l+1)==h || l==h || l>h)                                   // provjeravamo  broj razli�itih znakova (0, 1 ili 2)
 {
 if(l==h || l>h)                                               // ako je broj razli�itih znakova 0 ili 1 nije mogu�e kodirati
 return;
 s[h].niz[++(s[h].top)]=1;                                     // ako je broj razli�itih znakova 2, znak s ve�om vjerojatno��u kodiramo s 1
     s[l].niz[++(s[l].top)]=0;                                 // a drugi s manjom vjerojatno��u s 0

 return;
 }
 else                                                          // ukoliko imamo vi�e od 2 razli�ita znaka
 {
 for(i=l;i<=h-1;i++                                            )// radimo na principu grupiranja vjerojatnosti u dvije skupine, te tra�imo granicu na kojoj �e razlika suma vjerojatnosti tih dviju skupina biti �to manja
 sum1=sum1+s[i].vjerojatnost;
 sum2=sum2+s[h].vjerojatnost;                                  // vjerojatnost zadnjeg znaka
 raz1=sum1-sum2;                                               // definiramo razliku izme�u simbola s najve�om vjerojatno��u i ostatka kao referentu za odlu�ivanje o razdiobi
 if(raz1< 0)                                                   
 raz1=raz1*-1;
 j=2;
 while(j!=h-l+1)
 {                                                             // prvo dijelimo znakove u dvije grupe. znaku s najve�om vjerojatno��u dodajemo slijede�eg najbli�eg u jednu grupu i ostatak znakova u drugu grupu
 granica=h-j;
 sum1=sum2=0;
 for(i=l;i<=granica;i++)                                       // ponovno zbrajamo vjerojatnosti novonastale podjele
 sum1=sum1+s[i].vjerojatnost;
 for(i=h;i>granica;i--)
 sum2=sum2+s[i].vjerojatnost;
 raz2=sum1-sum2;
 if(raz2< 0)
 raz2=raz2*-1;
 if(raz2>=raz1)                                                // ukoliko nova podjela ima ve�u ili jednaku razliku suma vjerojatnosti od prethodne izlazimo iz petlje
 break;
 raz1=raz2;                                                    // ako pak nova podjela ima manju razliku suma vjerojatnosti od prethodne uzimamu tu razliku za referentu i pove�avamo grupu znakova ve�ih vjerojatnosti za 1
 j++;
 }
granica++;                                                     // pri izlasku iz petlje ustanovili smo da je prethodna grupacija bila bolja pa se vra�amo njoj
 for(i=l;i<=granica;i++)
 s[i].niz[++(s[i].top)]=0;                                     // sve znakove iz prve grupe kodiramo s 0, 
 for(i=granica+1;i<=h;i++)
 s[i].niz[++(s[i].top)]=1;                                     // a znakove iz druge grupe kodiramo s 1
 shannon(l,granica,s);                                         // pozivamo funkciju za svaku  podgrupu koje  se zatim kodiraju na isti na�in
 shannon(granica+1,h,s);
 }
}

//////////////////////////////////////
int main(int argc, char *argv[]) {
    int i,j,k,res,ukupnoznakova,n,mark;
    float x;
    char ch[10],c;ch[0]='\0';

FILE *ulaz,*kod,*izlaz;
cvor temp;
 ulaz = fopen ( argv[1] , "r" );                              // deklariramo ulazni tok podataka
 if (ulaz == NULL){
               printf("Gre�ka pri otvaranju\n");
               getchar();                                      // u slu�aju nemogu�nosti otvaranja javljamo gre�ku
               exit(-99);
               }
i=0;
mark=0;
ukupnoznakova=0;

    n=0;
while ((c=fgetc(ulaz)) != EOF){                               // u�itavamo jedan po jedan znak iz ulaza
append(ch,c);                                                 // dodajemo znak u string
//while (fscanf(ulaz,"%1s",ch) == 1){
ukupnoznakova++;                                              // ukuupan broj znakova potreban za ra�unanje vjerojatnosti
         for( j=0;j<=n;j++){                                  
         int res = strncmp(ch, s[j].simbol, 1);               // ako znak ve� postoji u nizu struktura
          if(res == 0) {
            s[j].brojponavljanja=s[j].brojponavljanja+1;      // pove�avamo broj ponavljanja        
             mark=0;                                          // gasimo zastavicu
             ch[0]='\0';                                      // inicijaliziramo string
             break;
             }
          if (res!=0)                                         // ukoliko nije bilo znaka u nizu struktura postavljamo zastavicu za dodavanje novog znaka
           mark=1;
             }
            if (mark){                                        // ako je postavljena zastavica
               strncpy(s[n].simbol,ch,1);                     // dodajemo novi znak
               s[n].brojponavljanja=1;                        // postavljamo broj ponavljanja na 1
               mark=0;                                        // gasimo zastavicu
               ch[0]='\0';                                    // inicijaliziramo string
               n++;                                           // broj razli�itih znakova
             } 
             }  
 fclose(ulaz);
 for (k=0;k<n;k++){                                           // ra�unamo vjerojatnosti znakova
     s[k].vjerojatnost=s[k].brojponavljanja/(float)ukupnoznakova;
     }

 for(j=1;j<=n-1;j++)                                          // sortiramo znakova uzlazno po vjerojatnosti
 {
 for(i=0;i<n-1;i++)
 {
 if((s[i].vjerojatnost)>(s[i+1].vjerojatnost))
 {
 temp.vjerojatnost=s[i].vjerojatnost;
 strncpy(temp.simbol,s[i].simbol,1);
 s[i].vjerojatnost=s[i+1].vjerojatnost;
 strncpy(s[i].simbol,s[i+1].simbol,1);
 s[i+1].vjerojatnost=temp.vjerojatnost;
 strncpy(s[i+1].simbol,temp.simbol,1);
 }
 }
 }
 for(i=0;i<n;i++){
 s[i].top=-1;
 }
 
shannon(0,n-1,s);                                             // pozivamo funkciju za ra�unanje entropijskog koda
kod=fopen(argv[3],"w");                                       // otvaramo tok podataka do datoteka za spremanje koda
 for(i=n-1;i>=0;i--)
 {
 fprintf(kod,"%s=",s[i].simbol);                              // spremamo znak
 for(j=0;j<=s[i].top;j++){
 fprintf(kod,"%d",s[i].niz[j]);                               // i odgovaraju�i kod
 }
fprintf(kod,"\n");
 }

 
ulaz = fopen ( argv[1] , "r" );
if (ulaz == NULL){
               printf("Gre�ka pri otvaranju\n");
               getchar();                                     // u slu�aju nemogu�nosti otvaranja javljamo gre�ku
               exit(-99);
               }
izlaz=fopen(argv[2],"w");
if (izlaz == NULL){
               printf("Gre�ka pri otvaranju\n");
               getchar();                  // u slu�aju nemogu�nosti otvaranja javljamo gre�ku
               exit(-99);
               }
while ((c=fgetc(ulaz)) != EOF){                               // u�itavamo jedan po jedan znak iz ulaza
append(ch,c);
//while (fscanf(ulaz,"%1s",ch) == 1){
       for(k=0; k<n; ++k) {                                   // putujemo kroz niz i kada prona�emo odgovaraju�i znak
                int res = strncmp(ch, s[k].simbol, 1);
                if (res==0){
                            for(j=0;j<=s[k].top;j++)
                            fprintf(izlaz,"%d",s[k].niz[j]);  // na mjesto znaka zapisujemo njegov kod
                            ch[0]='\0';      
        }
        }
        }

fclose(ulaz);                                                 // zatvaramo tokove podataka
fclose(izlaz);
fclose(kod);
return 0;
}
