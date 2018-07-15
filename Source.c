#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#define numPernottazioni 10
#define numHotel 6

//mie funzioni

int Scambia(char  S[], char X, char Y);

int ContaSegueVoc(char S[], char C);

int ContaSegueVocRIC(char S[], char C);

void Pernotta(char Citta[], char Mese[]);

void Bubble();

void Stampa();

void Esercizio44(char Citta[], int CodCliente, int *MaxNumNotti, char Risultato[]);

//mie struct 

typedef struct {
	int CodCliente;
	int CodHotel;
	char Mese[10];
	int NumNotti;
}TipoPernotta; 

typedef struct {
	int CodHotel;
	char Citta[10];
	int Prezzo;
}TipoHotel;

TipoPernotta Pernottazioni[numPernottazioni] = {
	{101,5,"FEB",1},
{ 101,5,"DIC",2 },
{ 101,3,"DIC",1 },
{ 101,4,"DIC",2 },
{ 102,1,"DIC",1 },
{ 103,3,"GEN",1 },
{ 102,5,"GEN",3 },
{ 102,2,"GEN",1 },
{ 102,6,"GEN",4 },
{ 101,1,"DIC",1 },
};

TipoHotel Hotel[numHotel] = {
	{1,"MODENA",100},
{ 2,"MODENA",150 },
{ 3,"MODENA",100 },
{ 4,"BOLOGNA",150 },
{ 5,"BOLOGNA",300 },
{ 6,"FIRENZE",300 },
};


void main()
{
	int numero;

	numero=Scambia("sostituzioni", '*', 'i');
	printf("\nnumero di sostituzioni e' %d", numero);

	numero=ContaSegueVocRIC("innanzitutto", 't');
	printf("\nnumero di volte e' %d", numero);

	Pernotta("MODENA", "DIC");

	Bubble();

	Stampa();
	int MaxNumNotti = 0;
	char Risultato[100];
	Esercizio44("BOLOGNA", 101 , &MaxNumNotti, Risultato);

	getchar();
	getchar();
}

int Scambia(char  S[], char X, char Y)
{
	//modifica stringa s sostituendo a tutte le occorrenze del carattere Y con il carattere X ad eccezione della prima occorrenza , returna il numero di sostituzioni
	int numero=0;
	int primoBool=1;
	int len = strlen(S);
	int i;
	char Smod[1000];

	for (i = 0;i < len;i++)//scannerizzo tutta la stringa
	{
		if ((S[i] == Y))//vi è una occorrenza
		{	
			if (!primoBool)//non è la prima occorrenza
			{
				Smod[i] = X;
				numero++;
			}
			
			if (primoBool)//prima occorrenza
			{
				//non modifico la stringa
				Smod[i] = S[i];
				primoBool = 0;//mi chiudo fuori
			}
		}
		if (S[i] != Y)//non è una occorrenza
		{
			Smod[i] = S[i];//se non vi è occorrenza copio e basta
		}
	}
	Smod[i] = '\0';
	printf("La stringa originale è %s", S);
	printf("\nLa stringa modificata è %s", Smod);
	return numero;//ritorno il numero di volte che ho sostituito tranne la prima occorrenza
}

int ContaSegueVoc(char S[], char C)
{
	//data una stringa S contare quante volte e restituire in cui C è immediatamente dopo una vocale
	int len = strlen(S);
	int i;
	int numero = 0;

	for (i = 0;i < len;i++)
	{
		if ((S[i+1] == C)&&(S[i]=='a'|| S[i] == 'i' || S[i] == 'e' || S[i] == 'o' || S[i] == 'u' ))
		{
			numero++;
		}
	}

	return numero;//restituisco il numero di volte in cui...
}

int ContaSegueVocRIC(char S[], char C)
{
	if (S[0] == '\0')//la stringa è finita
	{
		return 0;
	}

	if ((S[1] == C) && (S[0] == 'a' || S[0] == 'i' || S[0] == 'e' || S[0] == 'o' || S[0] == 'u'))
	{
		return 1 + ContaSegueVocRIC( S+1 , C);
	}
	ContaSegueVocRIC(S + 1, C);

}

void Pernotta(char Citta[], char Mese[])
{
	//stampa a video gli hotel della città data riportando anche il numero di notti complessive dei pernottamenti del mese specifico
	int i,j;
	int nottiPernottate = 0;

	for (i = 0;i < numHotel;i++)
	{
		if (strcmp(Hotel[i].Citta, Citta) == 0)//ho trovato un hotel della citta data
		{
			for (j = 0;j < numPernottazioni;j++)//controllo tutte le pernottazioni per calcolare il numero totali di notte pernottate per quel singolo hotel
			{
				if ((Pernottazioni[j].CodHotel==Hotel[i].CodHotel)&&(strcmp(Pernottazioni[j].Mese,Mese)==0))//ho trovato una pernottazione dell'hotel dato e anche il mese è giust
				{
					nottiPernottate = nottiPernottate + Pernottazioni[j].NumNotti;
				}
			}
			//ho tutto adesso stampo
			if (nottiPernottate!=0)//ci sono state pernopttazioni per quell'hotel
			{
				printf("\n%d   %s   %d   -Notti Pernottate Complessive = %d", Hotel[i].CodHotel, Hotel[i].Citta, Hotel[i].Prezzo, nottiPernottate);
			}
			if (nottiPernottate == 0)//non ci sono state pernopttazioni per quell'hotel
			{
				printf("\n%d   %s   %d   -NESSUN CLIENTE", Hotel[i].CodHotel, Hotel[i].Citta, Hotel[i].Prezzo);
			}
			nottiPernottate = 0;
		}
	}
}

void Bubble()
{
	//ordino hotel in base alla città e a parità di cità  iin basde al prezzo dal più economico al più costoso
	int i, j;
	TipoHotel temp;

	for (i = 0;i < numHotel - 1;i++)
	{
		for (j = 0;j < numHotel - 1 - i;j++)
		{
			if (strcmp(Hotel[j].Citta, Hotel[j + 1].Citta)>0 ||
				strcmp(Hotel[j].Citta, Hotel[j + 1].Citta) == 0 &&
				Hotel[j].Prezzo > Hotel[j + 1].Prezzo)
			{
				temp = Hotel[j];
				Hotel[j] = Hotel[j + 1];
				Hotel[j + 1] = temp;
				
			}
		}
	}
}

void Stampa()
{
	//stampare a video per ogni città il prezzo minimo degli hotel di quella città e i codici degli hotel che hanno il prezzo minimo
	int i,j;
	int prezzoMinimo = 99999;

	for (i = 0;i < numHotel;i++)//avendo ordinato arrivo fino a quando la città non cambio e li faccio tutto
	{
		if (strcmp(Hotel[i].Citta, Hotel[i + 1].Citta) != 0)//sto per cambiare città
		{
			//calcolo il prezzo minimo degli hotel nelle città sopra
			for (j = 0;j < numHotel;j++)
			{
				if ((Hotel[j].Prezzo < prezzoMinimo) && (strcmp(Hotel[j].Citta, Hotel[i].Citta) == 0))//se ve ne è bisopgnop aggiorno il prezzo minimo
				{
					prezzoMinimo = Hotel[j].Prezzo;
				}
			}
		//subito prima di cambiare la città stampo tutto
			printf("\n%s, prezzo minimo %d, negli hotel :", Hotel[i].Citta, prezzoMinimo);
			for (j = 0;j < numHotel;j++)//cerco altri hotel con quel prezzo minimo per stampare pure quelli nel caso
			{
				if ((Hotel[j].Prezzo == prezzoMinimo) && (strcmp(Hotel[j].Citta, Hotel[i].Citta) == 0))//se ho ritrovato un hotel che costa minimo ed è di quella città allora stampo anche il c odice hotel in append
				{
					printf(", %d", Hotel[j].CodHotel);
				}
			}
			//quando sono pronto a cambiare città inizializzo il prezzo minimo
			prezzoMinimo = 999999;
		}
	}
}

void Esercizio44(char Citta[], int CodCliente,int *MaxNumNotti, char Risultato[])
{
	int i,j;
	int esisteHotelBool = 0;
	int haPernottatoCittaGiustaBool = 0;
	
	for (i = 0;i < numPernottazioni;i++)//controllo tutte le pernottazioni cercando il codice clienti
	{
		if (Pernottazioni[i].CodCliente == CodCliente)//se trovo una pernottazione del codcliente dato mi devo preoccupare che sia fatta nella città data
		{
			for (j = 0;j < numHotel;j++)//controllo tutti gli hotel
			{
				if (Hotel[j].CodHotel == Pernottazioni[i].CodHotel)//se ho trovato l'hotel nel qule il cliente ha pernottato controllo che abbia pernottato nella città giusta
				{
					if (strcmp(Hotel[j].Citta, Citta) == 0)//se la città è giusta allora aggiorno il max num notti
					{
						if (Pernottazioni[i].NumNotti > (*MaxNumNotti))//allora aggiorno max num notti
						{
							*MaxNumNotti = Pernottazioni[i].NumNotti;
						}
					}
				}
			}
		}
	}
	//ora aggiorno la stringa di risultato ma prima cerco
	//cerco se ci soon hotel nella citta data
	for (i = 0;i < numHotel;i++)
	{
		if (strcmp(Hotel[i].Citta, Citta) == 0)//ho trovato un hotel della città data
		{
			esisteHotelBool = 1;
		}
		//else rimane a 0
	}
	if (!esisteHotelBool)
	{
		strcpy(Risultato, "NO_HOTEL");
	}

	//ora cerco se e solo se l'hotel esiste stampo no clienti se il codice cliente non ha pernottato in nessun hotel della città data
	for (i = 0;i < numPernottazioni;i++)
	{
		if (Pernottazioni[i].CodCliente == CodCliente)//se ho trovato una pernottazione di quel cliente vado a controllare negli hotel per vedere se ha pernottato
		{
			for (j = 0;j < numHotel;j++)
			{
				if ((Pernottazioni[i].CodHotel == Hotel[j].CodHotel) && (strcmp(Hotel[j].Citta, Citta) == 0))//se ha effettuato una pernottazione in almeno un hotel della città giusta
				{
					haPernottatoCittaGiustaBool = 1;
				}
			}
		}
	}
	if (((*MaxNumNotti) == 0) && (!haPernottatoCittaGiustaBool))//se non ha pernottato nella città giusta ma l'hotel esiste allora
	{
		strcpy(Risultato, "NO_CLIENTI");
	}

	if (haPernottatoCittaGiustaBool)//se invece ha pernottato nella città giusta
	{
		strcpy(Risultato, "OK");
	}
}
