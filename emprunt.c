#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include <malloc.h>
#include <windows.h>
#include "Offre.h"
#include "usefulFunctions.h"
#include "Client.h"
#include "Exemplaire.h"
struct date {
	int jour;
	int moins;
	int annee;
};
typedef struct date date;
typedef struct emprunt emprunt;
struct emprunt {
	int idEmprunt;
	int idOffre;
	int idClient;
	int *idsExemplaires;
	date dateEmprunt;
	date dateRetour;
	emprunt *suivant; 
};
//fonction qui va etre utile pour afficher les exemplaires sous format x:x:x
void afficher(int *tab,int taille){
	int i;
	for(i =0;i<taille;i++)
	  printf("%d :",tab[i]);
	printf("\n");
}
void afficherDate(date d){
	printf("%d-%d-%d\n",d.jour,d.moins,d.annee);
}
//fonction qui retourn une tableau de int a partir d'unr chaine
//cette fonction va etre utile pour convertir le chaine returner par
//SaisirChaine() a des ints qu'on va utiliser 
int *strToInts(char *chaine,char c){
	char *ch = (char*)malloc(sizeof(char));
	int *tab=NULL;
	unsigned int i=0,j=0,k=0;
	while(1){
		if((chaine[i]==c) || (chaine[i] == '\0')){		
		   tab = (int*)realloc(tab,(j+1)*sizeof(int));
		   ch[k]='\0';
		   tab[j] = atoi(ch);
		   if(chaine[i] == '\0')
		    break;
		   ch = (char*)malloc(sizeof(char));
		   j++;
		   k=0;
		   i++;
      	}
      	else{
      	ch[k] = chaine[i];
      	k++;
      	ch = (char*)realloc(ch,(k+1)*sizeof(char));
      	i++;
        }
	}
	return tab;
}
//cette fonction va nous permettre de convertir le tableau des IDs 
//des exemplaires a une chaine formater comme suite x-x-x
char *intsToStr(int* tab,int taille){
	char *ch = (char*)malloc(2*sizeof(char));
	int i=0,j=0;
	for(i=0;i<taille;i++){
	//	sprintf(ch[i],"%d",tab[i]);
	    ch[j] = tab[i] +'0';
	    ch[j+1] = '-';
	    j+=2;
		ch = (char*)realloc(ch,(j+2)*(sizeof(char)));
	}
	ch[j-1]='\0';
	return ch;
}

//cette fonction va nous donne la possibilite d'entrer les exemplaires a emprunter en fonction de nombre 
//d'exesemplaires correspondants au idOffre passe en parametre
int *idsExemplaires(int taille){
	int *ids=(int*)malloc(sizeof(int));
	int i,tempo;
	for(i=0;i<taille;i++){
	    ids=(int*)realloc(ids,(i+1)*sizeof(int));	
	    do{
		printf("donner le ID de l'exemplaire %d : ",i+1);
		scanf("%d",&tempo);
		getchar();
		if((!existe_exemplaire(tempo)) || (!dispo(tempo)))
		  printf("cet exemplaire n'existe pas ou il est pas disponible\n");
		else if((existe_exemplaire(tempo)) && (dispo(tempo)))
		  ids[i]=tempo;
	    }while((!existe_exemplaire(tempo)) || (!dispo(tempo)));
	}
	return ids;
}
//pour les exemplaires empruntes non disponibles
void mettreLesExemplairesIndispo(int *tab,int taille){
	int i=0;
	for(i=0;i<taille;i++){
		changer_dispo(tab[i],0);
	}
}
//pour les exemplaires retournes disponibles
void mettreLesExemplairesDispo(int *tab,int taille){
	int i=0;
	for(i=0;i<taille;i++){
		changer_dispo(tab[i],1);
	}
}
//fonction qui permet d'ajouter une emprunt en donnant idEmprunt en parametre cette fonction ca va nous aider de charger les donner de fichier
//vesrs une liste 
emprunt *ajouterEmprunt(emprunt *liste ,int idEmprunt,int idOffre,int idClient,int *idsExemplaires,date dateEmprunt,date dateRetour){
	emprunt *nouveau = (emprunt*)malloc(sizeof(emprunt));
	if(nouveau == NULL){
		printf("erreur dans nouveau\n");
		return NULL;
	}
	nouveau->idEmprunt=idEmprunt;
	nouveau->idOffre=idOffre;
	nouveau->idClient=idClient;
	nouveau->idsExemplaires=idsExemplaires;
	nouveau->dateEmprunt=dateEmprunt;
	nouveau->dateRetour=dateRetour;
	nouveau->suivant=NULL;
	emprunt *courant = liste;
	if(liste == NULL)
	{
		return nouveau;
	}
	else {
	emprunt *courant=liste;
	while(courant->suivant!=NULL)
	{
		courant = courant->suivant;	
	}
	courant->suivant=nouveau;
	return liste;
    }
}
//fonction qui permet de'ajouter une emprunt avec id emprunt va etre generer en ajoutant 1 au dernier id 
emprunt *ajouterEmprunt1(emprunt *liste,int idOffre,int idClient,int *idsExemplaires,date dateEmprunt,date dateRetour){
	emprunt *nouveau = (emprunt*)malloc(sizeof(emprunt));
	int id=1;
	if(nouveau == NULL){
		printf("erreur dans nouveau\n");
		return NULL;
	}
	nouveau->idOffre=idOffre;
	nouveau->idClient=idClient;
	nouveau->idsExemplaires=idsExemplaires;
	nouveau->dateEmprunt=dateEmprunt;
	nouveau->dateRetour=dateRetour;

	nouveau->suivant=NULL;
	emprunt *courant = liste;
	if(liste == NULL)
	{   
	    nouveau->idEmprunt=id;
		return nouveau;
	}
	else {
	emprunt *courant=liste;
	while(courant->suivant!=NULL)
	{
		courant = courant->suivant;	
	}
	id = courant->idEmprunt;
	nouveau->idEmprunt=++id;
	courant->suivant=nouveau;
	return liste;
    }
}

//fonction pour charger les donner du ficher des emprunts en liste 
emprunt *ChargerEmprunt(char *nom_fichier_client)
{
	FILE * f = fopen(nom_fichier_client, "r") ;
	emprunt *liste=NULL;
	int idOffre,idClient,*idsExemplaires,idEmprunt;
	date de,dr;
	char *chaine,*chaine2,*chaine3;
	if(f==NULL){
		printf("erreur d'ouvrire le file '");
		return NULL;
	}
	//pour tester si le fichier est vide 
	if(fgetc(f)==EOF){
		return NULL;
	}
	//ici on a utiliser la fonction feek() our reposistioner le cursur au bebut du ficheir 
	//car ila ete deplacer d'une caractere par la fonction fgetc()
	else{
	fseek(f,0,SEEK_SET);
    }
	while(!feof(f))
	{
		idEmprunt=atoi(SaisirChaine(f));
		idOffre=atoi(SaisirChaine(f));
		idClient=atoi(SaisirChaine(f));
		chaine = SaisirChaine(f);
		idsExemplaires = strToInts(chaine,'-');
		chaine2 = SaisirChaine(f);
		de.jour=strToInts(chaine2,'-')[0];
		de.moins=strToInts(chaine2,'-')[1];
		de.annee=strToInts(chaine2,'-')[2];
		chaine3 = SaisirChaine(f);
		dr.jour=strToInts(chaine3,'-')[0];
		dr.moins=strToInts(chaine3,'-')[1];
		dr.annee=strToInts(chaine3,'-')[2];	
        liste=ajouterEmprunt(liste,idEmprunt,idOffre,idClient,idsExemplaires,de,dr);
	}
	
	fclose(f) ;
	return liste;
}

void SauvegarderEmprunt(emprunt * ,char * );

//fonction qui permet d'ajouter une offre dans le ficher d'offres s'il ya pas une autre offre avec le meme ID ou avec les meme caracteristiques
void ajouterEmprunt2(){
	int choix;
	emprunt *liste;
	SYSTEMTIME Time;
	GetLocalTime(&Time);
	int idOffre,idClient,*ids,id;
	date de,dr;
	char *chaine;
	liste=ChargerEmprunt("emprunt.txt");
	printf("donner les informations de l'emprunt a ajoutrer \n");
	//cette boucle a  pour but de s'assurer que le idOffre exite
	do{
	printf("idOffre :");
	scanf("%d",&idOffre);
	if(!chercherOffre(idOffre))
	   printf("y'a pas une offre avec ce ID\n");
    }while(!chercherOffre(idOffre));
    //cette boucle a  pour but de s'assurer que le idClient exite
	do{
	printf("idClient :");
	scanf("%d",&idClient);
	getchar();
	if(!Client_exist(idClient))
	   printf("y'a pas un client avec ce ID\n");
    }while(!Client_exist(idClient));
    
	ids=idsExemplaires(nombreLivres(idOffre,"offre.txt"));
	//mettre la date emprunt a la date local
	de.jour = Time.wDay;
	de.moins = Time.wMonth;
	de.annee = Time.wYear;
	//mettre la date de retour a des valeurs null en atendants que le client rendre les livre pour le changer
	dr.jour = 0;
	dr.moins = 0;
	dr.annee = 0;
	//si le ficher est vide on va ajouter notre emprunt
	if(liste == NULL){
		liste = ajouterEmprunt1(liste,idOffre,idClient,ids,de,dr);
		
	}

	else{
	emprunt *nouveau = (emprunt*)malloc(sizeof(emprunt));
	emprunt *courant=liste,*precourant;
	if(nouveau == NULL){
		printf("erreur dans nouveau\n");
		return;
	}
	nouveau->idOffre=idOffre;
	nouveau->idClient=idClient;
	nouveau->idsExemplaires=ids;
	nouveau->dateEmprunt=de;
	nouveau->dateRetour=dr;
	nouveau->suivant=NULL;
	while(courant!=NULL ){
		if((courant->idClient == idClient) && (courant->dateRetour.annee == 0))
		{
			printf("ce client a deja une ou des livres non retournes \n");
			return ;
		}
		//variable id nous permet d'avoir le dernier idEmprunt pour generie le nouveau idEmprunt en ajoutant 1
		id=courant->idEmprunt;
		precourant=courant;
		courant = courant->suivant;
	}
    if(courant == NULL){
    	nouveau->idEmprunt=++id;
		precourant->suivant=nouveau;
	}
    }
    printf("entrer 1 pour sauvgarder :");
    scanf("%d",&choix);
    if(choix == 1){
    	printf("sauvgarde avec succee !!\n");
    	mettreLesExemplairesIndispo(ids,nombreLivres(idOffre,"offre.txt"));
       SauvegarderEmprunt(liste ,"emprunt.txt");
       //mettre les exemplaires empruntes indisponible

   }
   else 
      printf("vous avez pas sauvgarder \n");
 
}

void afficherEmprunt(emprunt *liste){
	emprunt *courant =liste;
	printf("--------------------vos emprunt sont ---------------------");
	while(courant != NULL){
	printf("\n---------------------------------------------------------\n");
	printf("Id de l'offre' est \t\t\t: %d\t\t:\n",courant->idEmprunt);
	printf("designation de l'offre' est \t\t: %d\t\t:\n",courant->idOffre);
	printf("tarif de l'offre est \t\t\t: %d\t\t:\n",courant->idClient);
	printf("les exemplaires sont : ");
	afficher(courant->idsExemplaires,nombreLivres(courant->idOffre,"offre.txt"));
	printf("date emprunt est :");
	afficherDate(courant->dateEmprunt);
	printf("date retoure est :");
	afficherDate(courant->dateRetour);
	courant = courant->suivant;
 }
}
//fonction qui permet de sauvgarder une liste chainee dans une fichier
void SauvegarderEmprunt(emprunt *liste ,char * nom_fichier_client)
{
	if(liste == NULL){
		printf("la liste est vide \n");
		FILE *f =fopen(nom_fichier_client,"w");
	  fclose(f);
	  return;
     }
	FILE * f = fopen(nom_fichier_client, "w") ;
	emprunt *courant;
	courant = liste;

	while(courant!=NULL){
		fprintf(f,"%d:",courant->idEmprunt);
		fprintf(f,"%d:",courant->idOffre);
		fprintf(f,"%d:",courant->idClient);
		fprintf(f,"%s:",intsToStr(courant->idsExemplaires,nombreLivres(courant->idOffre,"offre.txt")));
		fprintf(f,"%d-%d-%d:",courant->dateEmprunt.jour,courant->dateEmprunt.moins,courant->dateEmprunt.annee);
		if(courant->suivant!=NULL)
			fprintf(f,"%d-%d-%d\n",courant->dateRetour.jour,courant->dateRetour.moins,courant->dateRetour.annee);
		else if (courant->suivant==NULL)
			fprintf(f,"%d-%d-%d",courant->dateRetour.jour,courant->dateRetour.moins,courant->dateRetour.annee);
		courant=courant->suivant;		
	}	
	fclose(f) ;
}
//cette fonction permet de changer la date de retour d'un emprunt si un client a returner le livre
void livreRetourner(int idClient){
	int choix,*ids,idOffre;
	emprunt *liste,*courant;
	SYSTEMTIME Time;
	GetLocalTime(&Time);
	liste=ChargerEmprunt("emprunt.txt");
	courant=liste;
	while(courant != NULL){
		if(courant->idClient == idClient){
		   courant->dateRetour.jour = Time.wDay;
		   courant->dateRetour.moins =Time.wMonth;
		   courant->dateRetour.annee = Time.wYear;
		   //ids et idOffre vont nous survivre pour mettre les exemplaires retournes disponible
		   ids=courant->idsExemplaires;
		   idOffre = courant->idOffre; 
		   break;
	    }
	    courant=courant->suivant;
	}
   printf("entrer 1 pour sauvgarder :");
    scanf("%d",&choix);
    if(choix == 1){
    	printf("sauvgarde avec succee !!\n");
    mettreLesExemplairesDispo(ids,nombreLivres(idOffre,"offre.txt"));
     SauvegarderEmprunt(liste ,"emprunt.txt");
     //mettre les exemplaires retournes disponible
     
   }
   else 
      printf("vous avez pas sauvgarder \n");		
}

//fonction pour supprimer les emprunts pour les quells les clients ont retourner les livres 
void supprimerEmprunt()
{    
   int choix;
	emprunt *liste=NULL;
   liste=ChargerEmprunt("emprunt.txt");
   emprunt  *courant,*precourant;

while ((liste!=NULL) && (liste->dateRetour.annee!=0)){
	precourant = liste;
	liste=liste->suivant;
	free(precourant);
}
courant=liste;
while(courant != NULL)
{
   if(courant->dateRetour.annee!=0){
   	precourant->suivant=courant->suivant;
   	free(courant);
   	courant=precourant->suivant;
   }
   else {
   	precourant = courant;
   	courant=courant->suivant;
   }
}
   printf("entrer 1 pour sauvgarder :");
    scanf("%d",&choix);
    if(choix == 1){
    	printf("sauvgarde avec succee !!\n");
     SauvegarderEmprunt(liste ,"emprunt.txt");
   }
   else 
      printf("vous avez pas sauvgarder \n");
}
