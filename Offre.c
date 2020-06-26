#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usefulFunctions.h"
typedef struct offre offre ;
struct offre{
	int idOffre;
	char *designation;
	float tarif;
	int nombreLivres;
	offre *suivant; 
};
//fonction qui permet d'ajouter une offre a une liste s'il exixte ou de le creer s'il n'existe pas
offre *ajouterOffre1(offre *liste ,int idOffre,float tarif,char *designation,int nombreLivres){
	offre *nouveau = (offre*)malloc(sizeof(offre));
	if(nouveau == NULL){
		printf("erreur dans nouveau\n");
		return NULL;
	}
	nouveau->designation=designation;
	nouveau->idOffre=idOffre;
	nouveau->nombreLivres=nombreLivres;
	nouveau->tarif=tarif;
	nouveau->suivant=NULL;
	offre *courant = liste;
	if(liste == NULL)
	{
		return nouveau;
	}
	else {
	offre *courant=liste;
	while(courant->suivant!=NULL)
	{
		courant = courant->suivant;
		
	}
	courant->suivant=nouveau;
	return liste;
    }
}

//fonction qui permet de charger les donnees a partir d'une ficher dans une liste 
offre *ChargerOffre(char *nom_fichier_client)
{
	FILE * f = fopen(nom_fichier_client, "r") ;
	offre *liste1=NULL;
	int idOffre,nbrLivres;
	char *designation;
	float tarif;
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
		idOffre=atoi(SaisirChaine(f));
		tarif=atof(SaisirChaine(f));
		designation=SaisirChaine(f);
		nbrLivres=atoi(SaisirChaine(f));
        liste1=ajouterOffre1(liste1,idOffre,tarif,designation,nbrLivres);
	}
	
	fclose(f) ;
	return liste1;
}

//fonction qui permet de sauvgarder une liste chainee dans une fichier
void SauvegarderOffre(offre *liste ,char * nom_fichier_client)
{
	FILE * f = fopen(nom_fichier_client, "w") ;
	offre *courant;
	courant = liste;
	
	while(courant!=NULL){
		fprintf(f,"%d:",courant->idOffre);
		fprintf(f,"%.2f:",courant->tarif);
		fprintf(f,"%s:",courant->designation) ;
		if(courant->suivant!=NULL)
		    fprintf(f,"%d\n",courant->nombreLivres) ;
		else if (courant->suivant==NULL)
		     fprintf(f,"%d",courant->nombreLivres) ;
		courant=courant->suivant;		
	}	
	fclose(f) ;
}
//fonction qui permet d'afficher les offres
void afficherOffre(char *ficher){
	offre *liste=NULL;
	liste = ChargerOffre(ficher);
	offre *courant =liste;
	printf("--------------------vos offres sont ---------------------");
	while(courant != NULL){
	printf("\n---------------------------------------------------------\n");
	printf("Id de l\'offre \t\t : %d\n",courant->idOffre);
	printf("designation de l\'offre \t : %s\n",courant->designation);
	printf("tarif de l\'offre \t : %.2f\n",courant->tarif);
	printf("nomber de livre autorise : %d\n",courant->nombreLivres);
	printf("---------------------------------------------------------\n");
	courant = courant->suivant;
 }
}
//fonction pour modifier une offre
void modifierOffre(){
	int idOffre;
	int choix;
	int choix2 = 4;
	offre *liste;
	offre *courant;
	liste=ChargerOffre("offre.txt");
	if(liste == NULL){
		printf("le fichier des offres est vide \n");
		return ;
	}
	else{
	printf("donner le ID d'offre que tu veut modifier : ");
	scanf("%d",&idOffre);
	getchar();
	courant = liste;
	//on va sortir de la boucle on deux cas soit on a trouver le ID ou bien on a arriver a la fin de liste  
	while ((courant!=NULL) && (courant->idOffre != idOffre)){
       courant = courant->suivant;
	}
	//pour tester si on'a arriver a la fin de la liste sans trouver le ID qu'on cherche 
	if (courant==NULL){
		printf("y a pas une offre avec ce ID\n");
		return;
	}
	else if(courant->idOffre == idOffre){
		do{
			printf("1) Pour changer le nom de l\'offre\n2) pour changer le nombre de livres autorise\n3)pour changer le tarif\n0)exit");
			printf("\nvotre choix : ");
			scanf("%d", &choix2);
		}while(choix2 != 0 && choix2 != 1 && choix2 != 2 && choix2 != 3);
		switch (choix2)
		{
			case 0:
				return;
			case 1:
				printf("\nEntrer le nouveau nom : ");
				getchar();
				courant->designation = SaisirChaine(stdin);
				break;
			case 2:
				printf("\nEntrer le nouveau nombre de livres autorise : ");
				scanf("%d",&courant->nombreLivres);
				break;
			case 3:
				printf("\nEntrer le nouveau tarif : ");
				scanf("%f",&courant->tarif);
				break;
		}
		
	}
	//pour donner le choix au utilisateur de sauvgarder les changments au de ne pas le faire
	do{
	printf("voulez vous sauvgarder les changements ? \n");
	printf("entez 1 pour valider ou 0 sinon : ");
	scanf("%d",&choix);
    }while((choix != 0) && (choix != 1));
	if(choix == 1){
    	SauvegarderOffre(liste ,"offre.txt");
    	printf("vous avez sauvgarder.\n");
    }
    else if (choix == 0)
         printf("vous n'avez pas sauvgarder.\n");
}
}

//fonction qui permet d'ajouter une offre dans le ficher d'offres s'il ya pas une autre offre avec le meme ID ou avec les meme caracteristiques
void ajouterOffre2(){
	offre *liste;
	int idOffre,nbrLivres,choix;
	char *designation;
	float tarif;
	idOffre = getId("offre.txt") + 1;
	liste=ChargerOffre("offre.txt");
	printf("donner les informations de l'offre a ajoutrer \n");
//	printf("idOffre :");
//	scanf("%d",&idOffre);
	getchar();
	printf("Nom de l\'offre :");
	designation = SaisirChaine(stdin);
	printf("nombre de livres autorise :");
	scanf("%d",&nbrLivres);
	printf("tarif :");
	scanf("%f",&tarif);
	//si le ficher est vide on va ajouter notre offre
	if(liste == NULL){
		liste = ajouterOffre1(liste,idOffre,tarif,designation,nbrLivres);
	}
	//si le fichier n'est pas vide il faut verifier si on a une autre offre avec le meme ID 
	//ou bien avec les meme informations
	else{
	offre *nouveau = (offre*)malloc(sizeof(offre));
	offre *courant;
	if(nouveau == NULL){
		printf("erreur dans nouveau\n");
		return;
	}
	nouveau->designation=designation;
	nouveau->idOffre=idOffre;
	nouveau->nombreLivres=nbrLivres;
	nouveau->tarif=tarif;
	nouveau->suivant=NULL;
	courant = liste;
	while((courant->suivant!=NULL) && (courant->idOffre != idOffre)){
		courant = courant->suivant;
	}
	if(courant->idOffre == idOffre){
		printf("il'ya un autre offre avec le meme ID \n");
		return;
	}
	else if ((courant->tarif == tarif) && (courant->nombreLivres == nbrLivres)&&(strcmp(designation,courant->designation)==0) ){
	 	printf("vous avez un autre offre avec les memes caracteristiques \n");
	 	return;
	 }
	else if(courant->suivant == NULL){
		 courant->suivant=nouveau;
	}
    }
    //pour donner le choix au utilisateur de sauvgarder les changments au de ne pas le faire
	do{
	printf("voulez vous sauvgarder les changements ? \n");
	printf("entez 1 pour valider ou 0 sinon : ");
	scanf("%d",&choix);
    }while((choix != 0) && (choix != 1));
	if(choix == 1){
    	SauvegarderOffre(liste ,"offre.txt");
    	printf("vous avez sauvgarder.\n");
    }
    else if (choix == 0)
         printf("vous n'avez pas sauvgarder.\n");
}
//fonction aui permet du supprimer une offre
void supprimerOffre(){
	int idOffre;
	int choix;
	offre *liste;
	offre *courant,*precourant;
	liste=ChargerOffre("offre.txt");
	if(liste == NULL){
		printf("le fichier des offres est vide \n");
		return ;
	}
	else{
	printf("donner le ID d'offre que tu veut supprimer : ");
	scanf("%d",&idOffre);
	getchar();
	if (liste->idOffre==idOffre){
	precourant=liste;
	liste=liste->suivant;
	free(precourant);
    }
    else{
    	courant = liste;
    	while((courant != NULL) && (courant->idOffre != idOffre))
	    {
	    	precourant = courant;
	    	courant =courant->suivant;
	    }
	    if(courant == NULL){
	    	printf("vous n'avez pas une offre avec ce ID :");
	    	return;
		}
	    else if(courant->idOffre==idOffre){
	   	precourant->suivant=courant->suivant;
	   	free(courant);
	   }
	   }
	}
	do{
	printf("voulez vous sauvgarder les changements ? \n");
	printf("entez 1 pour valider ou 0 sinon : ");
	scanf("%d",&choix);
    }while((choix != 0) && (choix != 1));
	if(choix == 1){
    	SauvegarderOffre(liste ,"offre.txt");
    	printf("vous avez sauvgarder.\n");
    }
    else if (choix == 0)
         printf("vous n'avez pas sauvgarder.\n");
}
//fonction qui retourn le nombre de livres corespondant a une offre donner
int nombreLivres(int idOffre,char *fichier){
	offre *liste=NULL,*courant;
	int nbrLivre;
	liste=ChargerOffre("offre.txt");
	courant=liste;
	while((courant != NULL) && (courant->idOffre != idOffre)){
		courant = courant->suivant;
	}
	if(courant == NULL)
	   return 0;
	else if(courant->idOffre == idOffre)
	   return courant->nombreLivres;
}

int chercherOffre(int idOffre){
	offre *liste=NULL,*courant;
	liste=ChargerOffre("offre.txt");
	courant=liste;
	while(courant != NULL){
		if(courant->idOffre == idOffre)
			return 1; 
		courant = courant->suivant;
	}	
return 0;	
}

