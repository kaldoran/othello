// -------------------------------------------------------- 
// AUTEUR : REYNAUD Nicolas                                |
// FICHIER : global.c                          		    |
// DATE : 13/03/14                                         |
//                                                         |
// - Définition des fonctions de global.h                  |
// -------------------------------------------------------- 


#include <stdio.h>
#include <stdlib.h>

#include "global.h"

/* Fait un CTRL + L pour néttoyer l'ecran */
void _clean() {
	system("clear");
}

/* Reinitialise l'écran */
void _reset_term() {
	system("reset");
}

/* Vide le buffer */
void videbuffer() {
  char videbuffer = 'a';
  while( (videbuffer = getchar()) != '\0' && videbuffer != '\n'); // on vide le buffer

}

/* Fait une pause et attend Entrée pour continuer */
void do_pause() {

	printf("Appuyer sur entrée pour continuer...");
 	getchar();

}

