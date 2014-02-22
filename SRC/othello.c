#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "othello.h"

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

/* Verifira si effectivement le coup est possible 
 */	
int check_choice(Othello *othello, int position, char player) {
	if ( position - 1 > GRID_SIZE )
		return 0;
	return 1;
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
			DEBUG_PRINTF("Value : %d %d - %d\n", (int)row, column, SQUARE(column, (int)row));
			check_choice(othello, SQUARE((int)row ,column), player);
			printf("Ok");
		}
		
		printf("Erreur : Entrez un nouveau coup : ");
		videbuffer();
	}
	return 1;
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

	for (i = 0; i < W_SIDE; i++) {
		printf("%d |", i + 1);
		for(j = 0; j < W_SIDE; j++) {
			if( (lettre = othello->grid[SQUARE(i,j)]) == PAWN_J1) printf("\033[30m %c \033[0m|", lettre);
			else printf(" %c |", (lettre == PAWN_J2) ? lettre : lettre + 32 ); /* Lettre + 32 car 32 est le code ascii de l'espace */
		}
		print_ligne();
	}
	
	printf("\n    Score \033[30mX\033[0m : %u   Score O : %u\n",othello->nb_pawn_p1, othello->nb_pawn_p2);
 
	return;
}

