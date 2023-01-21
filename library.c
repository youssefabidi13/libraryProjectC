#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ENTER 13												// button entrer en ascii est 13
#define TAB 9													// button tab en ascii est 9
#define BCKSPC 8												// button backspace en ascii est 8
char catagories[][16] = {"TLC", "WEB", "EN", "ADO", "C", "SE"}; // global variables
struct Utilisateur
{
	char Nom_Complet[50];
	char email[50];
	char mot_de_pass[50];
	char pseudo[50];
	char Id[50];
};
struct livres
{
	int id;
	char nom[20];
	char Auteur[20];
	int nombre_examplaire;
	char *categorie;
};
struct Emp
{
	int id;
	char nom[20];
	char prenom[20];
	char date[100];
};
int i;
char generateurDePseudo(char email[50], char pseudo[50]) // dans cette fonction on recupere le pseudo en utilisant l'address email une fois arrive '@' on affecte la valeur saisie dans pseudo
{
	for (i = 0; i < strlen(email); i++)
	{
		if (email[i] == '@')
			break;
		else
			pseudo[i] = email[i];
	}
}

void recuperateur_mdp(char mdp[50])
{
	int i;
	char ch;
	while (1)
	{
		ch = getch();
		if (ch == ENTER || ch == TAB)
		{ // ici une fois on clique sur 'tab a pour ascii 9' ou 'entre a pour ascii 13' on arrete l'insertion du password
			mdp[i] = '\0';
			break;
		}
		else if (ch == BCKSPC)
		{ // si on clique sur 'backspace=8' le curseur va decrementer et remplacer le lettre suivante par 'espace' puis on revient a la lettre precedente
			if (i > 0)
			{
				i--;
				printf("\b \b");
			}
		}
		else
		{
			mdp[i++] = ch; // ici  on stock le mdp dans mdp[] et  on affiche a l'ecran des *
			printf("* \b");
		}
	}
}
void Liste_des_emps();
void RechercherEmp();
void Liste_des_livres(void);
void gestionemp();
void authentification();
void acceuil();
void returnfunc(void);
void SuppressionLivre();
void SuppressionEmp();
void RechercherLivre();
void ajout_livre(void);
void bienvenue(void);
int login();
void mainmenu(void);
void minimenu(void);
FILE *fp, *ft, *fl,*fa,*fo,*fpt; // globale file
// liste des globales variables
int s;
char VerifierSiLivreExiste;
struct livres monLivre;
struct Emp monEmp;

int main()

{
	bienvenue();
	login();
	getch();
	return 0;
}

void bienvenue() // function de bienvenue screen
{
	login();
}
char pseudo[50], mdp[50];

struct Utilisateur usr;
int login()
{
	struct Utilisateur Utilisateur;
	char mot_de_pass2[50];
	FILE *fp;
	int choix, trouve_utilisateur = 0;
	printf("\nVeuillez entrer votre choix");
	printf("\n1.S'inscrire");
	printf("\n2.Se connecter");
	printf("\n3.Quitter");
	printf("\n\nVore choix est :\t");
	scanf("%d", &choix);
	fgetc(stdin);
	switch (choix)
	{
	case 1:
		system("cls");
		printf("\nEntrer votre nom complet:\t");
		scanf("%s", Utilisateur.Nom_Complet);
		printf("Entrer votre email:\t");
		scanf("%s", Utilisateur.email);
		printf("Entrer votre id:\t");
		scanf("%s", Utilisateur.Id);
		printf("Entrer votre mot_de_pass:\t");
		recuperateur_mdp(Utilisateur.mot_de_pass); // appeler la fonction recuperateur_mdp pour cripter le mdp
		printf("\nConfirmer votre mot_de_pass:\t");
		recuperateur_mdp(mot_de_pass2); // appeler la fonction recuperateur_mdp pour cripter le mdp

		if (!strcmp(Utilisateur.mot_de_pass, mot_de_pass2)) // si les deux mot de pass sont identiques
		{
			generateurDePseudo(Utilisateur.email, Utilisateur.pseudo); // appler la fonction generateurDePseudo pour extrair le pseudo depuis l'email
			fp = fopen("Users.bin", "a+");
			fwrite(&Utilisateur, sizeof(struct Utilisateur), 1, fp);
			if (fwrite != 0) // la structure utilisateur n'est pas vide
				printf("\n\nInsription Reussi!!, Votre Pseudo est %s", Utilisateur.pseudo);
			else
				printf("\n\nErreur qlq Part!:(");
			fclose(fp);
		}
		else
		{
			printf("\n\nLes deux mdp ne sont pas identiques");
		}
		break;

	case 2:
		printf("\nEntrer votre Pseudo:\t");
		gets(pseudo);
		printf("Entrer votre mot de pass:\t");
		recuperateur_mdp(mdp); // appele a la fct recuperateur_mdp pour cripter le mot de pass
		fp = fopen("Users.bin", "r");
		while (fread(&usr, sizeof(struct Utilisateur), 1, fp))
		{
			if (!strcmp(usr.pseudo, pseudo))	   // si le pesudo qu'on a saisi existe dans notre fichier
			{									  
				if (!strcmp(usr.mot_de_pass, mdp)) // si le mdp qu'on a saisi existe dans notre fichier
				{								   
					system("cls");
					mainmenu();
				}
				else
				{
					printf("\n\nMot de passe incorrect!");
				}
				trouve_utilisateur = 1;
			}
		}
		if (!trouve_utilisateur)
		{
			printf("\n\nvous n'etes pas inscrit'!");
		}
		fclose(fp);
		break;

	case 3:
		printf("\t\t\tmerci :)");
		return 0;
	}
	return 0;
}
void mainmenu()
{
	system("cls");
	int i;
	printf(" \t\t\t\t1Menu\n");
	printf("\n 1:Gestion des livres\n");
	printf("\n 2:Gestion des emprunteurs\n");
	printf("\n 3.Importer fichier HTML\n");
	printf("\n 4.Exporter un fichier Html vers un fichier Excel\n");
	printf("\n 5.Exporter un fichier Html vers un fichier text\n");
	printf("\n 6.Stocker un fichier Html dans une liste doublement châinée\n");
	printf("\n 7.Creer la page d'authentification de votre site\n");
	printf("\n 8.Creer la page d'acceuil\n");
	printf("\n 9.Gestion des liens entre les pages web\n");
	printf("\n 10. Quitter\n");
	printf("Entrer un choix:\n");
	switch (getch())
	{
	case '1':
		minimenu();
	case '2':
		gestionemp();	
	case '7':
		authentification();
	case '8':
		acceuil();
	case 'q':
		system("cls");
		exit(0);
	}
}
void minimenu()
{
	system("cls");
	int i;
	printf(" ---------------------MAIN MENU---------------------- ");
	printf("\n 1. Ajouter un livre   ");
	printf("\n 2. Supprimer un livre");
	printf("\n 3. Chercher un livre");
	printf("\n 4. liste des livres");
	printf("\n 5. Quitter");
	printf("\nEntrer votre choix!:");
	switch (getch())
	{
	case '1':
		ajout_livre();
		break;
	case '2':
		SuppressionLivre();
		break;
	case '3':
		RechercherLivre();
		break;
	case '4':
		Liste_des_livres();
		break;
	case '5':
	{
		system("cls");
		exit(0);
	}
	default:
	{
		printf("\nAcces non autorisee!!");
		if (getch())
			minimenu();
	}
	}
}
void gestionemp()
{
	system("cls");
	int i;
	printf(" ---------------------MAIN MENU---------------------- ");
	printf("\n 1. Ajouter un emprunteur   ");
	printf("\n 2. Supprimer un emprunteur");
	printf("\n 3. Chercher un emprunteur");
	printf("\n 4. liste des emprunteurs");
	printf("\n 5. Quitter");
	printf("\nEntrer votre choix!:");
	switch (getch())
	{
	case '1':
		ajout_Emp();
		break;
	case '2':
		SuppressionEmp();
		break;
	case '3':
	RechercherEmp();
		break;
	case '4':
		Liste_des_emps();
		break;
	case '5':
	{
		system("cls");
		exit(0);
	}
	default:
	{
		printf("\nAcces non autorisee!!");
		if (getch())
			gestionemp();
	}
	}
}
int nb_livre = 0;
int IdExisteOuNon(int Id_a_saisir) // verifie si le livre existe ou non dans la bibliothèque
{
	rewind(fp); // se positioner au debut du fichier
	while (fread(&monLivre, sizeof(monLivre), 1, fp) == 1)
		if (monLivre.id == Id_a_saisir)
			return 0; // return 0 si le livre est deja existe
	return 1;		  // return 1 sinon
}
int IdExisteOuNonEmp(int Id_a_saisir) // verifie si le livre existe ou non dans la bibliothèque
{
	rewind(fpt); // se positioner au debut du fichier
	while (fread(&monEmp, sizeof(monEmp), 1, fpt) == 1)
		if (monEmp.id == Id_a_saisir)
			return 0; // return 0 si le livre est deja existe
	return 1;		  // return 1 sinon
}
int getdata()
{
	int Id_a_saisir;
	printf("Entrez les informations concernat le livre\n");
	printf("Category:\n");
	printf("%s", catagories[s - 1]);
	printf(" Code du livre:\t");
	scanf("%d", &Id_a_saisir);
	if (IdExisteOuNon(Id_a_saisir) == 0) // appeler la fonction IdExisteOuNon pour verifier si le livre est deja existe
	{
		printf("\nLe livre est deja existe\n");
		getch();
		mainmenu();
		return 0;
	}
	monLivre.id = Id_a_saisir;
	printf(" Nom du livre:");
	scanf("%s", monLivre.nom);
	printf("\n Auteur:");
	scanf("%s", monLivre.Auteur);
	printf("\n Nombre d'examplaire:");
	scanf("%d", &monLivre.nombre_examplaire);
	return 1;
}
int getdataEmp()
{
	int Id_a_saisir;
	printf("Entrez les informations concernat l'emprunteur\n");
	printf(" Code d'emprunteur:\t");
	scanf("%d", &Id_a_saisir);
	//fflush(stdin);
	if (IdExisteOuNonEmp(Id_a_saisir) == 0) // appeler la fonction IdExisteOuNon pour verifier si le livre est deja existe
	{
		printf("\nL emprunteur est deja existe\n");
		getch();
		mainmenu();
		return 0;
	}
	monEmp.id = Id_a_saisir;
	printf(" Nom du emprunteur:");
	scanf("%s", monEmp.nom);
	//fflush(stdin);
	printf("\n Prenom:");
	scanf("%s", monEmp.prenom);
	//fflush(stdin);
	printf("\n Date d emprunte:");
	scanf("%s", monEmp.date);
	//fflush(stdin);
	return 1;
}
void ajout_livre(void)
{
	FILE *fi = NULL;
	fi = fopen("ajouter.html", "w"); // generer un fichier ajouter.html pour l'ajout des livres
	if (fi != NULL)
	{
		fputs("<!DOCTYPE html>", fi);
		fputs("<html>", fi);
		fputs("<body>", fi);
		fputs("<h1>ajouter un livre</h1>", fi);
		fputs("<a href=\"home.html\">Acceuil</a><br><br>", fi);
		fputs("<form>", fi);
		fputs("Code du livre 			 : <input type=\"number\"><br><br>", fi);
		fputs("Auteur       				 : <input type=\"text\"><br><br>", fi);
		fputs("Titre de livre        : <input type=\"text\"><br><br>", fi);
		fputs("Nombre d'examplaire   : <input type=\"number\"><br><br>", fi);
		fputs("<input type=\"submit\"><br><br>", fi);
		fputs("</form>", fi);
		fputs("</body>", fi);
		fputs("</html>", fi);
		fclose(fi);
	}
	system("cls");
	int i;
	printf("\tVeuillez selectionner votre genre");
	printf("\n 1. TLC");
	printf("\n 2. WEB");
	printf("\n 3. EN");
	printf("\n 4. ADO");
	printf("\n 5. C");
	printf("\n 6. SE");
	printf("\n 7. Main menu");
	printf("\nEntrez votre choix:");
	scanf("%d", &s);
	if (s == 7)
		minimenu();
	system("cls");
	fp = fopen("database.bin", "ab+");
	if (getdata() == 1)
	{
		monLivre.categorie = catagories[s - 1];
		fseek(fp, 0, SEEK_END);						// SEEK_END se positionnr a la fin du file
		fwrite(&monLivre, sizeof(monLivre), 1, fp); // ajouter le livre a la fin du fichier
		fclose(fp);
		printf("l'enregistrement a ete bien efffectue'");
		nb_livre++;
		printf("\nVeuillez ajoutez un autre livre?(Y / N):");
		if (getch() == 'n')
			minimenu();
		else
			system("cls");
		ajout_livre();
	}
}
void ajout_Emp(void)
{
	system("cls");
	fpt = fopen("databaseEmp.bin", "ab+");
	if (getdataEmp() == 1)
	{
		fseek(fpt, 0, SEEK_END);						// SEEK_END se positionnr a la fin du file
		fwrite(&monEmp, sizeof(monEmp), 1, fpt); // ajouter le livre a la fin du fichier
		fclose(fpt);
		printf("l'enregistrement a ete bien effectue'");
		printf("\nVeuillez ajoutez un autre emprunteur?(Y / N):");
		if (getch() != 'y')
			gestionemp();
		else
			system("cls");
		ajout_Emp();
	}
}
void RechercherLivre() 
{
	system("cls");
	int Id_a_chercher;
	printf("\nRechercher : ");
	printf("\n1.Par ID:");
	printf("\n2. Revenir au menu principal");
	printf("Entrer votre choix");
	fp = fopen("database.bin", "rb+");
	rewind(fp); // se positionner au debut du fichier
	switch (getch())
	{
	case '1':
	{
		system("cls");
		printf("\nRechercher par Id ");
		printf("\nEntrer id:");
		scanf("%d", &Id_a_chercher);
		printf("en cours de recherche........");
		while (fread(&monLivre, sizeof(monLivre), 1, fp) == 1)
		{
			if (monLivre.id == Id_a_chercher) // si l'Id a rechercher existe dans le fichier il va afficher les infos de ce livvre a l'ecran
			{
				printf("\nLe livre est disponible");
				printf("\nID:%d", monLivre.id);
				printf("\nnom:%s", monLivre.nom);
				printf("\nAuteur:%s ", monLivre.Auteur);
				printf("\nNombre d'examplaire:%d ", monLivre.nombre_examplaire);
				VerifierSiLivreExiste = 'o';
			}
		}
		if (VerifierSiLivreExiste != 'o') 
		{
			printf("\rCe livre n'existe pas");
		}
		printf("Veuillez vous rechercher un autre livre? Si oui  clique sur(y) \nsinon(n)");
		if (getch() == 'y')
			RechercherLivre();
		else
			mainmenu();
		break;
	}
	case '2':
	{
		mainmenu();
		break;
	}
	default:
		getch();
		RechercherLivre();
	}
	fclose(fp);
} 
char VerifierSiEmpExiste;
void RechercherEmp() 
{
	system("cls");
	int Id_a_chercher;
	printf("\nRechercher : ");
	printf("\n1.Par ID:");
	printf("\n2. Revenir au menu principal");
	printf("Entrer votre choix");
	fpt = fopen("databaseEmp.bin", "rb+");
	rewind(fpt); // se positionner au debut du fichier
	switch (getch())
	{
	case '1':
	{
		system("cls");
		printf("\nRechercher par Id ");
		printf("\nEntrer id:");
		scanf("%d", &Id_a_chercher);
		printf("en cours de recherche........");
		while (fread(&monEmp, sizeof(monEmp), 1, fpt) == 1)
		{
			if (monEmp.id == Id_a_chercher) // si l'Id a rechercher existe dans le fichier il va afficher les infos de ce livvre a l'ecran
			{
				printf("\nL emprunteur est disponible");
				printf("\nID:%d", monEmp.id);
				printf("\nnom:%s", monEmp.nom);
				printf("\nPrenom:%s ", monEmp.prenom);
				printf("\nLa date d emprunte:%s ", monEmp.date);
				VerifierSiEmpExiste = 'o';
			}
		}
		if (VerifierSiEmpExiste != 'o') 
		{
			printf("\rCet emprunteur n'existe pas");
		}
		printf("\nVeuillez vous rechercher un autre emprunteur? Si oui  clique sur(y) \nsinon(n)");
		if (getch() == 'y')
			RechercherEmp();
		else
			mainmenu();
		break;
	}
	case '2':
	{
		mainmenu();
		break;
	}
	default:
		getch();
		RechercherEmp();
	}
	fclose(fpt);
}
void SuppressionLivre()
{
	system("cls");
	int Id_a_supprimer;
	char SupprimerEncors = 'y';

	while (SupprimerEncors == 'y')
	{
		system("cls");
		printf("\nEntrer le livre a supprimer:");
		scanf("%d", &Id_a_supprimer);
		FILE *fp;
		fp = fopen("database.bin", "rb+"); // ouvrir le fichier pour chercher le livre a supprimer
		rewind(fp);
		while (fread(&monLivre, sizeof(monLivre), 1, fp) == 1)
		{
			if (monLivre.id == Id_a_supprimer)
			{
				VerifierSiLivreExiste = 't';
			}
		}
		if (VerifierSiLivreExiste != 't')
		{
			printf("\nCe livre n'existe pas'");
			if (getch())
				mainmenu();
		}
		fclose(fp);
		if (VerifierSiLivreExiste == 't')
		{
			printf("Etes vous sur de supprimer ce livre?(Y/N):"); // confirmation de suppression
			if (getch() != 'n')
			{
				FILE *ft = NULL;
				fp = fopen("database.bin", "rb+");
				ft = fopen("temp.bin", "wb+"); 
				rewind(fp);					   
				while (fread(&monLivre, sizeof(monLivre), 1, fp) == 1)
				{
					if (monLivre.id != Id_a_supprimer)
					{
						fseek(ft, 0, SEEK_CUR);						//  se postionner a la position courante du fichier
						fwrite(&monLivre, sizeof(monLivre), 1, ft); // copier tous les livres sauf le livre a supprimer dans un nouveau fichier
					}
				}
				fclose(ft);
				fclose(fp);
				remove("database.bin");			   // supprimer le fichier
				rename("temp.bin", "database.bin"); // renomer le fichier par le nom de l'ancien fichier
				if (VerifierSiLivreExiste == 't')
				{
					printf("\nLe livre a ete supprimer");
					nb_livre--;
					printf("\nSupprimer un autre livre(Y/N)");
				}
			}
			else
				mainmenu();
			fflush(stdin);
			SupprimerEncors = getch();

		}
	}
	mainmenu();
}
void SuppressionEmp()
{
	system("cls");
	int Id_a_supprimer;
	char SupprimerEncors = 'y';

	while (SupprimerEncors == 'y')
	{
		system("cls");
		printf("\nEntrer l emprunteur a supprimer:");
		scanf("%d", &Id_a_supprimer);
		FILE *fs;
		fs = fopen("databaseEmp.bin", "rb+"); // ouvrir le fichier pour chercher le livre a supprimer
		rewind(fs);
		while (fread(&monEmp, sizeof(monEmp), 1, fs) == 1)
		{
			if (monEmp.id == Id_a_supprimer)
			{
				VerifierSiEmpExiste = 't';
			}
		}
		if (VerifierSiEmpExiste != 't')
		{
			printf("\nCet emprunteur n'existe pas'");
			if (getch())
				mainmenu();
		}
		fclose(fpt);
		if (VerifierSiEmpExiste == 't')
		{
			printf("Etes vous sur de supprimer cet emprunteur?(Y/N):"); // confirmation de suppression
			if (getch() != 'n')
			{
				FILE *ft = NULL;
				fs = fopen("databaseEmp.bin", "rb+");
				ft = fopen("temp.bin", "wb+"); 
				rewind(fs);					   
				while (fread(&monEmp, sizeof(monEmp), 1, fs) == 1)
				{
					if (monEmp.id != Id_a_supprimer)
					{
						fseek(ft, 0, SEEK_CUR);						//  se postionner a la position courante du fichier
						fwrite(&monEmp, sizeof(monEmp), 1, ft); // copier tous les livres sauf le livre a supprimer dans un nouveau fichier
					}
				}
				fclose(ft);
				fclose(fs);
				remove("databaseEmp.bin");			   // supprimer le fichier
				rename("temp.bin", "databaseEmp.bin"); // renomer le fichier par le nom de l'ancien fichier
				if (VerifierSiEmpExiste == 'r')
				{
					printf("\nCet emprunteur a ete supprimer");
					printf("\nSupprimer un autre emprunteur(Y/N)");
				}
			}
			else
				mainmenu();
			fflush(stdin);
			SupprimerEncors = getch();

		}
	}
	mainmenu();
}
void Liste_des_livres(void)
{
	int i = 0, l = 0;
	system("cls");
	FILE *fl = NULL;
	fl = fopen("Lister les livres.html", "w+");
	if (fl != NULL)
	{
		fputs("<!DOCTYPE html>", fl);
		fputs("<html>", fl);
		fputs("<body>", fl);
		fputs("<h1>Liste de tous les livres</h1>", fl);
		fputs("<a href=\"home.html\">Acceuil</a><br><br>", fl);
		fputs("<table><tr><td>Categorie:</td><td>Code du livre:</td><td>Auteur du livre:</td><td>Titre du livre</td><td>Nombre d'examplaire:</td></tr>", fl);
		fp = fopen("database.bin", "rb");
		while (fread(&monLivre, sizeof(monLivre), 1, fp) == 1)
		{
			fputs("<tr>", fl);
			fprintf(fl, "<td>%s</td>", monLivre.categorie);
			fprintf(fl, "<td>%d</td>", monLivre.id);
			fprintf(fl, "<td>%s</td>", monLivre.nom);
			fprintf(fl, "<td>%s</td>", monLivre.Auteur);
			fprintf(fl, "<td>%d</td>", monLivre.nombre_examplaire);
			fputs("</tr>", fl);
			fputs("\n\n", fl);
			l = l + monLivre.nombre_examplaire;//l calcule le nombre total des livre
		}
		fputs("</table>", fl);
		fputs("</body>", fl);
		fputs("</html>", fl);
		fclose(fl);
		fclose(fp);
	}
	printf("                              Liste des livres                                   \n\n");
	printf("Categorie     Id    Nom du livre     Auteur      Nombre d'examplaire    \n\n");
	fp = fopen("database.bin", "rb");

	while (fread(&monLivre, sizeof(monLivre), 1, fp) == 1)
	{
		printf("%s", monLivre.categorie);
		printf("\t   %d", monLivre.id);
		printf("\t\t%s", monLivre.nom);
		printf("\t\t %s", monLivre.Auteur);
		printf("\t\t  %d", monLivre.nombre_examplaire);
		printf("\n\n");
		//j++;
		i = i + monLivre.nombre_examplaire;
	}
	//printf("Le nombre total des livres =%d", i);
	fclose(fp);
	returnfunc();
}
void Liste_des_emps(void)
{
	int i = 0, l = 0;
	system("cls");
	printf("                              Liste des Emprunteurs                                  \n\n");
	printf("Id    	Nom     	prenom      	Date    \n\n");
	fp = fopen("databaseEmp.bin", "rb");

	while (fread(&monEmp, sizeof(monEmp), 1, fp) == 1)
	{
		printf("%d", monEmp.id);
		printf("\t%s", monEmp.nom);
		printf("\t\t %s", monEmp.prenom);
		printf("\t\t%s", monEmp.date);
		printf("\n\n");
		
	}
	fclose(fp);
	returnfunc();
}
void returnfunc(void)
{
		printf("Cliquer sur ENTRER pour revenir au menu principal");
	if (getch() == 13) // ENTRE a pour ascii 13
		mainmenu();
	else
		printf("\n");
		returnfunc();
}
void acceuil(){
	FILE *fa = NULL;
	fa = fopen("home.html", "w"); // generer un fichier ajouter.html pour l'ajout des livres
	if (fa != NULL)
	{
		fputs("<!DOCTYPE html>", fa);
		fputs("<html>", fa);
		fputs("<head>", fa);
		fputs("<link rel=\"stylesheet\" href=\"styles.css\">", fa);
		fputs("<title>Bibliotheque</title>", fa);		
		fputs("</head>", fa);
		fputs("<body>", fa);
		fputs("<div class=\"container\">", fa);
		fputs("<div class=\"option\"><ul class=\"operation\"><li class=\"one\"><a href=\"ajouter.html\">Ajouter un livre</a></li><li class=\"one\"><a href=\"supprimer.html\">Supprimer un livre</a></li><li class=\"one\"><a href=\"lister.html\">Lister les livres</a></li><li class=\"one\"><a href=\"rechercher.html\">rechercher un livre</a></li></ul></div></div>", fa);
		fputs("<h1>Bienvenue dans l'espace administration</h1>", fa);
		fputs("<div class=\"biblo\"><ul class=\"main-operation\">", fa);
		fputs("<li class=\"two\"><a href=\"ajouter.html\">Ajouter un livre</a></li><li class=\"two\"><a href=\"supprimer.html\">Supprimer un livre</a></li>", fa);
		fputs("<li class=\"two\"><a href=\"Lister%20les%20livres.html\">Lister les livres</a></li><li class=\"two\"><a href=\"rechercher.html\">rechercher un livre</a></li>", fa);
		fputs("</ul>", fa);
		fputs("<img src=\"https://www.archimag.com/sites/archimag.com/files/styles/article/public/web_articles/image/role_bibliotheque_coronavirus-crise.jpg?itok=Pf_-2R1e\">", fa);
		fputs("</div>", fa);
		fputs("</body>", fa);
		fputs("</html>", fa);
		fclose(fa);
	}
	mainmenu();
}
void authentification(){
		FILE *fo = NULL;
	fo = fopen("authentification.html", "w"); // generer un fichier ajouter.html pour l'ajout des livres
	if (fo != NULL)
	{
		fputs("<!DOCTYPE html>", fo);
		fputs("<html>", fo);
		fputs("<head>", fo);
		fputs("<link href=\"style.css\" rel=\"stylesheet\">", fo);		
		fputs("</head>", fo);
		fputs("<body>", fo);
		fputs("<form class=\"form\">", fo);
		fputs("<h3 class=\"h3\">Authentification</h3>", fo);
		fputs("<div class=\"div\"><label class=\"lbl\" for=\"#login\">Login:</label><input class=\"inn\" type=\"text\" name=\"login\" placeholder=\"admin\" /></div>", fo);
		fputs("<div class=\"div\"><label for=\"#Mot de passe\">Mot de passe:</label>", fo);
		fputs("<input class=\"in\" type=\"password\" name=\"Mot de passe\" placeholder=\".....\"/>", fo);
		fputs("</div>", fo);
		fputs("</ul><br />", fo);
		fputs("<button class=\"div\">Se connecter</button>", fo);
		fputs("</form>", fo);
		fputs("</body>", fo);
		fputs("</html>", fo);
		fclose(fo);
	}
	mainmenu();
}

