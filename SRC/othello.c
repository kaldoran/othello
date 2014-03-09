#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "othello.h"
#include "time.h"

Othello *new_othello() {

	Othello *othello;
	int mid = 0, val = 0;

	if ((othello = calloc(1, sizeof *othello)) == NULL)
		QUIT_MSG("Erreur : Probleme d'allocation de la structure de l'othello");
		
	if((othello->grid = calloc(GRID_SIZE, sizeof(char))) == NULL) {
		free(othello);
		QUIT_MSG("Erreur : Probleme d'allocation du tableau de l'othello");
	}
	
	/* Initialisation */
	othello->nb_pawn_p1 = othello->nb_pawn_p2 = 2;

	/* Calcul du milieu de grille */
	val = W_SIDE / 2 - 1;
	mid = SQUARE(val, val);

	/* Positionnement des pions de bases */
	
	othello->grid[mid] = PAWN_J2;
	othello->grid[mid + 1] = PAWN_J1;

	mid += W_SIDE;
	othello->grid[mid] = PAWN_J1;
	othello->grid[mid + 1] = PAWN_J2;

	return othello;
}

/* Vide le buffer
 * a deplacer dans un fichier global
 */
int videbuffer() {
  char videbuffer = 'a';
  while( (videbuffer = getchar()) != '\0' && videbuffer != '\n'); // on vide le buffer
  return 1;
}

/* Récupere le coup sur STDIN
 * Et verifi simplement que le coup est dans la grille 
 */
int othello_ask_choice(Othello *othello, char player) {
	int column = 0;
	char row = ' ';
	if ( ! move_left(othello, player) ) 
		return 0;
	
	printf("%c ou voulez vous jouer ? ", player);
	while(1) {

		scanf("%c%d",&row, &column);
		DEBUG_PRINTF("%c %d\n", row, column);
		if ( (( row >= 'A' && row < 'A' + W_SIDE ) || ( row >= 'a' && row < 'a' + W_SIDE )) && column > 0 && column <= W_SIDE ) {
			row = toupper(row) - 'A';
			--column;

			if ( good_move(othello, SQUARE((int)row, column), player) ) {
				change_value(othello, SQUARE((int)row, column), player);
				videbuffer();
				return 1;
			}
		}
		
		printf("Erreur : Entrez un nouveau coup : ");
		videbuffer();
	}
	return 1;
}

/* change le pion, */
void do_calc(Othello *othello, int position, char player) {
	othello->grid[position] = player;
	(player == 'X') ? othello->nb_pawn_p1++ : othello->nb_pawn_p2++;
	(player == 'O') ? othello->nb_pawn_p1-- : othello->nb_pawn_p2--;
	
	return;
}

/* Change la grille */
void change_value(Othello *othello, int position, char player) {
	/* Pourquoi faire une double boucle ?
	 *	- car dans cette fonction on verifi TOUT les chemins
	 *	Il faut donc etre sur que le chemin que l'on test contient un pio ennemie
	 *	Pour cause, si il y en a pas alors la boucle s'arretera uniquement sur le bord [ en ajoutant des pions sur la grille au passage ]
	 */
	int i = position;
	char inv_player = SWITCH_PLAYER(player);
	
	othello->grid[i] = player;
	(player == 'X') ? othello->nb_pawn_p1++ : othello->nb_pawn_p2++;
	/* Horizontal en partant sur la gauche */	
	if ( i % W_SIDE != 0 ) { /* Si la case a gauche est enemi, on part a l'avanture */
		for( --i; i % W_SIDE != 0 && othello->grid[i] == inv_player; i--) 
			; 
		if ( othello->grid[i] == player ) 
			for( ++i; othello->grid[i] == inv_player ; i++) 
				do_calc(othello, i, player);
	}

	/* Horizontal en partant vers la droite */
	if ( (i = position) % W_SIDE != 7 ) { /* Si la case a droite est enemi, on part a l'avanture */
		for(++i ; i % W_SIDE != 7 && othello->grid[i] == inv_player; i++) 
			; 
		if ( othello->grid[i] == player ) 
			for( --i ; othello->grid[i] == inv_player; i--) 
				do_calc(othello, i, player);
	}
	
	/* Vertical en partant vers le haut */

	if ( (i = position) > W_SIDE ) {
		for(i -= W_SIDE; i > 0 && othello->grid[i] == inv_player; i -= W_SIDE) 
			; 
		if ( othello->grid[i] == player ) 
			for( i += W_SIDE; othello->grid[i] == inv_player; i += W_SIDE) 
				do_calc(othello, i, player);
	}

	/* Vertical en partant vers le bas */
	if ( (i = position) < SQUARE(0, (W_SIDE - 1)) ) {
		for(i += W_SIDE; i < GRID_SIZE && othello->grid[i] == inv_player; i += W_SIDE) 
			; 
		if ( othello->grid[i] == player )
			for( i -= W_SIDE; othello->grid[i] == inv_player; i -= W_SIDE) 
				do_calc(othello, i, player);
	}

	/* Diagonale en partant vers bas droite */
	if ( (i = position) < SQUARE(0, (W_SIDE - 1)) && i % W_SIDE != 7 ) {
		for(i += W_SIDE + 1; i < GRID_SIZE && i % W_SIDE != 7 && othello->grid[i] == inv_player; i += W_SIDE + 1) 
			; 
		if ( othello->grid[i] == player ) 
			for( i -= (W_SIDE + 1); othello->grid[i] == inv_player; i -= (W_SIDE + 1) ) 
				do_calc(othello, i, player);
	}

	/* Diagonale en partant vers bas gauche */
	if ( (i = position) < SQUARE(0, (W_SIDE - 1)) && i % W_SIDE != 0 ) {
		for(i += W_SIDE - 1; i < GRID_SIZE && othello->grid[i] == inv_player; i += W_SIDE - 1) 
			; 
		if ( othello->grid[i] == player ) 
			for( i -= W_SIDE - 1; othello->grid[i] == inv_player; i -= W_SIDE - 1) 
				do_calc(othello, i, player);	
	}

	/* Diagonale en partant vers haut droite */
	if ( (i = position) > W_SIDE && i % W_SIDE != 7 ) {
		for(i -= (W_SIDE + 1); i < GRID_SIZE && othello->grid[i] == inv_player; i -= (W_SIDE + 1)) 
			; 
		if ( othello->grid[i] == player ) 
			for( i += W_SIDE + 1; othello->grid[i] == inv_player; i += W_SIDE + 1) 
				do_calc(othello, i, player);	
	}

	/* Diagonale en partant vers haut gauche */
	if ( (i = position) > W_SIDE && i % W_SIDE != 0) {
		for(i -= (W_SIDE - 1); i < GRID_SIZE && othello->grid[i] == inv_player; i -= (W_SIDE - 1)) 
			; 
		if ( othello->grid[i] == player ) 
			for( i += W_SIDE - 1; othello->grid[i] == inv_player; i += W_SIDE - 1) 
				do_calc(othello, i, player);	
	}
	
	return;
}

/* Verifie si le coup est correct si return_or_not == 0
 * I.E : Verifi si il trouve un pion enemie autour du pion qui vas etre jouer
 * 			- Si un pion est trouvé on verifie toute la ligne
 *			  Si un pion enemie est trouvé sur cette ligne on retourne 1
 *			  Sinon on retourne 0
 * Si return_or_not == 1
 * 		Meme action que pour return_or_not == 0
 *		Cependant au lieu de s'arreter en fin de ligne des qu'il rencontre un pion enemie
 *		on fait demi tour en inversant les pions
 *		Et on ne s'arretepas au premier coup trouvé 
 */
int good_move(Othello *othello, int position, char player) {
	
	int i;
	char inv_player = SWITCH_PLAYER(player);
	
	/* En verifiant le coup ça devrait aller mieu */
	if (othello->grid[position] != 0 ) 
		return 0;
	
	/* Horizontal en partant sur la gauche */	
	if ( (i = position) % W_SIDE != 0 && othello->grid[--i] == inv_player ) { /* Si la case a gauche est enemi, on part a l'avanture */
		for( ; i % W_SIDE != 0 && othello->grid[i] == inv_player; i--) 
			; 
		if ( othello->grid[i] == player )
			return 1;
	}

	/* Horizontal en partant vers la droite */
	if ( (i = position) % W_SIDE != 7 && othello->grid[++i] == inv_player ) { /* Si la case a droite est enemi, on part a l'avanture */
		for(; i % W_SIDE != 7 && othello->grid[i] == inv_player; i++) 
			; 
		if ( othello->grid[i] == player )
			return 1; 

	}
	
	/* Vertical en partant vers le haut */

	if ( (i = position) > W_SIDE && othello->grid[i -= W_SIDE ] == inv_player ) {
		for(; i > 0 && othello->grid[i] == inv_player; i -= W_SIDE) 
			; 
		if ( othello->grid[i] == player )
			return 1;
	}

	/* Vertical en partant vers le bas */
	if ( (i = position) < SQUARE(0, (W_SIDE - 1)) && othello->grid[i += W_SIDE] == inv_player ) {
		for(; i < GRID_SIZE && othello->grid[i] == inv_player; i += W_SIDE) 
			; 
		if ( othello->grid[i] == player ) 
			return 1;	
	}

	/* Diagonale 
	 * Dans cette partie je vais gérer les coups en diagonales
	 	- Diagonale de la position vers bas droite
	 	- Diagonale de la position vers bas gauche
	 	- Diagonale de la position vers haut droite
	 	- Diagonale de la position vers haut gauche*/

	/* Diagonale en partant vers bas droite */
	if ( (i = position) < SQUARE(0, (W_SIDE - 1)) && i % W_SIDE != 7 && othello->grid[i += W_SIDE + 1] == inv_player ) {
		for(; i < GRID_SIZE && i % W_SIDE != 7 && othello->grid[i] == inv_player; i += W_SIDE + 1) 
			; 
		if ( othello->grid[i] == player ) 
			return 1;	
	}

	/* Diagonale en partant vers bas gauche */
	if ( (i = position) < SQUARE(0, (W_SIDE - 1)) && i % W_SIDE != 0 && othello->grid[i += W_SIDE - 1] == inv_player ) {
		for(; i < GRID_SIZE && othello->grid[i] == inv_player; i += W_SIDE - 1) 
			; 
		if ( othello->grid[i] == player ) 
			return 1;	
	}

	/* Diagonale en partant vers haut droite */
	if ( (i = position) > W_SIDE && i % W_SIDE != 7 && othello->grid[i -= (W_SIDE + 1)] == inv_player ) {
		for(; i < GRID_SIZE && othello->grid[i] == inv_player; i -= (W_SIDE + 1)) 
			; 
		if ( othello->grid[i] == player ) 
			return 1;	
	}

	/* Diagonale en partant vers haut gauche */
	if ( (i = position) > W_SIDE && i % W_SIDE != 0 && othello->grid[i -= (W_SIDE - 1)] == inv_player ) {
		for(; i < GRID_SIZE && othello->grid[i] == inv_player; i -= (W_SIDE - 1) ) 
			; 
		if ( othello->grid[i] == player ) 
			return 1;	
	}
	
	return 0;
}

int hasard(int max) { // fonction hassard , donne un nombre compris entre 0 et max de facon aléatoire.
  return (int)  ((float) rand() / RAND_MAX * max );
}

void move_IA (Othello *othello, char player ) {

	int i,nb_coup_possible = 0;
	int *coup_possible = NULL;
	int * tmp;
	
	if((coup_possible = calloc(nb_coup_possible, sizeof(int))) == NULL)
		QUIT_MSG("Erreur : Probleme d'allocation du tableau de l'IA\n");

	for ( i = 0; i < GRID_SIZE; i++ ) 
		if ( good_move(othello, i, player) ) {
			if ( (tmp = realloc (coup_possible, ++nb_coup_possible * sizeof(int)) ) == NULL ) 
				QUIT_MSG("Erreur : Probleme d'Re-allocation du tableau de l'IA\n");
				
			coup_possible = tmp;
			printf("Move REAL: %c %d - %d\n", COLUMN(i) ,ROW(i), i);
			coup_possible[nb_coup_possible - 1] = i;
		}
	
	if ( nb_coup_possible > 0) {
		nb_coup_possible = coup_possible[hasard(nb_coup_possible)];
		free(coup_possible);

		printf("je vais jouer en %c %d - %d\n",  COLUMN(nb_coup_possible) ,ROW(nb_coup_possible), nb_coup_possible);
		change_value(othello, nb_coup_possible, player);
	}
	else 
		printf("Je suis bloquée :'( \n");
		

	return;
}

int move_left (Othello *othello, char player ) {

	int i;
	
	if ( othello->nb_pawn_p1 + othello->nb_pawn_p2 == GRID_SIZE ) 
		return 0;
		
	for ( i = 0; i < GRID_SIZE; i++ ) 
		if ( good_move(othello, i,player) ) 
				return 1;
		
	return 0; /* Normalement jamais atteind , c'est juste pour faire plaisir a GCC */
}

/* Mettre dans un fichier "affichage"
 */
void print_ligne() {
	int i ;
	printf("\n  +");
	for (i = 0; i < W_SIDE; i++) { printf("---+"); }
	printf("\n");
}

/* Mettre dans affichage 
 * affiche la grille d'othello
 */
void print_othello(Othello *othello) {
	int i,j;
	char lettre = 'A'; 
	printf("  ");
	
	for (i = 0; i < W_SIDE; i++) { /* Affiche les lettres de A à Z sur l'axe Horizontale */
        	printf ("  %c ", lettre);
        	lettre++;
    	} 
    	
	print_ligne();

	for (j = 0; j < W_SIDE; j++) {
		printf("%d |", j + 1);
		for(i = 0; i < W_SIDE; i++) {
			if( (lettre = othello->grid[SQUARE(i,j)]) == PAWN_J1) printf("\033[30m %c \033[0m|", lettre);
			else printf(" %c |", (lettre == PAWN_J2) ? lettre : lettre + 32 ); /* Lettre + 32 car 32 est le code ascii de l'espace */
		}
		print_ligne();
	}
	
	printf("\n    Score \033[30mX\033[0m : %u   Score O : %u\n",othello->nb_pawn_p1, othello->nb_pawn_p2);
 
	return;
}


