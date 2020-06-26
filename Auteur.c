#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"usefulFunctions.h"
typedef struct Auteur{
	int idauteur;
	char *nomauteur;
	struct Auteur *suivant;
}Auteur;



Auteur *Ajouterauteurliste(Auteur *l ,int idauteur,char *nomauteur){
	Auteur *nouveau = (Auteur*)malloc(sizeof(Auteur));
	if(nouveau == NULL){
		printf("Memoire insuffisante!\n");
		return NULL;
	}
	nouveau->idauteur = idauteur;
	nouveau->nomauteur = nomauteur;
	nouveau->suivant=NULL;
	Auteur *courant = l;
	if(l == NULL)
	{
		l = nouveau;
	}
	else {
	while(courant->suivant!=NULL)
	{
		courant = courant->suivant;
		
	}
	courant->suivant=nouveau;
    }
    return l;
}
Auteur *chargerauteur(char *fich){
   FILE * f = fopen(fich, "r") ;
    Auteur *liste1 = NULL;
	int idauteur;
	char *nomauteur;
    if(f==NULL){
		printf("erreur d'ouvrire le file '");
		return NULL;
	}
	if(fgetc(f)==EOF){	
	return NULL;
	}
	else{
	fseek(f,0,SEEK_SET);
    }
	while(!feof(f))
	{
		idauteur = atoi(SaisirChaine(f));
		nomauteur = SaisirChaine(f);
       liste1 = Ajouterauteurliste(liste1,idauteur,nomauteur);
	}
	fclose(f);
	return liste1;
}
void insererauteur(Auteur *l , char *fich)
{   FILE * f = fopen(fich, "w") ;
	Auteur *courant;	
	courant = l;
	while(courant!=NULL){
		fprintf(f,"%d:",courant->idauteur);
		if(courant->suivant!=NULL)
			fprintf(f,"%s\n", courant->nomauteur) ;
		else if (courant->suivant==NULL)
			fprintf(f,"%s", courant->nomauteur) ;
		courant=courant->suivant;		
	}
	fclose(f) ;	
}
void afficherlesauteurs(char *fich){
	Auteur *l = NULL;
	l = chargerauteur(fich);
	Auteur *courant =l;
	printf("\nLa liste des auteurs\n");
	while(courant != NULL){
	printf("\n---------------------------------------------------------\n");
	printf("Id de l\'auteur \t\t:%d\t\t\n",courant->idauteur);
	printf("Nom de l\'auteur \t:%s\t\t\n",courant->nomauteur);
	courant = courant->suivant;
 }
}
int auteur_existe(char * Nom)
{
	Auteur *l = chargerauteur("Auteurs.txt");
	Auteur *courant =l;
	
	while(courant != NULL)
	{
		if(strcmp(courant->nomauteur, Nom) == 0)
		{
			return 1;
		}
	}
	return 0;
	
}
void Ajouterauteurlistefich(){
	Auteur *l ;
	int idauteur,choix;
	char *nomauteur;
	Auteur *courant2;
	int i = 0;
	l = chargerauteur("Auteurs.txt");
	courant2 = l;
	while(courant2!=NULL){
		i++;
		courant2 = courant2->suivant;
	}
//	printf("ATTENTION! id auteur commence a partir de %3d\n",i+1);
//	printf("\nid auteur :");
//	scanf("%d",&idauteur);
	getchar();
	idauteur = i+1;
	printf("nom auteur :");
    nomauteur = SaisirChaine(stdin);
	if(l == NULL){
		l = Ajouterauteurliste(l,idauteur,nomauteur);
	}
	else{
	Auteur *nouveau = (Auteur*)malloc(sizeof(Auteur));
	Auteur *courant;
	if(nouveau == NULL){
		printf("Memoire insuffisante!\n");
		return;
	}
	nouveau->idauteur = idauteur;
	nouveau->nomauteur = nomauteur;
	nouveau->suivant = NULL;
	courant = l;
	while(courant->suivant!=NULL){
		courant = courant->suivant;
	}
	if(courant->suivant == NULL){
		courant->suivant=nouveau;
	}

    }
	do{
	printf("\nConfirmer ajout auteur :\n");
	printf("\nentrez 1 pour valider ou 0 sinon : ");
	scanf("%d",&choix);
    }while((choix != 0) && (choix != 1));
	if(choix == 1){
    insererauteur(l ,"Auteurs.txt");	
    	printf("\nAuteur ajoute  avec succes\n");
    }
    else if (choix == 0)
         printf("\nAjout abandonne\n");
}
void supprimerauteur(){
	int idauteur;
	int choix;
	Auteur *l;
	Auteur *courant,*precourant;
	l = chargerauteur("Auteurs.txt");
	if(l == NULL){
		printf("\nLa liste des auteurs est vide ! \n");
		return ;
	}
	else{
	printf("donner id de auteur a supprimer : ");
	scanf("%d",&idauteur);
	getchar();
	if (l->idauteur == idauteur){
	precourant=l;
	l =l->suivant;
	free(precourant);
    }
    else{
    	courant = l;
    	while((courant != NULL) && (courant->idauteur != idauteur))
	    {
	    	precourant = courant;
	    	courant =courant->suivant;
	    }
	    if(courant == NULL){
	    	printf("\nAucun auteur ne possede cet id :");
	    	return;
		}
	   
	   	precourant->suivant=courant->suivant;
	   	free(courant);
	   }
	}
	do{
	printf("\nvoulez vous sauvgarder les changements ? \n");
	printf("entrez 1 pour valider ou 0 sinon : ");
	scanf("%d",&choix);
    }while((choix != 0) && (choix != 1));
	if(choix == 1){
    	insererauteur(l ,"Auteurs.txt");
    	printf("\nAuteur supprime avec succes !\n");
    }
    else if (choix == 0)
         printf("\nsuppression abandonne!\n");
}
void rechercherauteur(){
	Auteur *l;
	int idauteur,choix = 3;
	char *nomauteur;
	l = chargerauteur("Auteurs.txt");
	if(l == NULL){
		printf("\nle fichier  est vide \n");
		return ;
	}
	else{
	Auteur *courant,*courant2;
	do
	{
	printf("Recherche par id : 1\n");
	printf("Recherche par nom auteur : 2\n");
	printf("Exit : 0\n");
	printf("Votre choix :");
	scanf("%d",&choix);
	}while(choix != 1 && choix != 0 && choix != 2);
	if(choix == 1){
		courant = l;
		printf("Donner id auteur que vous cherchez :");
		scanf("%d",&idauteur);
	while ((courant!=NULL) && (courant->idauteur != idauteur)){
       courant = courant->suivant;
	}
	if (courant==NULL){
		printf("Cet  auteur nexiste pas dans le fichier !\n");
		return;
	}
	else{
	printf("\n---------------------------------------------------------\n");
	printf("Id auteur \t\t\t: %d\t\t\n",courant->idauteur);
	printf("Nom auteur \t\t\t: %s\t\t\n",courant->nomauteur);
	}
	}
	else if(choix == 2)
	{   courant = l;
        printf("Donner le nom de ou des auteurs que vous cherchez: ");
        getchar();
		nomauteur = SaisirChaine(stdin);
	   while ((courant!=NULL) && (strcmp(nomauteur,courant->nomauteur) != 0)){
       courant = courant->suivant;
	}
	if (courant==NULL){
		printf("Cet nom n\'existe pas dans le fichier !\n");
		return;
	}
	else {
	while(courant!=NULL)
	{
	if(strcmp(nomauteur,courant->nomauteur ) == 0)
	{
	printf("\n------------------------------------\n");
	printf("Id auteur \t: %d\t\n",courant->idauteur);
	printf("Nom auteur \t: %s\t\n",courant->nomauteur);
	printf("------------------------------------\n");
	}
	 courant = courant->suivant;
	}
	printf("\nRecherche termine\n");
     }
    }
    else if(choix == 0)
    {
    	return;
	}
}
}

int existeAuteur(int idAuteur){
	Auteur *liste,*courant;
	liste = chargerauteur("Auteurs.txt");
	courant=liste;
	while(courant != NULL){
		if(courant->idauteur == idAuteur)
			return 1; 
		courant = courant->suivant;
	}	
return 0;
}


	














