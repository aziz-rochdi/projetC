#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "usefulFunctions.h"


typedef struct SClient
{
	int IdClient ;
	char * NomClient ;
	char * PrenomClient ;
	char * AdresseClient;
	char * TelClient ;
	struct SClient * next;
}Client;

Client * getClients(char* );

int is_empty(Client *C) //Verifier si la liste est vide
{
	if(C == NULL) 
		return 1;
	return 0;
	
}

int FileEmpty(FILE *file) // Verifier si le ficher Client est vide
{ 
    long savedOffset = ftell(file);
    fseek(file, 0, SEEK_END);

    if (ftell(file) == 0){
        return 1;
    }
    fseek(file, savedOffset, SEEK_SET);
    return 0;
}

int Client_existe(char* Nom, char* Prenom, char * Adresse, char* Tel)// existance d'un client par ses informations
{
	Client *All = getClients("Client.txt");
	Client *C;
	C = All;

	while(C != NULL)
	{
		if(strcmp(C->NomClient, Nom) == 0 && strcmp(C->PrenomClient, Prenom) == 0 && strcmp(C->AdresseClient, Adresse) == 0 && strcmp(C->TelClient, Tel) == 0)
		{
			return 1;
		}
		C = C->next;
	}
	return 0;
} 

void AddClient(char* Nom, char* Prenom, char* Adresse, char* Tel) // ajouter un Client au fichier Client.txt
{
	FILE *f = fopen("Client.txt", "a+");
	Client *New;
	New = malloc(sizeof(Client));
	New -> IdClient = getId("Client.txt") + 1;
	New -> NomClient = Nom;
	New -> PrenomClient = Prenom;
	New -> AdresseClient = Adresse;
	New -> TelClient = Tel;
	New -> next = NULL;
	
	if(FileEmpty(f) == 1) 
	{
		fprintf(f,"%d:%s:%s:%s:%s", New -> IdClient, New -> NomClient, New -> PrenomClient, New -> AdresseClient, New -> TelClient);
		printf("%s %s est devenu un client",New -> NomClient,New -> PrenomClient);
		fclose(f);
		return;
	}
	else
	{
		if(Client_existe(Nom, Prenom, Adresse, Tel) == 0)
		{
			fprintf(f,"\n%d:%s:%s:%s:%s", New -> IdClient, New -> NomClient, New -> PrenomClient, New -> AdresseClient, New -> TelClient);
			printf("%s %s est devenu un client",New -> NomClient,New -> PrenomClient);
			fclose(f);
			return ;
		}
		else {
			printf("\nCe Client deja existe.\n");
			return;
		}
	}
}

Client * AddClientToList(Client* List, int id, char* Nom, char* Prenom, char * Adresse, char* Tel) // Ajouter un Client a la list chainee
{
	Client * C = malloc(sizeof(Client));
	C -> IdClient = id;
	C -> NomClient = Nom;
	C -> PrenomClient = Prenom;
	C -> AdresseClient = Adresse;
	C -> TelClient = Tel;
	C -> next = NULL;
	
	if(is_empty(List) == 1){
		List = C;
		return List;
	}
	else{
		Client *pt;
		Client *pos;
		
		pt = List;
		while(pt->next != NULL)
		{
			pos = pt;
			pt = pt -> next;
		}
		pt -> next = C;
		return List;
	}
}

Client * getClients(char* File) // Generer une liste chainee dapres le ficher Client.txt
{
	unsigned int id;
	char *Nom, *Prenom, *Adresse, *Tel; 
	Client *ListClient=NULL;
	FILE *f = fopen(File , "r");
	while(!feof(f))
	{
		id = atoi(SaisirChaine(f));
		Nom = SaisirChaine(f);
		Prenom = SaisirChaine(f);
		Adresse = SaisirChaine(f);
		Tel = SaisirChaine(f);
		ListClient = AddClientToList(ListClient, id, Nom, Prenom, Adresse, Tel);

	}
	fclose(f);
	return ListClient;
}

void AfficherTousLesClients() // Afficher Tous les clients
{
	printf("L\'affichage de tous les clients\n");
	Client *AllClient = getClients("Client.txt");
	Client *Cl;
	Cl = AllClient;
	if(Cl == NULL){
		printf("Il n\'y a pas des clients");
		return;
	}
	else{
		while(Cl != NULL)
		{
			if(Cl->IdClient == 0)
			{
				printf("\nIl n\'y a pas des clients");
				return;	
			}
			else
			{
			printf("--------------------------------------");
			printf("\nId:\t\t%i\n", Cl -> IdClient);
			printf("Nom:\t\t%s\n", Cl -> NomClient);
			printf("Prenom \t\t%s\n", Cl -> PrenomClient);
			printf("Adresse:\t%s\n", Cl -> AdresseClient);
			printf("Telephone:\t%s\n", Cl -> TelClient);
			}
			Cl = Cl -> next;
			
		}
	}
	
}

void RefrechClients(Client* list,char * file) // mis a jour le ficher Client
{
	if(list == NULL)
	{
		printf("la list est vide");
		FILE * f = fopen(file , "w");
		fclose(f);
		return;
	}
	FILE * f = fopen(file , "w");
	if(f == NULL)
	{
		printf("Can\'t open the file");
		return;
	}
	Client *curent;
	curent = list;
	while(curent != NULL){
		fprintf(f, "%d:", curent ->IdClient);
		fprintf(f, "%s:",  curent -> NomClient);
		fprintf(f, "%s:",  curent -> PrenomClient);;
		fprintf(f, "%s:",  curent -> AdresseClient);
		if(curent -> next != NULL)
		{
			fprintf(f, "%s\n",  curent -> TelClient);
		}
		else if (curent -> next == NULL)
		{
			fprintf(f, "%s",  curent -> TelClient);
	}
		curent = curent -> next;
	}
	fclose(f);
}

void changerInfoClient(int id) // modifier les info un client dapres son ID
{
	Client *AllClient = getClients("Client.txt");
	int choix;
	Client *Cl;
	Cl = AllClient;
		if(Cl == NULL){
		printf("Il n\'y a pas des clients");
		return  ;
	}
	else{
		while(Cl != NULL)
		{
			if(Cl -> IdClient == id)
			{
				printf("\nChoisissez ce que vous voulez changer:\n1 - Le nom\n2 - Le prenom\n3 - L\'adresse\n4 - Telephone\n");
				scanf("%i", &choix);
				getchar();
				switch(choix)
				{
					case 1 ://si jamais on fait des erreure au niveau de la saisir du nom 
						printf("Inserer le nouveau nom: ");
						Cl -> NomClient =SaisirChaine(stdin);
						
						break;
					case 2 ://si jamais on fait des erreure au niveau de la saisir du prenom 
						printf("Inserer le nouveau Prenom: ");
						Cl -> PrenomClient = SaisirChaine(stdin);
						break;
					case 3 :
						printf("Inserer la nouvelle Adresse: ");
						Cl -> AdresseClient = SaisirChaine(stdin);
						
						break;
					case 4 :
						printf("Inserer la nouvelle numero de telephone: ");
						Cl -> TelClient = SaisirChaine(stdin);
					
						break;
				}
				printf("\nLe nouveau profil est : \n");
				printf("\nId:\t\t%i\n", Cl -> IdClient);
				printf("\nNom:\t\t%s\n", Cl -> NomClient);
				printf("\nPrenom \t\t%s\n", Cl -> PrenomClient);
				printf("\nAdresse:\t%s\n", Cl -> AdresseClient);
				printf("\nTelephone:\t%s\n", Cl -> TelClient);
				do{
				printf("voulez vous sauvgarder les changements ? \n");
				printf("entez 1 pour valider ou 0 sinon : ");
				scanf("%d",&choix);
			    }while((choix != 0) && (choix != 1));
				if(choix == 1){
			    	RefrechClients(AllClient,"Client.txt");
			    	printf("vous avez sauvgarder.\n");
			    	return ;
		        }
		        else if (choix == 0){
		         printf("vous n'avez pas sauvgarder.\n");
		         return ;
		        }
			}
			Cl = Cl -> next;
		}
		printf("Ce Client n\'existe pas");
		return ;
	}
}

void deleteClient(int id) // Supprimer un client dapres son ID
{
	int choix = 3;
	Client *AllClients = getClients("Client.txt");
	Client *CClient; // Curent Client
	Client *PClient = NULL; // Previous Client
	
	if(AllClients == NULL){
	printf("Il n\'y a pas des clients");
	return  ;
	}
	else{
		CClient = AllClients;
		while(CClient != NULL)
		{
			if(CClient -> IdClient == id)
			{
				if(PClient == NULL && CClient->next == NULL)
				{
					AllClients = NULL;
					do{
						printf("voulez vous sauvgarder les changements ? \n");
						printf("entez 1 pour valider ou 0 sinon : ");
						scanf("%d",&choix);
					    }while((choix != 0) && (choix != 1));
						if(choix == 1)
						{
					    	RefrechClients(AllClients,"Client.txt");
					    	printf("\nvous avez sauvgarder.\n");
							return;
						}
						else if (choix == 0)
						{
							printf("\nvous n'avez pas sauvgarder.\n");
							return;
						}
				}
				else if(PClient == NULL)
				{
					AllClients = CClient -> next;
						do{
						printf("voulez vous sauvgarder les changements ? \n");
						printf("entez 1 pour valider ou 0 sinon : ");
						scanf("%d",&choix);
					    }while((choix != 0) && (choix != 1));
						if(choix == 1){
					    	RefrechClients(AllClients,"Client.txt");
					    	printf("vous avez sauvgarder.\n");
					    	return;
				        }
				        else if (choix == 0){
				         printf("vous n'avez pas sauvgarder.\n");
				         return ;
				        }
				}
				else
				{
					if(CClient -> next == NULL)
					{
						PClient -> next = NULL;
						do{
						printf("voulez vous sauvgarder les changements ? \n");
						printf("entez 1 pour valider ou 0 sinon : ");
						scanf("%d",&choix);
					    }while((choix != 0) && (choix != 1));
						if(choix == 1){
					    	RefrechClients(AllClients,"Client.txt");
					    	printf("vous avez sauvgarder.\n");
					    	return ;
				        }
				        else if (choix == 0){
				         printf("vous n'avez pas sauvgarder.\n");
				         return ;
				        }
					}
					else
					{
						PClient -> next = CClient -> next;
						do{
						printf("voulez vous sauvgarder les changements ? \n");
						printf("entez 1 pour valider ou 0 sinon : ");
						scanf("%d",&choix);
					    }while((choix != 0) && (choix != 1));
						if(choix == 1){
					    	RefrechClients(AllClients,"Client.txt");
					    	printf("vous avez sauvgarder.\n");
					    	return ;
				        }
				        else if (choix == 0){
				         printf("vous n'avez pas sauvgarder.\n");
				         return ;
				        }

					}
				}
			}
			PClient = CClient;
			CClient = CClient -> next;
		}
		printf("Ce Client n\'existe pas");
		return ;
	}
}

void ChercherCient()
{
	Client *All;
	Client *C;
	int id, choix = 0;
	char *nom;
	char *prenom;
	char temp;
	
	All = getClients("client.txt");
	C = All;
	if(C == NULL)
	{
		printf("\nLa liste est vide\n");
		return;
	}
	
	printf("\nRecherche par id : 1\n");
	printf("Recherche par Nom : 2\n");
	printf("Recherche par Prenom : 3\n");
	do{
	printf("Votre choix :");
	scanf("%d",&choix);
	getchar();
	}while(choix != 1 && choix != 2 && choix != 3);
	switch(choix){
		case 1:
			printf("\nDonner id du Client que vous cherchez :");
			scanf("%d",&id);
			getchar();
			while(C != NULL)
			{
				if(C->IdClient == id)
				{
					printf("\n--------------------------------\n");
					printf("Id:\t\t%i\n", C -> IdClient);
					printf("Nom:\t\t%s\n", C -> NomClient);
					printf("Prenom \t\t%s\n", C -> PrenomClient);
					printf("Adresse:\t%s\n", C -> AdresseClient);
					printf("Telephone:\t%s\n", C -> TelClient);
					printf("--------------------------------\n");
					return;
				}
				C = C->next; 
			}
			printf("\nCette id n\'existe pas\n");
			return;
		case 2:
			printf("\nDonner le nom du Client que vous cherchez :");
			nom=SaisirChaine(stdin);
			while(C != NULL)
			{
				if(strcmp(C->NomClient, nom) == 0)
				{
					printf("\n--------------------------------\n");
					printf("Id:\t\t%i\n", C -> IdClient);
					printf("Nom:\t\t%s\n", C -> NomClient);
					printf("Prenom \t\t%s\n", C -> PrenomClient);
					printf("Adresse:\t%s\n", C -> AdresseClient);
					printf("Telephone:\t%s\n", C -> TelClient);
					printf("--------------------------------\n");
					
				}
				C = C->next;
			}
			printf("\nRecherche termine\n");
			return;
		case 3:
			printf("\nDonner le prenom du Client que vous cherchez :");
             prenom=SaisirChaine(stdin);
			while(C != NULL)
			{
				if(strcmp(C->PrenomClient, prenom)== 0)
				{
					printf("\n--------------------------------\n");
					printf("Id:\t\t%i\n", C -> IdClient);
					printf("Nom:\t\t%s\n", C -> NomClient);
					printf("Prenom \t\t%s\n", C -> PrenomClient);
					printf("Adresse:\t%s\n", C -> AdresseClient);
					printf("Telephone:\t%s\n", C -> TelClient);
					printf("--------------------------------\n");
					
				}
				C = C->next;
			}
			printf("\nRecherche termine\n");
			return;
	}
}


int Client_exist(int id) // existance d'un client par son ID
{
	Client *All = getClients("Client.txt");
	Client *C ;
	C = All;
	if(C == NULL)
	{
		printf("\nLa liste est vide\n");
		return;
	}
	while(C != NULL)
	{
		if(C->IdClient == id)
		{
			return 1;	
		}
		C = C->next;
	}
	return 0;	
}


