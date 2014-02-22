#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "othello.h"

/* Verifie seulement si le coup est possible
 */
#define check_only(OTHELLO, POSITION, PLAYER)          \
                good_move(OTHELLO, POSITION, PLAYER, 0)
                
/* Verifie si le coup est correct et retournes les pions 
 */
#define check_and_return(OTHELLO, POSITION, PLAYER)    \
                good_move(OTHELLO, POSITION, PLAYER, 1)

Othello *new_othello() {

	Othello *othello;
	int mid = 0, val = 0;
	
	if ((othello = calloc(1, sizeof *othello)) == NULL)
		QUIT_MSG("Erreur : Probleme d'allocation de la structure de l'othello");

	/* Initialisation */
	othello->nb_pawn_p1 = othello->nb_pawn_p2 = 2;
	memset(othello->grid, 0, sizeof *othello); 

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
void videbuffer() {
  char videbuffer = 'a';
  while( (videbuffer=getchar()) != '\0' && videbuffer != '\n'); // on vide le buffer
}

/* Récupere le coup sur STDIN
 * Et verifi simplement que le coup est dans la grille 
 */
int othello_ask_choice(Othello *othello, char player) {
	int column = 0;
	char row = ' ';
	
	printf("%c ou voulez vous jouer ? ", player);
	while(1) {

		scanf("%c%d",&row, &column);
		DEBUG_PRINTF("%c %d\n", row, column);
		if ( (( row >= 'A' && row < 'A' + W_SIDE ) || ( row >= 'a' && row < 'a' + W_SIDE )) && column > 0 && column <= W_SIDE ) {
			row = toupper(row) - 'A';
			--column;
			DEBUG_PRINTF("Value : %d %d - %d\n", (int)row, column, SQUARE((int)row, column));
			printf("Move Ok ? %d\n", check_only(othello, SQUARE((int)row, column), player) );
		}
		
		printf("Erreur : Entrez un nouveau coup : ");
		videbuffer();
	}
	return 1;
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
int good_move(Othello *othello, int position, char player, int return_or_not) {
	
	int i;
	char inv_player = SWITCH_PLAYER(player);
	DEBUG_PRINTF("%d %c\n" , position, player);
	/* Horizontal en partant sur la gauche */
	if ( othello->grid[position - 1] == inv_player ) { /* Si la case juste a coté est un pion enemi, on part a l'avanture */
		for( i = position - 1; i % W_SIDE != 0 && othello->grid[i] == inv_player; i--) 
			; 
		if ( othello->grid[i] == player ) return 1; 	
	}
	
	
	return 0;
}

int move_left (Othello *othello, char player ) {

	int column, line;
	
	if ( othello->nb_pawn_p1 + othello->nb_pawn_p1 == GRID_SIZE ) 
		return 0;
		
	for ( column = 0; column < W_SIDE; column++) 
		for ( line = 0; line < W_SIDE; line++) 
			return check_only(othello, SQUARE(line, column),player);
			
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

