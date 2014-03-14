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

/* Merci a Ronan Abhamon pour son aide précieuse pour cette fonction */
char * startWith(char *s1, char *s2) {

	for ( ; *s1 == *s2; s1++, s2++)
		if (*s1 == '\0')
			return s2;

	if (*s1 == '\0')
		return s2;
	return NULL;
}

Configuration *nouvelle_configuration() {
	Configuration *config;
	if ((config = calloc(1, sizeof *config)) == NULL)
		QUIT_MSG("Erreur : Probleme d'allocation de la structure de la configuration");
	
	return config;
}

void charger_configuration(Configuration *config) {
	char *ret;
	char ligne_lue[TAILLE_LIGNE];
	
	FILE* fichier = fopen(ADRESSE_CONFIG, "r");
	while(fgets(ligne_lue, TAILLE_LIGNE, fichier) != NULL){
		if ( strchr (ligne_lue, '#') == NULL ) { /* On vire les commentaires */

			if ( (ret = startWith("Pseudo:",ligne_lue)) != NULL ) /* Si la ligne commence par */
				strcpy(config->pseudo, ret);

			if ( (ret = startWith("Ip:",ligne_lue)) != NULL ) /* Si la ligne commence par */
				config->ip = (in_addr_t)atoi(ret);
					
			if ( (ret = startWith("Port:",ligne_lue)) != NULL) /* Si la ligne commence par */
				config->port = (in_port_t)atoi(ret);
		}
	}

	printf("Config : %s", config->pseudo);
	fclose(fichier);
	
	return;
}


