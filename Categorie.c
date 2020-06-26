#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"usefulFunctions.h"
typedef struct Categorie{
	int idcategorie;
	char *nomcategorie;
	struct Categorie *suivant;
}Categorie;

Categorie *Ajoutercategorieliste(Categorie *l ,int idcategorie,char *nomcategorie){
	Categorie *nouveau = (Categorie*)malloc(sizeof(Categorie));
	if(nouveau == NULL){
		printf("Memoire insuffisante!\n");
		return NULL;
	}
	nouveau->idcategorie = idcategorie;
	nouveau->nomcategorie = nomcategorie;
	nouveau->suivant=NULL;
	Categorie *courant = l;
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

Categorie *chargercategorie(char *fich)
{   FILE * f = fopen(fich, "r") ;
    Categorie *liste1 = NULL;
	int idcategorie;
	char *nomcategorie;
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
		idcategorie = atoi(SaisirChaine(f));
		nomcategorie = SaisirChaine(f);
       liste1 = Ajoutercategorieliste(liste1,idcategorie,nomcategorie);
	}
	fclose(f);
	return liste1;
}
void inserercategorie(Categorie *l , char *fich)
{   FILE * f = fopen(fich, "w") ;
	Categorie *courant;	
	courant = l;
	while(courant!=NULL){
		fprintf(f,"%d:",courant->idcategorie);
		if(courant->suivant!=NULL)
			fprintf(f,"%s\n", courant->nomcategorie) ;
		else if (courant->suivant==NULL)
			fprintf(f,"%s", courant->nomcategorie) ;
		courant=courant->suivant;		
	}
	fclose(f) ;	
}
void afficherlescategories(char *fich){
	Categorie *l = NULL;
	l = chargercategorie(fich);
	Categorie *courant =l;
	printf("--------------------Touts les categories de la bibliotheque ---------------------");
	while(courant != NULL){
	printf("\n---------------------------------------------------------\n");
	printf("Id du livre \t\t\t:%d\t\t\n",courant->idcategorie);
	printf("Nom du livre \t\t\t:%s\t\t\n",courant->nomcategorie);
	courant = courant->suivant;
 }
}
void modifiercategorie(){
	int idcategorie;
	int choix;
	Categorie *l;
	Categorie *courant;
	l = chargercategorie("Categories.txt");
	if(l == NULL){
		printf("le fichier  est vide \n");
		return ;
	}
	else{
	printf("donner id de la categorie que vous souhaitez modifier : ");
	scanf("%d",&idcategorie);
	getchar();
	courant = l; 
	while ((courant!=NULL) && (courant->idcategorie != idcategorie)){
       courant = courant->suivant;
	}
	if (courant==NULL){
		printf("Cette categorie nexiste pas dans le fichier !\n");
		return;
	}
	else if(courant->idcategorie == idcategorie) {
        printf("Donner le nouveau nom  de la categorie:");
		courant->nomcategorie = SaisirChaine(stdin);
	}
  do{
	printf("voulez vous vraiment modifier le nom de la categorie ? \n");
	printf("entrez 1 pour valider / 0 sinon : ");
	scanf("%d",&choix);
    }while((choix != 0) && (choix != 1));
	if(choix == 1){
    	inserercategorie(l,"Categories.txt");
    	printf("\nModification effectuee  avec succes !\n");
    }
    else if (choix == 0)
         printf("\nModification abandonnee\n");
}
}

void Ajoutercategorielistefich(){
	Categorie *l ;
	int idcategorie,choix;
	char *nomcategorie;
	Categorie *courant2;
	int i = 0;
	l = chargercategorie("Categories.txt");
	courant2 = l;
	while(courant2!=NULL){
		i++;
		courant2 = courant2->suivant;
	}
//	printf("ATTENTION! id categorie commence a partir de %3d\n",i+1);
//	printf("\nid categorie :");
//	scanf("%d",&idcategorie);
	idcategorie = i+1;
	getchar();
	printf("nom categorie :");
    nomcategorie = SaisirChaine(stdin);
	if(l == NULL){
		l = Ajoutercategorieliste(l,idcategorie,nomcategorie);
	}
	else{
	Categorie *nouveau = (Categorie*)malloc(sizeof(Categorie));
	Categorie *courant;
	if(nouveau == NULL){
		printf("Memoire insuffisante!\n");
		return;
	}
	nouveau->idcategorie = idcategorie;
	nouveau->nomcategorie = nomcategorie;
	nouveau->suivant = NULL;
	courant = l;
	while((courant->suivant!=NULL) && (strcmp(courant->nomcategorie, nomcategorie) != 0)){
		courant = courant->suivant;
	}
	if(strcmp(courant->nomcategorie, nomcategorie) == 0){
		printf("\nCet auteur existe deja  !\n");
		return;
	}
	else if(courant->suivant == NULL){
		 courant->suivant=nouveau;
	}
    }
	do{
	printf("\nConfirmer ajout de la categorie :\n");
	printf("\nentrez 1 pour valider ou 0 sinon : ");
	scanf("%d",&choix);
    }while((choix != 0) && (choix != 1));
	if(choix == 1){
    inserercategorie(l ,"Categories.txt");	
    	printf("\nCategorie ajoutee  avec succes\n");
    }
    else if (choix == 0)
         printf("\nAjout abandonne\n");
}
void supprimercategorie(){
	int idcategorie;
	int choix;
	Categorie *l;
	Categorie *courant,*precourant;
	l = chargercategorie("Categories.txt");
	if(l == NULL){
		printf("\nLa liste des categories est vide ! \n");
		return ;
	}
	else{
	printf("donner id de la categorie a supprimer : ");
	scanf("%d",&idcategorie);
	getchar();
	if (l->idcategorie == idcategorie){
	precourant=l;
	l =l->suivant;
	free(precourant);
    }
    else{
    	courant = l;
    	while((courant != NULL) && (courant->idcategorie != idcategorie))
	    {
	    	precourant = courant;
	    	courant =courant->suivant;
	    }
	    if(courant == NULL){
	    	printf("\nAucune categorie ne possede cet id :");
	    	return;
		}
	   
	   	precourant->suivant=courant->suivant;
	   	free(courant);
	   }
	}
	do{
	printf("\nConfirmez la suppression ? \n");
	printf("entrez 1 pour valider ou 0 sinon : ");
	scanf("%d",&choix);
    }while((choix != 0) && (choix != 1));
	if(choix == 1){
    	inserercategorie(l ,"Categories.txt");
    	printf("\nCategorie supprimee avec succes !\n");
    }
    else if (choix == 0)
         printf("\nsuppression abandonnee!\n");
}
void recherchercategorie(){
	Categorie *l;
	int idcategorie,choix;
	char *nomcategorie;
	l = chargercategorie("Categories.txt");
	if(l == NULL){
		printf("\nle fichier  est vide \n");
		return ;
	}
	else{
	Categorie *courant,*courant2;
	do{
		printf("Recherche par id : 1\n");
		printf("Recherche par le nom de la categorie : 2\n");
		printf("Exit: 0\n");
		printf("Votre choix :");
		scanf("%d",&choix);
	}while(choix != 0 && choix != 1 && choix != 2);
	if(choix == 1){
		courant = l;
		printf("Donner id de la categorie que vous cherchez :");
		scanf("%d",&idcategorie);
	 while ((courant!=NULL) && (courant->idcategorie != idcategorie)){
       courant = courant->suivant;
	}
	if (courant==NULL){
		printf("Cet  auteur nexiste pas dans le fichier !\n");
		return;
	}
	else{
	printf("\n---------------------------------------------------------\n");
	printf("Id auteur \t\t\t: %d\t\t\n",courant->idcategorie);
	printf("Nom auteur \t\t\t: %s\t\t\n",courant->nomcategorie);
	}
	}
	else if(choix == 2)
	{   
		courant = l;
		getchar();
        printf("Donner le nom de ou des categories que vous cherchez: ");
		nomcategorie = SaisirChaine(stdin);
	   while ((courant!=NULL) && (strcmp(nomcategorie,courant->nomcategorie) != 0)){
       courant = courant->suivant;
	}
	if (courant==NULL){
		printf("Cet nom  n\'existe pas dans le fichier !\n");
		return;
	}
	else {
	while(courant!=NULL)
	{
	if(strcmp(nomcategorie,courant->nomcategorie ) == 0)
	{
	printf("\n----------------------------------------\n");
	printf("Id auteur \t: %d\t\n",courant->idcategorie);
	printf("Nom auteur \t: %s\t\n",courant->nomcategorie);
	printf("----------------------------------------\n");

	}
	 courant = courant->suivant;
	}
		printf("\nRecherche terminer.\n");
     }
    }
    else if (choix == 0)
    {
    	return;
	}
}
}
int existeCategorie(int idCategorie){
	Categorie *liste,*courant;
	liste = chargercategorie("Categories.txt");
	courant=liste;
	while(courant != NULL){
		if(courant->idcategorie == idCategorie)
			return 1; 
		courant = courant->suivant;
	}	
return 0;
}
