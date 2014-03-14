//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : affiche.h                                      |
// DATE : 13/03/14                                          |
//                                                          |
// - Prototypes des fonctions de global.c                   |
// - Défini tout les parametres du jeu                      |
// - Fonction de reset du terminal                          |
// - Fonction pour nettoyer le terminal                     |
// - Fonction pour vider le buffer                          |
// - Fonction pour faire une pause pendant le jeu           |
//   (Attendre la touche entrer pour continuer)             |
//----------------------------------------------------------


#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Définition des tailles de la grille */
#define W_SIDE 8
#define GRID_SIZE (W_SIDE * W_SIDE)

/* Définition des pions */
#define PAWN_J1 'X'
#define PAWN_J2 'O'

/* Permet d'obtenir la position d'un pion
* Converti un couple ROW, COLUMN en une case
*/
#define SQUARE(ROW, COLUMN) (ROW + W_SIDE * COLUMN)


#define ROW(SQUARE) (SQUARE / W_SIDE + 1)
#define COLUMN(SQUARE) ( SQUARE % W_SIDE + 'A' )
/* Inverse les joueur */
#define SWITCH_PLAYER(PLAYER) ((PLAYER == PAWN_J1) ? PAWN_J2 : PAWN_J1)

/* Affiche le message MSG
* Et les arguments [ possibilité de ne pas en mettre ]
* Puis quitte le programme
*/
#define QUIT_MSG(MSG, ...)                      \
do {                                            \
	fprintf(stderr, MSG, ## __VA_ARGS__);       \
	exit(EXIT_FAILURE);                         \
}while(0);

/* Si le mode debug est activé a la compilation
* Se flags est crée et la fonction DEBUG_PRINT affiche le message MSG et ses arguments hypothétique
*/
#ifdef DEBUG
	#define DEBUG_PRINTF(MSG, ...)                                                                                                               \
		do {                                                                                                                                     \
			fprintf(stderr, "File : %s - Line : %d - Function : %s() : " MSG, __FILE__, __LINE__, __func__, ## __VA_ARGS__);                     \
		} while(0);
#else
	#define DEBUG_PRINTF(MSG, ...)
#endif

void _clean();

void _reset_term();

void videbuffer();

void do_pause();

#endif /* GLOBAL_H inclu */


