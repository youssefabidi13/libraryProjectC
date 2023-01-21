#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ENTER 13												// button entrer en ascii est 13
 // global variables
char catagories[][16] = {"TLC", "WEB", "EN", "ADO", "C", "SE"};
FILE *fp, *ft, *fl, *fa, *fo, *fpt; // globale file
int s;
char VerifierSiLivreExiste;
int i;
char pseudo[50], mdp[50];
char VerifierSiEmpExiste;
int l = 0;
struct Utilisateur//structure d'utilisateur
{
	char Nom_Complet[50];
	char email[50];
	char mot_de_pass[50];
	char pseudo[50];
	char Id[50];
};
struct livres //structure du livre
{
	int id;
	char nom[20];
	char Auteur[20];
	int nombre_examplaire;
	char *categorie;
};
struct Emp // structure du emprunteur
{
	int id;
	char nom[20];
	char prenom[20];
	char date_emprunte[100];
	int id_livre_a_emprute;
	char date_limite[100];

};
char generateurDePseudo(char email[50], char pseudo[50]) // dans cette fonction on recupere le pseudo en utilisant l'address email une fois arrive '@' on affecte la valeur saisie dans pseudo
{
	for (i = 0; i < strlen(email); i++)
	{
		if (email[i] == '@')// si il arrive a '@' il va s'arreter
			break;
		else
			pseudo[i] = email[i];//le nom d'utilisateur est la chaine de caractere avant '@'
	}
}

void recuperateur_mdp(char mdp[50])
{
	int i;
	char ch;
	while (1)
	{
		ch = getch();
		if (ch == ENTER )
		{ 
		// ici une fois on clique sur 'tab a pour ascii 9' ou 'entre a pour ascii 13' on arrete l'insertion du password
			mdp[i] = '\0';
			break;
		}
		else
		{
			mdp[i++] = ch; // ici  on stock le mdp dans mdp[] et  on affiche a l'ecran des *
			printf("* \b");
		}
	}
}
void rechhtml();
void listerhtml();
void suphtml();
void htmlajout();
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
void importer();
void mainmenu(void);
void minimenu(void);

//definier mes structure
struct livres monLivre;
struct Emp monEmp;
//fonction du criptage : on va dooner a  chaque caractere son equivalent afin de rendre le mot de pass cripte
char cryptage( char T[50])
{
   int i;
   for(i=0;i<13;i++)
   {
      if(T[i]=='a')
       T[i]='<';
      if(T[i]=='b')
        T[i]='\]';
      if(T[i]=='c')
        T[i]='�';
      if(T[i]=='d')
        T[i]='�';
      if(T[i]=='e')
        T[i]='�';
      if(T[i]=='f')
         T[i]='�';
      if(T[i]=='g')
         T[i]='�';
      if(T[i]=='h')
         T[i]='�';
      if(T[i]=='i')
         T[i]='�';

      if(T[i]=='j')
         T[i]='�';

      if(T[i]=='k')
         T[i]='�';

      if(T[i]=='l')
         T[i]='�';

      if(T[i]=='m')
         T[i]='�';

      if(T[i]=='n')
         T[i]='�';

      if(T[i]=='o')
         T[i]='�';

      if(T[i]=='p')
         T[i]='�';

      if(T[i]=='q')
         T[i]='�';

      if(T[i]=='r')
         T[i]='�';

      if(T[i]=='s')
         T[i]='�';
      if(T[i]=='t')
         T[i]='�';

      if(T[i]=='u')
         T[i]='�';
      if(T[i]=='v')
         T[i]='�';

      if(T[i]=='w')
         T[i]='�';

      if(T[i]=='x')
         T[i]='�';

      if(T[i]=='y')
         T[i]='�';

      if(T[i]=='z')
         T[i]='�';

      if(T[i]=='1')
         T[i]='�';

      if(T[i]=='2')
         T[i]='�';

      if(T[i]=='3')
         T[i]='�';

      if(T[i]=='4')
         T[i]='�';

      if(T[i]=='5')
         T[i]='�';

      if(T[i]=='6')
         T[i]='�';

      if(T[i]=='7')
         T[i]='*';

      if(T[i]=='8')
         T[i]=':';

      if(T[i]=='9')
         T[i]='!';

      if(T[i]=='0')
         T[i]='^';

       }

  return T;
}
//fonction de decriptage : on fait l'operation inverse du criptage par ex si on a cripte 'a' par '!' alors dans le decriptage on donne a '!' la valeur 'a'
char decryptage(char T[100])
{
   int i;
      for(i=0;i<100;i++)
      {
          if(T[i]=='<')
        T[i]='a';
        if(T[i]==']')
        T[i]='b';
        if(T[i]=='�')
        T[i]='c';
        if(T[i]=='�')
        T[i]='d';
        if(T[i]=='�')
        T[i]='e';
        if(T[i]=='�')
        T[i]='f';
        if(T[i]=='�')
        T[i]='g';
        if(T[i]=='�')
        T[i]='h';
        if(T[i]=='�')
        T[i]='i';
        if(T[i]=='�')
        T[i]='j';
        if(T[i]=='�')
        T[i]='k';
        if(T[i]=='�')
        T[i]='l';
        if(T[i]=='�')
        T[i]='m';
        if(T[i]=='�')
        T[i]='n';
        if(T[i]=='�')
        T[i]='o';
        if(T[i]=='�')
        T[i]='p';
        if(T[i]=='�')
        T[i]='q';
        if(T[i]=='�')
        T[i]='r';
        if(T[i]=='�')
        T[i]='s';
        if(T[i]=='�')
        T[i]='t';
        if(T[i]=='�')
        T[i]='u';
        if(T[i]=='�')
        T[i]='v';
        if(T[i]=='�')
        T[i]='w';
        if(T[i]=='�')
        T[i]='x';
        if(T[i]=='�')
        T[i]='y';
        if(T[i]=='�')
        T[i]='z';
        if(T[i]=='�')
        T[i]='1';
        if(T[i]=='�')
        T[i]='2';
        if(T[i]=='�')
        T[i]='3';
        if(T[i]=='�')
        T[i]='4';
        if(T[i]=='�')
        T[i]='5';
        if(T[i]=='�')
        T[i]='6';
        if(T[i]=='*')
        T[i]='7';
        if(T[i]==':')
        T[i]='8';
        if(T[i]=='!')
        T[i]='9';
        if(T[i]=='^')
        T[i]='0';
      }
   return T;
}


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

struct Utilisateur usr;
int login() // fonction de registrer et se connecter selon le choix d'utilisateur
{
	struct Utilisateur Utilisateur;
	char mot_de_pass2[50];
	FILE *fp;
	int choix, trouve_utilisateur = 0;
	printf("\nVeuillez entrer votre choix");
	printf("\n1.S'inscrire");
	printf("\n2.Se connecter");
	printf("\n3.Quitter");
	printf("\n\nVotre choix est :\t");
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
		cryptage(Utilisateur.mot_de_pass);//appel a la fonction criptage pour cripter mon mdp
		printf("\nConfirmer votre mot_de_pass:\t");
		recuperateur_mdp(mot_de_pass2); // appeler la fonction recuperateur_mdp pour cripter le mdp
		cryptage(mot_de_pass2);

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
		fp = fopen("Users.bin", "r"); //les utilisateurs sont stocker dans le fichiers binaires 'Users.bin'
		while (fread(&usr, sizeof(struct Utilisateur), 1, fp))
		{
			decryptage(usr.mot_de_pass);//decripter le mot de pass pour qu'on puisse se connecter
			if (!strcmp(usr.pseudo, pseudo)) // si le pesudo qu'on a saisi existe dans notre fichier
			{
				if (!strcmp(usr.mot_de_pass, mdp)) // si le mdp qu'on a saisi existe dans notre fichier on va se diriger vers le mainmenu
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
		if (!trouve_utilisateur)//si l'utilisateur n'existe pas le programme va afficher un message d'erreur
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
	printf("\n 4.Exporter un fichier Html vers un fichier Excel\n");//n'est pas demande
	printf("\n 5.Exporter un fichier Html vers un fichier text\n");//n'est pas demande
	printf("\n 6.Stocker un fichier Html dans une liste doublement châinée\n");//n'est pas demande
	printf("\n 7.Creer la page d'authentification de votre site\n");
	printf("\n 8.Creer la page d'acceuil\n");
	printf("\n 9.Gestion des liens entre les pages web\n");//sont generer automatiquement
	printf("\n 10. Quitter\n");
	printf("Entrer un choix:\n");
	switch (getch())
	{
	case '1':
		minimenu();
		break;
	case '2':
		gestionemp();
		break;
	case '3':
		importer();
		break;
	case '7':
		authentification();
		break;
	case '8':
		acceuil();
		break;
	case '9':
		gestiondeslien();
	case 'q':
		system("cls");
		exit(0);
	}
}
int lienAjout =0;
int lienSup=0;
int lienRech=0;
int lienListe=0;
gestiondeslien(){
 lienAjout =1;
 lienSup=1;
 lienRech=1;
 lienListe=1;
 htmlajout();
 suphtml();
 listerhtml();
 rechhtml();
 acceuil();
 mainmenu();
}
void importer(){
	char nomfichier[100];
	printf("\n saisir le nom du fichier:");
	fflush(stdin);
	scanf("%s",nomfichier);	
	FILE *f_in=fopen(nomfichier,"r");
	FILE *f_out=fopen("importation.html","w+");
	char *tmp=(char*)malloc(150*sizeof(char*));
	if(f_in!=NULL && f_out!=NULL){
			printf("\nvotre fichier  ete importe\n ");
		while(!feof(f_in)){
			if(fscanf(f_in,"%s",tmp)!=-1){
				fprintf(f_out,"%s",tmp);
			}
					}
	}
	fclose(f_in);
	fclose(f_out);
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
	//saisir les infos du livre
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
	// fflush(stdin);
	if (IdExisteOuNonEmp(Id_a_saisir) == 0) // appeler la fonction IdExisteOuNon pour verifier si l emprunteur est deja existe
	{
		printf("\nL emprunteur est deja existe\n");
		getch();
		mainmenu();
		return 0;
	}
	monEmp.id = Id_a_saisir;
	printf(" Nom du emprunteur:");
	scanf("%s", monEmp.nom);
	// fflush(stdin);
	printf("\n Prenom:");
	scanf("%s", monEmp.prenom);
	fflush(stdin);
	printf("\n Date d emprunte:");
	scanf("%s", monEmp.date_emprunte);
	printf("\n  id du Livre dersire:");
	scanf("%d", &monEmp.id_livre_a_emprute);
	printf("\n Date limite a rendre le livre:");
	scanf("%s", monEmp.date_limite);
	return 1;
}
void htmlajout(){
	FILE *fi = NULL;
	fi = fopen("ajouter.html", "w"); // generer un fichier ajouter.html pour l'ajout des livres
	if (fi != NULL)
	{
		fputs("<!DOCTYPE html>", fi);
		fputs("<html>", fi);
		fputs("<head>", fi);
		fputs("<meta charset=\"utf-8\">", fi);
		fputs("<title></title>", fi);
		fputs("    <link rel=\"stylesheet\" href=\"SupprimerLivre\\style.css\">", fi);
		fputs("  </head>", fi);
		fputs("<body>", fi);
		if(lienAjout==1){
			fputs("<div class=\"login-box\"><h1>Ajouter un livre</h1><div class=\"textbox\"><input type=\"text\" placeholder=\"Code du livre\"></div><div class=\"textbox\"><input type=\"text\" placeholder=\"Auteur\"></div><div class=\"textbox\"><input type=\"text\" placeholder=\"Titre de livre\"></div><div class=\"textbox\"><input type=\"password\" placeholder=\"Nombre d'exemplaire\"></div><input type=\"button\" class=\"btn\" value=\"Valider\"><a href=\"home.html\"><input type=\"button\" class=\"btn\" value=\"Page d'acceuil\"></a></div></body>", fi);
		}
		else{
			fputs("<div class=\"login-box\"><h1>Ajouter un livre</h1><div class=\"textbox\"><input type=\"text\" placeholder=\"Code du livre\"></div><div class=\"textbox\"><input type=\"text\" placeholder=\"Auteur\"></div><div class=\"textbox\"><input type=\"text\" placeholder=\"Titre de livre\"></div><div class=\"textbox\"><input type=\"password\" placeholder=\"Nombre d'exemplaire\"></div><input type=\"button\" class=\"btn\" value=\"Valider\"></div></body>", fi);
		}
		fputs("</body>", fi);
		fputs("</html>", fi);
		fclose(fi);
	}
}
void ajout_livre(void)
{
	htmlajout();
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
	fp = fopen("database.bin", "ab+");//'database.bin est un fichier pour stocker les livres
	if (getdata() == 1)//si l admin a rempli les infos du livre alors : 
	{
		monLivre.categorie = catagories[s - 1];
		fseek(fp, 0, SEEK_END);						// SEEK_END se positionnr a la fin du file
		fwrite(&monLivre, sizeof(monLivre), 1, fp); // ajouter le livre a la fin du fichier
		fclose(fp);
		printf("l'enregistrement a ete bien efffectue'");
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
	FILE *fi = NULL;
	fi = fopen("ajouterEmp.html", "w"); // generer un fichier ajouterEmp.html pour l'ajout des emprunteur
	if (fi != NULL)
	{
		fputs("<!DOCTYPE html>", fi);
		fputs("<html>", fi);
		fputs("<head>", fi);
		fputs("<meta charset=\"utf-8\">", fi);
		fputs("<title></title>", fi);
		fputs("    <link rel=\"stylesheet\" href=\"transparent login form\\style.css\">", fi);
		fputs("  </head>", fi);
		fputs("<body>", fi);
		fputs("    <div class=\"login-box\"><h1>Ajouter un Emprunteur</h1><div class=\"textbox\"><input type=\"text\" placeholder=\"Nom Emprunteur\"></div><div class=\"textbox\"><input type=\"text\" placeholder=\"Prenom Emprunteur\"></div><div class=\"textbox\"><input type=\"text\" placeholder=\"Date Emprunt\"></div><div class=\"textbox\"><input type=\"password\" placeholder=\"Livre Emprunte\"></div><input type=\"button\" class=\"btn\" value=\"Valider\"><input type=\"button\" class=\"btn\" value=\"Acceuil\"></div>", fi);
		fputs("</body>", fi);
		fputs("</html>", fi);
		fclose(fi);
	}
	system("cls");
	fpt = fopen("databaseEmp.bin", "ab+");
	if (getdataEmp() == 1)
	{
		fseek(fpt, 0, SEEK_END);				 // SEEK_END se positionnr a la fin du file
		fwrite(&monEmp, sizeof(monEmp), 1, fpt); // ajouter l emprunteur a la fin du fichier
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
void rechhtml(){
	fl = fopen("RechercherLivre.html", "w+");//creer un fichier html pour la recherche dess livres par id
	if (fl != NULL)
	{
		if(lienRech==1){
				fputs("<!DOCTYPE html><html lang=\"en\" dir=\"ltr\"><head><meta charset=\"utf-8\"><title></title><link rel=\"stylesheet\" href=\"rechercherLivre\\style.css\"> </head> <body></body><div class=\"login-box\"><h1>Rechercher un livre</h1><div class=\"textbox\"><input type=\"text\" placeholder=\"Id du livre a Rechercher\"></div><input type=\"button\" class=\"btn\" value=\"Valider\"><a href =\"home.html\"><input type=\"button\" class=\"btn\" value=\"Page Acceuil\"></a></div></body></html>", fl);	
		}
		else{
				fputs("<!DOCTYPE html><html lang=\"en\" dir=\"ltr\"><head><meta charset=\"utf-8\"><title></title><link rel=\"stylesheet\" href=\"rechercherLivre\\style.css\"> </head> <body></body><div class=\"login-box\"><h1>Rechercher un livre</h1><div class=\"textbox\"><input type=\"text\" placeholder=\"Id du livre a Rechercher\"></div><input type=\"button\" class=\"btn\" value=\"Valider\"></div></body></html>", fl);
		}
		fclose(fl);
	}
}
void RechercherLivre()
{
	rechhtml();
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
			if (monLivre.id == Id_a_chercher) // si l'Id a rechercher existe dans le fichier il va afficher les infos de ce livre a l'ecran
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
void RechercherEmp()
{
	fl = fopen("RechercherEmp.html", "w+");
	if (fl != NULL)
	{
		fputs("<div class=\"login-box\"><h1>Rechercher un Emprunteur</h1><div class=\"textbox\"><input type=\"text\" placeholder=\"Id du Emprunteur a Rechercher\"></div><input type=\"button\" class=\"btn\" value=\"Valider\"><a href =\"home.html\"><input type=\"button\" class=\"btn\" value=\"Page Acceuil\"></a></div>", fl);
		fclose(fl);
	}
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
			if (monEmp.id == Id_a_chercher) // si l'Id a rechercher existe dans le fichier il va afficher les infos de cet emprunteur a l'ecran
			{
				printf("\nL emprunteur est disponible");
				printf("\nID:%d", monEmp.id);
				printf("\nnom:%s", monEmp.nom);
				printf("\nPrenom:%s ", monEmp.prenom);
				printf("\nLa date d emprunte:%s ", monEmp.date_emprunte);
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
			mainmenu();//revenir au menu principale
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
void suphtml(){
	fl = fopen("supprimerLivre.html", "w+");//generer la page du suppression des livre
	if (fl != NULL)
	{
		if(lienSup==1){
			fputs("<!DOCTYPE html><html lang=\"en\" dir=\"ltr\"><head><meta charset=\"utf-8\"><title></title><link rel=\"stylesheet\" href=\"SupprimerLivre\\style.css\"></head><body><div class=\"login-box\"><h1>Supprimer un livre</h1><div class=\"textbox\"><input type=\"text\" placeholder=\"Id du livre a supprimer\"></div><input type=\"button\" class=\"btn\" value=\"Valider\"><a href=\"home.html\"><input type=\"button\" class=\"btn\" value=\"Page Acceuil\"></a></div></body></html>", fl);
		}
		else{
			fputs("<!DOCTYPE html><html lang=\"en\" dir=\"ltr\"><head><meta charset=\"utf-8\"><title></title><link rel=\"stylesheet\" href=\"SupprimerLivre\\style.css\"></head><body><div class=\"login-box\"><h1>Supprimer un livre</h1><div class=\"textbox\"><input type=\"text\" placeholder=\"Id du livre a supprimer\"></div><input type=\"button\" class=\"btn\" value=\"Valider\"></div></body></html>", fl);
		}
		
		fclose(fl);
	}
}
void SuppressionLivre()
{
	suphtml();
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
			if (monLivre.id == Id_a_supprimer)//verifier si le livre d abord existe ou non pour le supprimer
			{
				VerifierSiLivreExiste = 't';//si le livre existe VerifierSiLivreExiste recoit 't' 
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
			printf("Etes vous sur de supprimer ce livre?(Y/N):"); // confirmation de suppression et supprimer le livre par la methode classique cad copier tous le fichier dans un nouveau fichier sauf le livre a supprimer puis renomer le nouveau fichier et supprimer l'ancien 
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
				remove("database.bin");				// supprimer le fichier
				rename("temp.bin", "database.bin"); // renomer le fichier par le nom de l'ancien fichier
				if (VerifierSiLivreExiste == 't')
				{
					printf("\nLe livre a ete supprimer");
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
	//creation du fichier html de suppression des emprunteurs
	fl = fopen("supprimerEmp.html", "w+");
	if (fl != NULL)
	{
		fputs("<div class=\"login-box\"><h1>Supprimer un Emprunteur</h1><div class=\"textbox\"><input type=\"text\" placeholder=\"Id du Emprunteur a supprimer\"><input type=\"button\" class=\"btn\" value=\"Valider\"></div><a href =\"home.html\"><input type=\"button\" class=\"btn\" value=\"Page Acceuil\"></a>", fl);
		fclose(fl);
	}
	system("cls");
	int Id_a_supprimer;
	char SupprimerEncors = 'o';

	while (SupprimerEncors == 'o')
	{
		system("cls");
		printf("\nEntrer eprunteur a supprimer:");
		scanf("%d", &Id_a_supprimer);
		FILE *fp;
		fp = fopen("databaseEmp.bin", "rb+"); // ouvrir le fichier pour chercher l emprunteur a supprimer dans le fichier de stockage databaseEmp
		rewind(fp);
		while (fread(&monEmp, sizeof(monEmp), 1, fp) == 1)
		{
			if (monEmp.id == Id_a_supprimer)//verifier si le l emprunteur existe deja
			{
				VerifierSiEmpExiste = 's';
			}
		}
		if (VerifierSiEmpExiste != 's')
		{
			printf("\nCe emp n'existe pas");
			if (getch())
				mainmenu();
		}
		fclose(fp);
		if (VerifierSiEmpExiste == 's')
		{
			printf("Etes vous sur de supprimer cet emp?(O/N):"); // confirmation de suppression
			if (getch() != 'n')
			{
				FILE *ft = NULL;
				fp = fopen("databaseEmp.bin", "rb+");
				ft = fopen("temp.bin", "wb+");
				rewind(fp);
				while (fread(&monEmp, sizeof(monEmp), 1, fp) == 1)
				{
					if (monEmp.id != Id_a_supprimer)
					{
						fseek(ft, 0, SEEK_CUR);					//  se postionner a la position courante du fichier
						fwrite(&monEmp, sizeof(monEmp), 1, ft); // copier tous les emprunteurs sauf celui a supprimer dans un nouveau fichier
					}
				}
				fclose(ft);
				fclose(fp);
				remove("databaseEmp.bin");			   // supprimer le fichier
				rename("temp.bin", "databaseEmp.bin"); // renomer le fichier par le nom de l'ancien fichier
				if (VerifierSiEmpExiste == 's')
				{
					printf("\nL emprunteur a ete supprimer");
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
void listerhtml(){
	system("cls");
	FILE *fl = NULL;
	fl = fopen("Lister les livres.html", "w+");//creation d une page web dynamique qui a chaque ajout du livre va l afficher automatiquement sans changer du code html 
	if (fl != NULL)
	{
		fputs("<!DOCTYPE html>", fl);
		fputs("<html>", fl);
		fputs("<head>", fl);
		fputs("    <link rel=\"stylesheet\" href=\"style1.css\">", fl);
		fputs("</head>", fl);
		fputs("<body>", fl);
		fputs("<h1>Liste de tous les livres</h1>", fl);
		if(lienListe==1){
				fputs("<a href=\"home.html\">Acceuil</a><br><br>", fl);
		}
		
		fputs("<table class=\"table-style\"><thead><tr><td>Categorie:</td><td>Code du livre:</td><td>Auteur du livre:</td><td>Titre du livre</td><td>Nombre d'examplaire:</td></tr></thead>", fl);
		fputs("<tbody>", fl);
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
			l = l + monLivre.nombre_examplaire; // l calcule le nombre total des livre
		}
		fputs("</tbody>", fl);
		fputs("</table>", fl);
		fputs("</body>", fl);
		fputs("</html>", fl);
		fclose(fl);
		fclose(fp);
	}
}
void Liste_des_livres(void)
{
	int i = 0;
	listerhtml();
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
		i = i + monLivre.nombre_examplaire;
	}
	printf("\nLe nombre total des livres =%d\n", i);
	fclose(fp);
	returnfunc();
}
void Liste_des_emps(void)
{
	system("cls");
	FILE *fl = NULL;
	fl = fopen("ListerEmp.html", "w+");//creation d une page web dynamique qui a chaque ajout du emprunteur va l afficher automatiquement sans changer du code html
	if (fl != NULL)
	{
		fputs("<!DOCTYPE html>", fl);
		fputs("<html>", fl);
		fputs("<head>", fl);
		fputs("    <link rel=\"stylesheet\" href=\"style1.css\">", fl);
		fputs("</head>", fl);
		fputs("<body>", fl);
		fputs("<h1>Liste les emprunteur</h1>", fl);
		fputs("<a href=\"home.html\">Acceuil</a><br><br>", fl);
		fputs("<table class=\"table-style\"><thead><tr><td>Code du emprunteur:</td><td>nom:</td><td>prenom:</td><td>Date d emprunte:</td><td>Date limite du rendement:</td><td>Id du livre emprunte</td></tr></thead>", fl);
		fp = fopen("databaseEmp.bin", "rb");
		fputs("<tbody>", fl);
		while (fread(&monEmp, sizeof(monEmp), 1, fp) == 1)
		{
			fputs("<tr>", fl);
			fprintf(fl, "<td>%d</td>", monEmp.id);
			fprintf(fl, "<td>%s</td>", monEmp.nom);
			fprintf(fl, "<td>%s</td>", monEmp.prenom);
			fprintf(fl, "<td>%s</td>", monEmp.date_emprunte);
			fprintf(fl, "<td>%s</td>", monEmp.date_limite);
			fprintf(fl, "<td>%d</td>", monEmp.id_livre_a_emprute);
			fputs("</tr>", fl);
			fputs("\n\n", fl);
		}
		fputs("</tbody>", fl);
		fputs("</table>", fl);
		fputs("</body>", fl);
		fputs("</html>", fl);
		fclose(fl);
		fclose(fp);
	}
	printf("                              Liste des emprunteur                                   \n\n");
	printf("Id        Nom:              Prenom:              Date emprunte:         Date de rendement limite:         id du livre emprunte:\n\n");
	fp = fopen("databaseEmp.bin", "rb");

	while (fread(&monEmp, sizeof(monEmp), 1, fp) == 1)
	{
		printf("%d", monEmp.id);
		printf("\t   %s", monEmp.nom);
		printf("\t\t%s", monEmp.prenom);
		printf("\t\t   %s", monEmp.date_emprunte);
		printf("\t\t\t  %s", monEmp.date_limite);
		printf("\t\t\t\t %d", monEmp.id_livre_a_emprute);

		printf("\n\n");
	}
	fclose(fp);
	returnfunc();
}
void returnfunc(void)//fonctionne pour revenir au menu principale
{
	printf("Cliquer sur ENTRER pour revenir au menu principal");
	if (getch() == 13) // ENTRE a pour ascii 13
		mainmenu();
	else
		printf("\n");
	returnfunc();
}
void acceuil()//ceatio de la page d'acceuil
{
	FILE *fa = NULL;
	fa = fopen("home.html", "w"); // generer un fichier ajouter.html pour l'ajout des livres
	if (fa != NULL)
	{
		fputs("<!DOCTYPE html>", fa);
		fputs("<html>", fa);
		fputs("<head>", fa);
		fputs("<meta charset=\"UTF-8\"><meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><title>Espace administration</title>    <link rel=\"stylesheet\" href=\"home\\styles.css\"><link rel=\"stylesheet\" href=\"https://cdnjs.cloudflare.com/ajax/libs/font-awesome/5.15.3/css/all.min.css\" integrity=\"sha512-iBBXm8fW90+nuLcSKlbmrPcLa0OT92xO1BIsZ+ywDWZCvqsWgccV3gFoRBv0z+8dLJgyAHIhR35VZc2oM/gI1w==\" crossorigin=\"anonymous\" referrerpolicy=\"no-referrer\" />", fa);
		fputs("</head>", fa);
		fputs("<body>", fa);
		fputs("    <div class=\"hero\"><nav><img src=\"home/images/téléchargement.png\" class=\"logo\"><ul>", fa);
		if(lienAjout==1)	{
			fputs(" <li><a href=\"ajouter.html\">Ajouter un livre</a></li>", fa);
		}
		
		if(lienSup==1){
			fputs(" <li><a href=\"supprimerLivre.html\">Supprimer un livre</a></li>", fa);
		}
		
		if(lienListe==1){
				fputs(" <li><a href=\"Lister les livres.html\">Lister un livre</a></li>", fa);
		}
		
		if(lienRech==1){
				fputs(" <li><a href=\"RechercherLivre.html\">Rechercher un livre</a></li>", fa);
		}	
		
		fputs(" </ul></nav><div class=\"detel\"><h1>Bienvenue dans l'espace administration!</h1></div><div class=\"images\"><img src=\"home/images/shape.png\" class=\"shape\"><img src=\"home/images/pic.jpg\" class=\"lib\"></div></div>", fa);
		fputs("</div>", fa);
		fputs("</body>", fa);
		fputs("</html>", fa);
		fclose(fa);
	}
	mainmenu();
}
void authentification()//creation de la page d'authentificaton
{
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
