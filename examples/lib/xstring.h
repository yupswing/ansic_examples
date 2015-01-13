/* XSTRING LIBRARY v1.0
// developed by fox [11/12/2005]
//
// alcune utili funzioni aggiuntive (a string.h) per la gestione delle stringhe
// è sufficiente includere xstring.h per avere tutte le funzioni di string.h e
// quelle aggiuntive
*/

#include <string.h>


/*** substring
// restituisce in strdest una sottostringa di strsource
// ii_start è il punto d'inizio della sottostringa (partendo da 0)
// ii_dim è la lunghezza della sottostringa */
void substring(char* strdest, char* strsource, int ii_start, int ii_dim)
{
	int ii=0;
	if (ii_start<0) ii_start = 0; 			//non accetta ii_start negativo

	for (ii=ii_start; ii<ii_dim+ii_start; ii++)	//preleva la sottostringa dalla sorgente
		strdest[ii-ii_start] = strsource[ii];	//e la inserisce nella destinazione

	strdest[ii-ii_start] = '\0'; 			//aggiunge il delimitatore di fine stringa

	return;
}

/*** substr
//sostituisce il contenuto di una stringa con una sottostringa di se stessa
//ii_start è il punto d'inizio della sottostringa (partendo da 0)
//ii_dim è la lunghezza della sottostringa */
void substr(char* strsource, int ii_start, int ii_dim)
{
	char strdest[ii_dim]; 				/*utilizza una destinazione temporanea*/
	substring(strdest,strsource,ii_start,ii_dim);	/*esegue il substring*/
	strcpy(strsource,strdest); 			/*copia il risultato del substring nella sorgente*/

	return;
}

/*-------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------*/

/***isNumber
// restituisce 1 se il char è un numero dell'ASCII normale [0-127]*/
short int isNumber(char chrsource)
{
	if ((chrsource >= 48) && (chrsource <= 57)) return 1;
	return 0;
}

/***isLowerLetter
// restituisce 1 se il char è una lettera MINUSCOLA dell'ASCII normale [0-127]*/
short int isLowerRegularLetter(char chrsource)
{
	if ((chrsource >= 97) && (chrsource <= 122)) return 1;
	return 0;
}

/***isUpperLetter
// restituisce 1 se il char è una lettera MAIUSCOLA dell'ASCII normale [0-127]*/
short int isUpperRegularLetter(char chrsource)
{
	if ((chrsource >= 65) && (chrsource <= 90)) return 1;
	return 0;
}

/***isLowerExtendedLetter
// restituisce 1 se il char è una lettera MINUSCOLA dell'ASCII esteso [128-255]*/
short int isLowerExtendedLetter(unsigned char chrsource)
{
	if ((chrsource >= 224) && (chrsource <= 255)) return 1;
	return 0;
}

/***isUpperExtendedLetter
// restituisce 1 se il char è una lettera MAIUSCOLA dell'ASCII esteso [128-255]*/
short int isUpperExtendedLetter(unsigned char chrsource)
{
	if ((chrsource >= 192) && (chrsource <= 223)) return 1;
	return 0;
}

/***isLetter
// restituisce 1 se il char è una lettera dell'ASCII normale [0-127]*/
short int isRegularLetter(char chrsource)
{
	if (isLowerRegularLetter(chrsource) || isUpperRegularLetter(chrsource)) return 1;
    return 0;
}

/***isExtendedLetter
// restituisce 1 se il char è una lettera dell'ASCII esteso [128-255]*/
short int isExtendedLetter(unsigned char chrsource)
{
	if (isLowerExtendedLetter(chrsource) || isUpperExtendedLetter(chrsource)) return 1;
    return 0;
}

short int isLowerLetter(unsigned char chrsource)
{
    if (isLowerRegularLetter(chrsource) || isLowerExtendedLetter(chrsource)) return 1;
    return 0;
}

short int isUpperLetter(unsigned char chrsource)
{
    if (isUpperRegularLetter(chrsource) || isUpperExtendedLetter(chrsource)) return 1;
    return 0;
}

short int isLetter(unsigned char chrsource)
{
    if (isRegularLetter(chrsource) || isExtendedLetter(chrsource)) return 1;
    return 0;
}

/***isAlphaNumeric
// restituisce 1 se il char è una lettera o un numero*/
short int isAlphaNumeric(char chrsource)
{
	if (isLetter(chrsource) || isNumber(chrsource)) return 1;
	return 0;
}

/*** toLowerCase
// tutti i valori ALFABETICI vengono resi MINUSCOLI*/
void toLowerCase(char* strsource)
{
	int ii=0;
	while(1)
	{
		if (strsource[ii] == 0) break;
		if (isUpperLetter(strsource[ii]))
			strsource[ii] += 32;
		ii++;
	}
	return;
}

/*** toUpperCase
// tutti i valori ALFABETICI vengono resi MAIUSCOLI*/
void toUpperCase(char* strsource)
{
	int ii=0;
	while(1)
	{
		if (strsource[ii] == 0) break;
		if (isLowerLetter(strsource[ii]))
			strsource[ii] -= 32;
		ii++;
	}
	return;
}

/*-------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------*/

/*** indexOf
// trova la prima corrispondenza di una sottostringa in una stringa
// ii_start è il punto d'inizio [default:0]
// restituisce la posizione della prima sottostringa trovata
// oppure -1 se non ha trovato la sottostringa nella stringa*/
int indexOf(char* strsource, char* strsubstring, unsigned int ii_start)
{
	unsigned int strsubstring_len = strlen(strsubstring);
	unsigned int strsource_len = strlen(strsource);

	char strsourcesubstring[strsubstring_len];

	if (strsubstring_len>strsource_len) return -1; /*la sottostringa è più lunga della stringa*/
	
	unsigned int ii=0;
	for (ii=ii_start;ii<=strsource_len-strsubstring_len;ii++)
	{
		substring(strsourcesubstring,strsource,ii,strsubstring_len);
		if (strmatch(strsourcesubstring,strsubstring))
			return ii;
	}

	return -1;
}

/*** strmatch
// confronta due stringhe
// se sono uguali restituisce 1
// se sono diverse restituisce 0*/
int strmatch(char* strfirst,char* strsecond)
{
	unsigned int strfirst_len = strlen(strfirst);
	unsigned int strsecond_len = strlen(strsecond);
	
	if (strfirst_len!=strsecond_len) return 0;		/*le due stringhe hanno lunghezza diversa*/
	
	unsigned int ii=0;
	for(ii=0;ii<=strfirst_len;ii++)
		if (strfirst[ii]!=strsecond[ii]) return 0;	/*un carattere non corrisponde*/

	return 1;
}
