// -------------------------------------------------------- 
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : gestion_fichier.c                              |
// DATE : 13/03/14                                          |
//                                                          |
// - Définition des fonctions de gestion_fichier.h          |
// - pour plus de detail C.F gestion_fichier.h              |
// -------------------------------------------------------- 


#include "gestion_fichier.h"

void afficher_regles() {                         
	char caractereActuel = 'z';
	FILE* fichier = fopen(ADRESSE_REGLES, "r");
	caractereActuel = fgetc(fichier);

	while(caractereActuel != EOF) {
		printf("%c",caractereActuel);
		caractereActuel = fgetc(fichier);
	}
	
	fclose(fichier);
	return;
}
