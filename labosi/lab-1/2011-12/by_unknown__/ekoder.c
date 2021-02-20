#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <math.h>
#include <limits.h>

//Funkcija za odre�ivanje mjesta u dijelu array-a int map[] gdje razlika zbroja frekvencija simbola, koje se dijele u dvije grupe, najbli�a nuli.
int distance(int map[], int start, int length)
{
    //Inicijalizacija varijabla
    int a=0, b=0, i=0, j=0, N=0;
    int temp = INT_MAX;
    
    //Tra�enje razlike zbroja frekvencija simbola koja je najbli�a nuli
    for(i=start; i<(length-1); i++)
    {
         a=0;
         b=0;
         
         //Zbrajanje frekvencija do granice
         for(j=start; j<i+1; j++)
         {
            a+=map[j];  
         }
         
         //Zbrajanje frekvencija iza granice
         for(j=i+1; j<length; j++)
         {
            b+=map[j];  
         }
         
         //Usporedba apsolutne vrijednosti razlike zbroja frekvencija sa varijablom temp
         //U varijabli temp se sprema razlika zbroja frekvencija koja je najbli�a nuli
         if(abs(a-b) < temp)
         {
         temp = abs(a-b);
         //varijabla N je broj�anik koji se vra�a kako bi se znalo mjesto u arrayu gdje se treba napraviti 
         //granica radi Shannon-Fanoovog kodiranja
         N = i+1;         
         }
         
         
                  
    }
    return N;
}


//Rekurzivna funkcija koja stvara kodne rije�i za dane frekvencije simbola pomo�u Shannon-Fanoovog kodiranja
void code(char *codemap, int map[], int start, int length, int rep)
{
     int i;
     //Pozivanje funkcije distance radi odre�ivanja granice
     int N = distance(map, start, length);
         
         
         if (length - start > 1)
         {
                    
            //Upisivanje 1 iznad granice
            for(i=start; i<N; i++)
            {
                 codemap[i*250+rep] = '1';      
            }
         
            //Upisivanje 0 ispod granice
            for(i=N; i<length; i++)
            {
                 codemap[i*250+rep] = '0';        
            }
         
            rep++;
         
         
            if(N>=1 && (length-start > 1))
            {
                 //Rekurzivni poziv
                 code(codemap, map, start, N, rep);
                 code(codemap, map, N, length, rep);
            }
         }
}


int main(int argc, char *argv[])
{
    //U�itavanje izvori�ta
    *argv++;
    FILE* f = fopen(*argv,"r");
    if(f==NULL)
    { 
           printf("Nemoguce otvoriti datoteku: %s...", *argv);
           return 0;
    }
    
    //Inicijalizacija varijabla
    char symmap[250];
    char codemap[250][250];
    int countmap[250];
    
    int i =0;
    
    char *chr;
    char sym;
    
    //Ra�unanje broja i upis simbola iz ulazne datoteke;
    while (1)
    {
        sym = fgetc (f); 
        if (sym == EOF)break ;
        else
        {
            //Tra�enje ulaznog simbola u mapi simbola
            chr=strchr(symmap, sym);
            if (chr != NULL)   
            {
               //U slu�aju da postoji ulazni simbol u mapi simbola pove�aj broj�anik za taj simbol za 1
               countmap[chr-symmap]++;
                     
            }
            else
            {
                //U slu�aju da ne postoji ulazni simbol u mapi simbola dodaj ga u mapu i pove�aj broj�anik za zaj simbol za 1
               symmap[i] = sym;
               symmap[i+1] = '\0';
               i++;
               countmap[strlen(symmap)-1] = 1;
                
            }
        }
    }
    
    
  
    
  
    //Inicijalizacija varijabla
    int temp, j;
    char ctemp;
    
    //Silazno sortiranje frekvencija simbola
    for(i=1; i<strlen(symmap); i++)
	{
		 temp = countmap[i];
		 ctemp = symmap[i];
		 j = i-1;
		 while(temp>countmap[j] && j>=0)
		 {
			 countmap[j+1] = countmap[j];
			 symmap[j+1] = symmap[j];
			 j = j-1;
		 }
		 countmap[j+1] = temp;
		 symmap[j+1] = ctemp;
	 }
     
     
     
    //Pozivanje funkcije koja puni mapu sa kodnim rije�ima
    code(&codemap[0][0], countmap, 0,  strlen(symmap), 0); 
    
    //Zatvaranje datoteka
    fclose(f);
    
    //Ponovno u�itavanje izvori�ta radi prevo�enja simbola u kodne rije�i u izlaznu datoteku
    f = fopen(*argv,"r");
    if(f==NULL)
    { 
           printf("Nemoguce otvoriti datoteku: %s...", *argv);
           return 0;
    }
    //Otvaranje i stvaranje izlazne datoteke 
    *argv ++;
    FILE* fp = fopen(*argv,"w");
    if(fp==NULL)
    { 
           printf("Nemoguce otvoriti datoteku: %s...", *argv);
           return 0;
    }
    //Ispis izlaznog niza (Prijevod simbola u kodne rije�i)
    while (1)
    {
        sym = fgetc (f); 
        if (sym == EOF)break;
        else
        {
            //Tra�enje ulaznog simbola u mapi simbola
            chr=strchr(symmap, sym);
            if (chr != NULL)   
            {
            //Ispis u izlaznu datoteku
            fprintf(fp, "%s", codemap[(chr-symmap)]);        
            }
        }
    }
    //Zatvaranje datoteka
    fclose(f);
    fclose(fp);
    
    //Otvaranje i stvaranje izlazne datoteke za ispis kodnih rije�i
    *argv++;
    fp = fopen(*argv,"w");
    if(fp==NULL)
    { 
           printf("Nemoguce otvoriti datoteku: %s...", *argv);
           return 0;
    }
    
    //Ispis kodnih rije�i
    for(i=0; i<strlen(symmap); i++)
    { 
        fprintf(fp, "%c=%s\n", symmap[i], codemap[i]);
    }
    //Zatvaranje datoteka
    fclose(fp);
    
  system("PAUSE");	
  return 0;
}



