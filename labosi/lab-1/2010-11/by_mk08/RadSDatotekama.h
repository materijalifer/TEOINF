#include <stdio.h>

/* Zapisuje polje znakova u datoteku */
/* Prvi parametar je pokaziva� na polje znakova, drugi je ime odredi�ne datoteke (koja ako postoji se pregazi) */
void ZapisiStringUDatoteku(const char *polje_znakova, const char *odredisna_datoteka)
{
	FILE *fp_odrediste = fopen(odredisna_datoteka, "w");
	
	{
		int element_polja;
		for(element_polja = 0; polje_znakova[element_polja] != '\0'; element_polja++)
		{
			fprintf(fp_odrediste, "%c", polje_znakova[element_polja]);
		}
	}

	fclose(fp_odrediste);
}

/* �ita polje znakova iz datoteke */
/* Prvi parametar je dvostruki pokaziva� na polje znakova, drugi je ime izvori�ne datoteke */
/* Ako izvori�na datoteka postoji, funkcija vra�a 0, a ako ne onda vra�a 1 */
int ProcitajStringIzDatoteke(char **ulazni_znakovi, const char *izvorna_datoteka)
{	
	FILE *fp_izvor = fopen(izvorna_datoteka, "r");
	
	if(fp_izvor == NULL)
	{
		return 1;
	}
	else
	{
		char *polje = NULL; /* pokaziva� koji reallokacijom mijenja svoju adresu */
		int element_polja = 0;

		do
		{
			polje = (char*) realloc (polje, sizeof(char)*(element_polja + 1) ); /* +1 je promjena indeksa u broj */
			if(fscanf(fp_izvor, "%c", &polje[element_polja]) == EOF)
			{
				polje[element_polja] = '\0';
				break;
			}
			element_polja++;
		}while(1);
		
		fclose(fp_izvor);

		*ulazni_znakovi = polje; /* Dajemo kona�nu adresu pokaziva�u koji je predan kao parametar */

		return 0;
	}
}