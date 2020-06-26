#include<stdio.h>
#include<stdlib.h>
#include"Auteur.h"
#include"Categorie.h"
#include"Client.h"
#include"Exemplaire.h"
#include"Livre.h"
#include"Offre.h"
#include"emprunt.h"

void menu2();
void menu()
{
	unsigned int choix = 20;
	unsigned int choix1 = 0;
	unsigned int choix2 = 0;
	unsigned int choix3 = 0;
	unsigned int choix4 = 20;
	int id;
	char Nom[30];
	char prenom[30];
	char Adresse[150];
	char Telephone[30];

	printf("\n                          ===================================================================\n");
	printf("\n                                                  Bibliotheque C.A.A.N\n");
	printf("\n                          ===================================================================\n");
	printf("\n  Menu 1:\n");
	printf("   _____________________________________________________________________________________________________________\n");
	printf("  | Client                  | Livre                                | Bibliotheque                               |\n");
	printf("  |_________________________|______________________________________|____________________________________________|\n");
	printf("  |                         |                                      |                                            |\n");
	printf("  |  1) Afficher les Clients|  6) Afficher Les Livre / Exemplaire  |  11) Emprunter un Exemplaire               |\n");
	printf("  |                         |                                      |                                            |\n");
	printf("  |  2) Ajouter un Client   |  7) Ajouter un Livre / Exemplaire    |  12) Retourner un Exemplaire               |\n");
	printf("  |                         |                                      |                                            |\n");
	printf("  |  3) Chercher un Client  |  8) Chercher un Livre / Exemplaire   |  13) Supprimer les emprunts                |\n");
	printf("  |                         |                                      |                                            |\n");
	printf("  |  4) Modifier un Client  |  9) Modifier un Livre / Exemplaire   |                                            |\n");
	printf("  |                         |                                      |                                            |\n");
	printf("  |  5) Supprimer un Client |  10) Supprimer un Livre / Exemplaire |  14) Autres(Auteurs - Categories - Offres) |\n");
	printf("  |                         |                                      |                                            |\n");
	printf("  |_________________________|______________________________________|____________________________________________|\n");

	
	do{
		printf("\nVeuillez choisir le numero de la fonction que vous souhaitez (Inserer \"0\" pour arreter) : ");
		scanf("%d", &choix);
	}while(choix != 0 &&choix != 1 && choix != 2 && choix != 3 && choix != 4 && choix != 5 && choix != 6 && choix != 7 && choix != 8 && choix != 9 && choix != 10 && choix != 11 && choix != 12 && choix != 13 && choix != 14) ;
	
	switch (choix)
	{
		case 0:
			printf("\nvous avez choisi le numero 0 L\'operation va arreter, Merci!\n");
			return;
		case 1:
			printf("\nvous avez choisi le numero 1 \n");
			do{
				printf("Veuillez confirmer votre choix (1: oui | 0: Non) :");
				scanf("%d", &choix1);
			}while(choix1 != 0 && choix1 != 1);
			
			if(choix1 == 0)
				menu();
			else if(choix1 == 1)
			{
				AfficherTousLesClients();
				do{
				printf("\n1) Retour au menu | 0) Arreter le programme ");
				scanf("%d", &choix2);
				}while(choix2 !=0 && choix2 != 1);
				if(choix2 == 1)
					menu();	
				else if(choix2 == 0)
					exit(0);
			}
		case 2:
			printf("\nvous avez choisi le numero 2 \n");	
			do{
				printf("Veuillez confirmer votre choix (1: oui | 0: Non) :");
				scanf("%d", &choix1);
			}while(choix1 != 0 && choix1 != 1);
				if(choix1 == 0)
				menu();
			else if(choix1 == 1)
			{
				char temp;
				printf("\nPour Ajouter un Client inserer les information suivants:\n");
				printf("Nom: ");
				scanf("%c",&temp);// temp statement to clear buffer
				scanf("%[^\n]",Nom);
				
				printf("\nPrenom: ");
				scanf("%c",&temp);
				scanf("%[^\n]",prenom);
				
				printf("\nAdresse: ");
				scanf("%c",&temp);
				scanf("%[^\n]",Adresse);
				
				printf("\nTelephone: ");
				scanf("%c",&temp);
				scanf("%[^\n]",Telephone);
				
				AddClient(Nom, prenom, Adresse, Telephone);
				
				do{
				printf("\n1) Retour au menu | 0) Arreter le programme ");
				scanf("%d", &choix2);
				}while(choix2 !=0 && choix2 != 1);
				if(choix2 == 1)
					menu();	
				else if(choix2 == 0)
				{
					exit(0);
				}
			}
		
		case 3:
			printf("\nvous avez choisi le numero 3 \n");
			do{
				printf("Veuillez confirmer votre choix (1: oui | 0: Non) :");
				scanf("%d", &choix1);
			}while(choix1 != 0 && choix1 != 1);
			
			if(choix1 == 0)
				menu();
			else if(choix1 == 1)
			{
				
				ChercherCient();
				do{
				printf("\n1) Retour au menu | 0) Arreter le programme ");
				scanf("%d", &choix2);
				}while(choix2 !=0 && choix2 != 1);
				if(choix2 == 1)
					menu();	
				else if(choix2 == 0)
					exit(0);
			}		
			
		case 4:
			printf("\nvous avez choisi le numero 4 \n");
			do{
				printf("Veuillez confirmer votre choix (1: oui | 0: Non) :");
				scanf("%d", &choix1);
			}while(choix1 != 0 && choix1 != 1);
			
			if(choix1 == 0)
				menu();
			else if(choix1 == 1)
			{
				printf("\nPour modifier les informations d\'un Client inserer son ID:");
				scanf("%d", &id);
				changerInfoClient(id);
				do{
				printf("\n1) Retour au menu | 0) Arreter le programme ");
				scanf("%d", &choix2);
				}while(choix2 !=0 && choix2 != 1);
				if(choix2 == 1)
					menu();	
				else if(choix2 == 0)
					exit(0);
			}
		case 5:
			printf("\nvous avez choisi le numero 5 \n");
			do{
				printf("Veuillez confirmer votre choix (1: oui | 0: Non) :");
				scanf("%d", &choix1);
			}while(choix1 != 0 && choix1 != 1);
			
			if(choix1 == 0)
				menu();
			else if(choix1 == 1)
			{
				printf("\nPour supprimer un Client inserer son ID:");
				scanf("%d", &id);
				deleteClient(id);
				do{
				printf("\n1) Retour au menu | 0) Arreter le programme ");
				scanf("%d", &choix2);
				}while(choix2 !=0 && choix2 != 1);
				if(choix2 == 1)
					menu();	
				else if(choix2 == 0)
					exit(0);
			}
			
		case 6:
			printf("\nvous avez choisi le numero 6 \n");
			do{
				printf("Veuillez confirmer votre choix (1: oui | 0: Non) :");
				scanf("%d", &choix1);
			}while(choix1 != 0 && choix1 != 1);
			
			if(choix1 == 0)
				menu();
			else if(choix1 == 1)
			{
				do{
					printf("\nPour afficher les livres entrer \"1\" et pour afficher les exemplaires entrer \"2\" : ");
					scanf("%d", &choix3);
				}while(choix3 != 1 && choix3 != 2);
				if(choix3 == 1){
					afficherlivre("Livres.txt");
					do{
						printf("\n1) Retour au menu | 0) Arreter le programme ");
						scanf("%d", &choix2);
					}while(choix2 !=0 && choix2 != 1);
						if(choix2 == 1)
							menu();	
						else if(choix2 == 0)
							exit(0);	
				}
				else if(choix3 == 2){
					AfficherTousLesExemplaires();
					do{
						printf("\n1) Retour au menu | 0) Arreter le programme ");
						scanf("%d", &choix2);
					}while(choix2 !=0 && choix2 != 1);
						if(choix2 == 1)
							menu();	
						else if(choix2 == 0)
							exit(0);
				}
			}
		case 7:
			printf("\nvous avez choisi le numero 7 \n");
			do{
				printf("Veuillez confirmer votre choix (1: oui | 0: Non) :");
				scanf("%d", &choix1);
			}while(choix1 != 0 && choix1 != 1);
			
			if(choix1 == 0)
				menu();
			else if(choix1 == 1)
			{
				do{
					printf("\nPour ajouter un livre entrer \"1\" et pour ajouter un exemplaire entrer \"2\" : ");
					scanf("%d", &choix3);
				}while(choix3 != 1 && choix3 != 2);
				if(choix3 == 1){				
					AjouterLivrelistefich();
					do{
					printf("\n1) Retour au menu | 0) Arreter le programme ");
					scanf("%d", &choix2);
					}while(choix2 !=0 && choix2 != 1);
					if(choix2 == 1)
						menu();	
					else if(choix2 == 0)
						exit(0);
			}
				else if(choix3 == 2)
				{
					AddExemplaire();
					do{
					printf("\n1) Retour au menu | 0) Arreter le programme ");
					scanf("%d", &choix2);
					}while(choix2 !=0 && choix2 != 1);
					if(choix2 == 1)
						menu();	
					else if(choix2 == 0)
						exit(0);
				}
			}
		case 8:
			printf("\nvous avez choisi le numero 8 \n");
			do{
				printf("Veuillez confirmer votre choix (1: oui | 0: Non) :");
				scanf("%d", &choix1);
			}while(choix1 != 0 && choix1 != 1);
			
			if(choix1 == 0)
				menu();
			else if(choix1 == 1)
			{
				do{
					printf("\nPour chercher un livre entrer \"1\" et pour chercher un exemplaire entrer \"2\" : ");
					scanf("%d", &choix3);
				}while(choix3 != 1 && choix3 != 2);
				if(choix3 == 1){				
					rechercherlivre();
					do{
					printf("\n1) Retour au menu | 0) Arreter le programme ");
					scanf("%d", &choix2);
					}while(choix2 !=0 && choix2 != 1);
					if(choix2 == 1)
						menu();	
					else if(choix2 == 0)
						exit(0);
			}
				else if(choix3 == 2)
				{
					ChercherExemplaire();
					do{
					printf("\n1) Retour au menu | 0) Arreter le programme ");
					scanf("%d", &choix2);
					}while(choix2 !=0 && choix2 != 1);
					if(choix2 == 1)
						menu();	
					else if(choix2 == 0)
						exit(0);
				}
			}
		case 9:
			printf("\nvous avez choisi le numero 9 \n");
			do{
				printf("Veuillez confirmer votre choix (1: oui | 0: Non) :");
				scanf("%d", &choix1);
			}while(choix1 != 0 && choix1 != 1);
			
			if(choix1 == 0)
				menu();
			else if(choix1 == 1)
			{
				do{
					printf("\nPour modifier un livre entrer \"1\" et pour modifier un exemplaire entrer \"2\" : ");
					scanf("%d", &choix3);
				}while(choix3 != 1 && choix3 != 2);
				if(choix3 == 1){				
					modifierlivre();
					do{
					printf("\n1) Retour au menu | 0) Arreter le programme ");
					scanf("%d", &choix2);
					}while(choix2 !=0 && choix2 != 1);
					if(choix2 == 1)
						menu();	
					else if(choix2 == 0)
						exit(0);
			}
				else if(choix3 == 2)
				{
					printf("\nPour modifier les informations d\'un exemplaire inserer son ID:");
					scanf("%d", &id);
					changerInfoExemplaires(id);
					do{
					printf("\n1) Retour au menu | 0) Arreter le programme ");
					scanf("%d", &choix2);
					}while(choix2 !=0 && choix2 != 1);
					if(choix2 == 1)
						menu();	
					else if(choix2 == 0)
						exit(0);
				}
			}
		case 10:
			printf("\nvous avez choisi le numero 10 \n");
			do{
				printf("Veuillez confirmer votre choix (1: oui | 0: Non) :");
				scanf("%d", &choix1);
			}while(choix1 != 0 && choix1 != 1);
			
			if(choix1 == 0)
				menu();
			else if(choix1 == 1)
			{
				do{
					printf("\nPour chercher un livre entrer \"1\" et pour chercher les exemplaire entrer \"2\" : ");
					scanf("%d", &choix3);
				}while(choix3 != 1 && choix3 != 2);
				if(choix3 == 1){				
					supprimerlivre();
					do{
					printf("\n1) Retour au menu | 0) Arreter le programme ");
					scanf("%d", &choix2);
					}while(choix2 !=0 && choix2 != 1);
					if(choix2 == 1)
						menu();	
					else if(choix2 == 0)
						exit(0);
			}
				else if(choix3 == 2)
				{
					
					deleteExemplaire();
					do{
					printf("\n1) Retour au menu | 0) Arreter le programme ");
					scanf("%d", &choix2);
					}while(choix2 !=0 && choix2 != 1);
					if(choix2 == 1)
						menu();	
					else if(choix2 == 0)
						exit(0);
				}
			}
		case 11 :
			printf("\nvous avez choisi le numero 11 \n");
			do{
				printf("Veuillez confirmer votre choix (1: oui | 0: Non) :");
				scanf("%d", &choix1);
			}while(choix1 != 0 && choix1 != 1);
			
			if(choix1 == 0)
				menu();
			else if(choix1 == 1)
			{
				ajouterEmprunt2();
				do{
				printf("\n1) Retour au menu | 0) Arreter le programme ");
				scanf("%d", &choix2);
				}while(choix2 !=0 && choix2 != 1);
				if(choix2 == 1)
					menu();	
				else if(choix2 == 0)
					exit(0);
			}
			
		case 12 :
			printf("\nvous avez choisi le numero 12 \n");
			do{
				printf("Veuillez confirmer votre choix (1: oui | 0: Non) :");
				scanf("%d", &choix1);
			}while(choix1 != 0 && choix1 != 1);
			if(choix1 == 0)
				menu();
			else if(choix1 == 1)
			{
				printf("\nEntrer ID du Client qui a le livre");
				scanf("%d", &id);
				livreRetourner(id);
				do{
				printf("\n1) Retour au menu | 0) Arreter le programme ");
				scanf("%d", &choix2);
				}while(choix2 !=0 && choix2 != 1);
				if(choix2 == 1)
					menu();	
				else if(choix2 == 0)
					exit(0);
			}
		case 13 :
			printf("\nvous avez choisi le numero 13 \n");
			do{
				printf("Veuillez confirmer votre choix (1: oui | 0: Non) :");
				scanf("%d", &choix1);
			}while(choix1 != 0 && choix1 != 1);
			if(choix1 == 0)
				menu();
			else if(choix1 == 1)
			{
				supprimerEmprunt();
				do{
				printf("\n1) Retour au menu | 0) Arreter le programme ");
				scanf("%d", &choix2);
				}while(choix2 !=0 && choix2 != 1);
				if(choix2 == 1)
					menu();	
				else if(choix2 == 0)
					exit(0);
		case 14 :
			printf("\nvous avez choisi le numero 14 \n");
			menu2();
}
}
}
void menu2()
{
	unsigned int choix1 = 3;
	unsigned int choix2 = 3;
	unsigned int choix3 = 3;
	unsigned int choix4 = 20;
	int id;
	char Nom[30];
	char prenom[30];
	char Adresse[150];
	char Telephone[30];
	
	printf("\n           ===================================================================\n");
	printf("\n                                Bibliotheque C.A.A.N\n");
	printf("\n           ===================================================================\n");
	printf("\n  Menu 2:\n");
	printf("   ___________________________________________________________________________________________\n");
	printf("  | Auteur                    | Categorie                          | Offre                    |\n");
	printf("  |___________________________|____________________________________|__________________________|\n");
	printf("  |                           |                                    |                          |\n");
	printf("  |  1) Afficher les Auteurs  |  5) Afficher Les Categories        |  10) Afficher Les Offres |\n");
	printf("  |                           |                                    |                          |\n");
	printf("  |  2) Ajouter un Auteur     |  6) Ajouter une Categories         |  11) Ajouter une Offre   |\n");
	printf("  |                           |                                    |                          |\n");
	printf("  |  3) Chercher un Auteur    |  7) Chercher une Categories        |  12) Modifier une Offre  |\n");
	printf("  |                           |                                    |                          |\n");
	printf("  |  4) Supprimer un Auteur   |  8) Modifier une Categories        |  13) Supprimer une Offre |\n");
	printf("  |                           |                                    |                          |\n");
	printf("  |                           |  9) Supprimer une Categories       |                          |\n");
	printf("  |                           |                                    |                          |\n");
	printf("  |___________________________|____________________________________|__________________________|\n");
	
	do{
		printf("\nVeuillez choisir le numero de la fonction que vous souhaitez (Inserer \"0\" pour arreter) : ");
		scanf("%d", &choix4);
	}while(choix4 != 0 && choix4 != 1 && choix4 != 2 && choix4 != 3 && choix4 != 4 && choix4 != 5 && choix4 != 6 && choix4 != 7 && choix4 != 8 && choix4 != 9 && choix4 != 10 && choix4 != 11 && choix4 != 12 && choix4 != 13);
	
	switch(choix4)
	{
		case 0:
			do{
				printf("\n1) Retour au menu 1 | 0) Arreter le programme ");
				scanf("%d", &choix2);
			}while(choix2 !=0 && choix2 != 1);
			if(choix2 == 1)
				menu();
			else if(choix2 == 0)
				exit(0);
		
		case 1:
			printf("\nvous avez choisi le numero 1 \n");
			do{
				printf("Veuillez confirmer votre choix (1: oui | 0: Non) :");
				scanf("%d", &choix1);
			}while(choix1 != 0 && choix1 != 1);
			
			if(choix1 == 0)
				menu2();
			else if(choix1 == 1)
			{
				afficherlesauteurs("Auteurs.txt");
				do{
				printf("\n1) Retour au menu | 0) Arreter le programme ");
				scanf("%d", &choix2);
				}while(choix2 !=0 && choix2 != 1);
				if(choix2 == 1)
					menu2();	
				else if(choix2 == 0)
					exit(0);
			}
			
		case 2:
			printf("\nvous avez choisi le numero 2 \n");
			do{
				printf("Veuillez confirmer votre choix (1: oui | 0: Non) :");
				scanf("%d", &choix1);
			}while(choix1 != 0 && choix1 != 1);
			
			if(choix1 == 0)
				menu2();
			else if(choix1 == 1)
			{
				Ajouterauteurlistefich();
				do{
				printf("\n1) Retour au menu | 0) Arreter le programme ");
				scanf("%d", &choix2);
				}while(choix2 !=0 && choix2 != 1);
				if(choix2 == 1)
					menu2();	
				else if(choix2 == 0)
					exit(0);
			}
		case 3:
			printf("\nvous avez choisi le numero 3 \n");
			do{
				printf("Veuillez confirmer votre choix (1: oui | 0: Non) :");
				scanf("%d", &choix1);
			}while(choix1 != 0 && choix1 != 1);
			
			if(choix1 == 0)
				menu2();
			else if(choix1 == 1)
			{
				rechercherauteur();
				do{
				printf("\n1) Retour au menu | 0) Arreter le programme ");
				scanf("%d", &choix2);
				}while(choix2 !=0 && choix2 != 1);
				if(choix2 == 1)
					menu2();	
				else if(choix2 == 0)
					exit(0);
			}
			
	//					case 4:
	//						printf("\nvous avez choisi le numero 4 \n");
	//						do{
	//							printf("Veuillez confirmer votre choix (1: oui | 0: Non) :");
	//							scanf("%d", &choix1);
	//						}while(choix1 != 0 && choix1 != 1);
	//						
	//						if(choix1 == 0)
	//							menu2();
	//						else if(choix1 == 1)
	//						{
	//							modifierauteur();
	//							do{
	//							printf("\n1) Retour au menu | 0) Arreter le programme ");
	//							scanf("%d", &choix2);
	//							}while(choix2 !=0 && choix2 != 1);
	//							if(choix2 == 1)
	//								menu2();	
	//							else if(choix2 == 0)
	//								return;
	//						}
	//						
		case 4:
			printf("\nvous avez choisi le numero 4 \n");
			do{
				printf("Veuillez confirmer votre choix (1: oui | 0: Non) :");
				scanf("%d", &choix1);
			}while(choix1 != 0 && choix1 != 1);
			
			if(choix1 == 0)
				menu2();
			else if(choix1 == 1)
			{
				supprimerauteur();
				do{
				printf("\n1) Retour au menu | 0) Arreter le programme ");
				scanf("%d", &choix2);
				}while(choix2 !=0 && choix2 != 1);
				if(choix2 == 1)
					menu2();	
				else if(choix2 == 0)
					exit(0);
			}
			
		case 5:
			printf("\nvous avez choisi le numero 5 \n");
			do{
				printf("Veuillez confirmer votre choix (1: oui | 0: Non) :");
				scanf("%d", &choix1);
			}while(choix1 != 0 && choix1 != 1);
			
			if(choix1 == 0)
				menu2();
			else if(choix1 == 1)
			{
				afficherlescategories("Categories.txt");
				do{
				printf("\n1) Retour au menu | 0) Arreter le programme ");
				scanf("%d", &choix2);
				}while(choix2 !=0 && choix2 != 1);
				if(choix2 == 1)
					menu2();	
				else if(choix2 == 0)
					exit(0);
		}
		
		case 6:
			printf("\nvous avez choisi le numero 6 \n");
			do{
				printf("Veuillez confirmer votre choix (1: oui | 0: Non) :");
				scanf("%d", &choix1);
			}while(choix1 != 0 && choix1 != 1);
			
			if(choix1 == 0)
				menu2();
			else if(choix1 == 1)
			{
				Ajoutercategorielistefich();
				do{
				printf("\n1) Retour au menu | 0) Arreter le programme ");
				scanf("%d", &choix2);
				}while(choix2 !=0 && choix2 != 1);
				if(choix2 == 1)
					menu2();	
				else if(choix2 == 0)
					exit(0);
				}
		case 7:
			printf("\nvous avez choisi le numero 7 \n");
			do{
				printf("Veuillez confirmer votre choix (1: oui | 0: Non) :");
				scanf("%d", &choix1);
			}while(choix1 != 0 && choix1 != 1);
			
			if(choix1 == 0)
				menu2();
			else if(choix1 == 1)
			{
				recherchercategorie();
				do{
				printf("\n1) Retour au menu | 0) Arreter le programme ");
				scanf("%d", &choix2);
				}while(choix2 !=0 && choix2 != 1);
				if(choix2 == 1)
					menu2();	
				else if(choix2 == 0)
					exit(0);
		}
		case 8:
			printf("\nvous avez choisi le numero 8 \n");
			do{
				printf("Veuillez confirmer votre choix (1: oui | 0: Non) :");
				scanf("%d", &choix1);
			}while(choix1 != 0 && choix1 != 1);
			
			if(choix1 == 0)
				menu2();
			else if(choix1 == 1)
			{
				modifiercategorie();
				do{
				printf("\n1) Retour au menu | 0) Arreter le programme ");
				scanf("%d", &choix2);
				}while(choix2 !=0 && choix2 != 1);
				if(choix2 == 1)
					menu2();	
				else if(choix2 == 0)
					exit(0);
	}
		case 9:
			printf("\nvous avez choisi le numero 9 \n");
			do{
				printf("Veuillez confirmer votre choix (1: oui | 0: Non) :");
				scanf("%d", &choix1);
			}while(choix1 != 0 && choix1 != 1);
			
			if(choix1 == 0)
				menu2();
			else if(choix1 == 1)
			{
				supprimercategorie();
				do{
				printf("\n1) Retour au menu | 0) Arreter le programme ");
				scanf("%d", &choix2);
				}while(choix2 !=0 && choix2 != 1);
				if(choix2 == 1)
					menu2();	
				else if(choix2 == 0)
					exit(0);
				}
		case 10:
			printf("\nvous avez choisi le numero 10 \n");
			do{
				printf("Veuillez confirmer votre choix (1: oui | 0: Non) :");
				scanf("%d", &choix1);
			}while(choix1 != 0 && choix1 != 1);
			
			if(choix1 == 0)
				menu2();
			else if(choix1 == 1)
			{
				afficherOffre("offre.txt");
				do{
				printf("\n1) Retour au menu | 0) Arreter le programme ");
				scanf("%d", &choix2);
				}while(choix2 !=0 && choix2 != 1);
				if(choix2 == 1)
					menu2();	
				else if(choix2 == 0)
					exit(0);
				}
		case 11:
			printf("\nvous avez choisi le numero 11 \n");
			do{
				printf("Veuillez confirmer votre choix (1: oui | 0: Non) :");
				scanf("%d", &choix1);
			}while(choix1 != 0 && choix1 != 1);
			
			if(choix1 == 0)
				menu2();
			else if(choix1 == 1)
			{
				ajouterOffre2();
				do{
				printf("\n1) Retour au menu | 0) Arreter le programme ");
				scanf("%d", &choix2);
				}while(choix2 !=0 && choix2 != 1);
				if(choix2 == 1)
					menu2();	
				else if(choix2 == 0)
					exit(0);
				}
			
		case 12:
			printf("\nvous avez choisi le numero 12 \n");
			do{
				printf("Veuillez confirmer votre choix (1: oui | 0: Non) :");
				scanf("%d", &choix1);
			}while(choix1 != 0 && choix1 != 1);
			
			if(choix1 == 0)
				menu2();
			else if(choix1 == 1)
			{
				modifierOffre();
				do{
				printf("\n1) Retour au menu | 0) Arreter le programme ");
				scanf("%d", &choix2);
				}while(choix2 !=0 && choix2 != 1);
				if(choix2 == 1)
					menu2();	
				else if(choix2 == 0)
					exit(0);
				}
		
		case 13:
			printf("\nvous avez choisi le numero 13 \n");
			do{
				printf("Veuillez confirmer votre choix (1: oui | 0: Non) :");
				scanf("%d", &choix1);
			}while(choix1 != 0 && choix1 != 1);
			
			if(choix1 == 0)
				menu2();
			else if(choix1 == 1)
			{
				supprimerOffre();
				do{
				printf("\n1) Retour au menu | 0) Arreter le programme ");
				scanf("%d", &choix2);
				}while(choix2 !=0 && choix2 != 1);
				if(choix2 == 1)
					menu2();	
				else if(choix2 == 0)
					exit(0);
				}
			
			
	}		
				
			
	}	

