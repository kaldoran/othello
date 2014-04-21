#include <string.h>
#include <ctype.h>
#include "global.h"
#include "othello.h"
#include "time.h"

#define COLOR  "\033[32m"
#define NCOLOR "\033[0m"

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

		scanf("%1c%1d",&row, &column);
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

	if ( (i = position) > SQUARE((W_SIDE - 1), 0) ) {
		for(i -= W_SIDE; i > SQUARE((W_SIDE - 1), 0) && othello->grid[i] == inv_player; i -= W_SIDE) 
			; 
		if ( othello->grid[i] == player ) 
			for( i += W_SIDE; othello->grid[i] == inv_player; i += W_SIDE) 
				do_calc(othello, i, player);
	}

	/* Vertical en partant vers le bas */
	if ( (i = position) < SQUARE(0, (W_SIDE - 1)) ) {
		for(i += W_SIDE; i < SQUARE(0, (W_SIDE - 1)) && othello->grid[i] == inv_player; i += W_SIDE) 
			; 
		if ( othello->grid[i] == player )
			for( i -= W_SIDE; othello->grid[i] == inv_player; i -= W_SIDE) 
				do_calc(othello, i, player);
	}

	/* Diagonale en partant vers bas droite */
	if ( (i = position) < SQUARE(0, (W_SIDE - 1)) && i % W_SIDE != 7 ) {
		for(i += W_SIDE + 1; i < SQUARE(0, (W_SIDE - 1)) && i % W_SIDE != 7 && othello->grid[i] == inv_player; i += W_SIDE + 1) 
			; 
		if ( othello->grid[i] == player ) 
			for( i -= W_SIDE + 1; othello->grid[i] == inv_player; i -= W_SIDE + 1 ) 
				do_calc(othello, i, player);
	}

	/* Diagonale en partant vers bas gauche */
	if ( (i = position) < SQUARE(0, (W_SIDE - 1)) && i % W_SIDE != 0 ) {
		for(i += W_SIDE - 1; i < SQUARE(0, (W_SIDE - 1)) && i % W_SIDE != 0 && othello->grid[i] == inv_player; i += W_SIDE - 1) 
			; 
		if ( othello->grid[i] == player ) 
			for( i -= W_SIDE - 1; othello->grid[i] == inv_player; i -= W_SIDE - 1) 
				do_calc(othello, i, player);	
	}

	/* Diagonale en partant vers haut droite */
	if ( (i = position) > SQUARE((W_SIDE - 1), 0) && i % W_SIDE != 7 ) {
		for(i -= W_SIDE - 1; i > SQUARE((W_SIDE - 1), 0) && i % W_SIDE != 7 && othello->grid[i] == inv_player; i -= W_SIDE - 1) 
			; 
		if ( othello->grid[i] == player ) 
			for( i += W_SIDE - 1; othello->grid[i] == inv_player; i += W_SIDE - 1) 
				do_calc(othello, i, player);	
	}

	/* Diagonale en partant vers haut gauche */
	if ( (i = position) > SQUARE((W_SIDE - 1), 0) && i % W_SIDE != 0) {
		for(i -= W_SIDE + 1; i > SQUARE((W_SIDE - 1), 0) && i % W_SIDE != 0 && othello->grid[i] == inv_player; i -= W_SIDE + 1) 
			; 
		if ( othello->grid[i] == player ) 
			for( i += W_SIDE + 1; othello->grid[i] == inv_player; i += W_SIDE + 1) 
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
	if (othello->grid[position] != 0 || position > GRID_SIZE || position < 0 ) 
		return 0;
	
	/* Horizontal en partant sur la gauche */	
	if ( (i = position) % W_SIDE != 0 && othello->grid[--i] == inv_player ) { /* Si la case a gauche est enemi, on part a l'avanture */
		for( ; i % W_SIDE != 0 && othello->grid[i] == inv_player; i--) 
			; 
		if ( othello->grid[i] == player )
			return 1;
	}

	/* Horizontal en partant vers la droite */
	if ( (i = position) % W_SIDE != W_SIDE - 1 && othello->grid[++i] == inv_player ) { /* Si la case a droite est enemi, on part a l'avanture */
		for(; i % W_SIDE != W_SIDE - 1 && othello->grid[i] == inv_player; i++) 
			; 
		if ( othello->grid[i] == player )
			return 1; 

	}
	
	/* Vertical en partant vers le haut */

	if ( (i = position) > SQUARE((W_SIDE - 1), 0) && othello->grid[i -= W_SIDE ] == inv_player ) {
		for(; i > SQUARE((W_SIDE - 1), 0) && othello->grid[i] == inv_player; i -= W_SIDE) 
			; 
		if ( othello->grid[i] == player )
			return 1;
	}

	/* Vertical en partant vers le bas */
	if ( (i = position) < SQUARE(0, (W_SIDE - 1)) && othello->grid[i += W_SIDE] == inv_player ) {
		for(; i < SQUARE(0, (W_SIDE - 1)) && othello->grid[i] == inv_player; i += W_SIDE) 
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
	if ( (i = position) < SQUARE(0, (W_SIDE - 1)) && i % W_SIDE != W_SIDE - 1 && othello->grid[i += W_SIDE + 1] == inv_player ) {
		for(; i < SQUARE(0, (W_SIDE - 1)) && i % W_SIDE != 7 && othello->grid[i] == inv_player; i += W_SIDE + 1) 
			; 
		if ( othello->grid[i] == player ) 
			return 1;	
	}

	/* Diagonale en partant vers bas gauche */
	if ( (i = position) < SQUARE(0, (W_SIDE - 1)) && i % W_SIDE != 0 && othello->grid[i += W_SIDE - 1] == inv_player ) {
		for(; i < SQUARE(0, (W_SIDE - 1)) && i % W_SIDE != 0 && othello->grid[i] == inv_player; i += W_SIDE - 1) 
			; 
		if ( othello->grid[i] == player ) 
			return 1;	
	}

	/* Diagonale en partant vers haut droite */
	if ( (i = position) > SQUARE((W_SIDE - 1), 0) && i % W_SIDE != W_SIDE - 1 && othello->grid[i -= W_SIDE - 1] == inv_player ) {
		for(; i > SQUARE((W_SIDE - 1), 0) && i % W_SIDE != 7 && othello->grid[i] == inv_player; i -= W_SIDE - 1) 
			; 
		if ( othello->grid[i] == player ) 
			return 1;	
	}

	/* Diagonale en partant vers haut gauche */
	if ( (i = position) > SQUARE((W_SIDE - 1), 0) && i % W_SIDE != 0 && othello->grid[i -= W_SIDE + 1] == inv_player ) {
		for(; i > SQUARE((W_SIDE - 1), 0) && i % W_SIDE != 0 && othello->grid[i] == inv_player; i -= W_SIDE + 1 ) 
			; 
		if ( othello->grid[i] == player ) 
			return 1;	
	}
	
	return 0;
}

int hasard(int max) { // fonction hassard , donne un nombre compris entre 0 et max de facon aléatoire.
  return (int)  ((float) rand() / RAND_MAX * max );
}

int move_IA_alea(Othello *othello, char player ) {

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

		printf("je vais jouer en %c %d - %d\n",  COLUMN(nb_coup_possible) ,ROW(nb_coup_possible), nb_coup_possible);
		change_value(othello, nb_coup_possible, player);
		free(coup_possible);
		return 1;
	}

	printf("Je suis bloquée :'( \n");
		
	free(coup_possible);
	return 0;
}


int move_IA_minmax_alphabeta_pvs(Othello *othello, char player){
	int bestMove;

	bestMove = minMax_alphabeta_pvs(othello, player);

	if(bestMove != -1){
		print_othello(othello);
		change_value(othello, bestMove, player);

		printf("je vais jouer en %c %d - %d\n",  COLUMN(bestMove) ,ROW(bestMove), bestMove);
		return 1;
	}
	
	printf("Je suis bloqué :'( \n");
			
	return 0;
}

int move_IA_minmax_alphabeta(Othello *othello, char player){
	int bestMove;

	bestMove = minMax_alphabeta(othello, player);

	if(bestMove != -1){
		print_othello(othello);
		change_value(othello, bestMove, player);

		printf("je vais jouer en %c %d - %d\n",  COLUMN(bestMove) ,ROW(bestMove), bestMove);
		return 1;
	}
	
	printf("Je suis bloqué :'( \n");
			
	return 0;
}

int move_IA_minmax(Othello *othello, char player){
	int bestMove;

	bestMove = minMax(othello, player);

	if(bestMove != -1){
		print_othello(othello);
		change_value(othello, bestMove, player);

		printf("je vais jouer en %c %d - %d\n",  COLUMN(bestMove) ,ROW(bestMove), bestMove);
		return 1;
	}
	
	printf("Je suis bloqué :'( \n");
			
	return 0;
}

int move_left (Othello *othello, char player ) {

	int i;
	
	if ( othello->nb_pawn_p1 + othello->nb_pawn_p2 == GRID_SIZE ) 
		return 0;
		
	for ( i = 0; i < GRID_SIZE; i++ ) 
		if ( good_move(othello, i,player) ) 
				return 1;
		
	return 0;
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
			if( (lettre = othello->grid[SQUARE(i,j)]) == PAWN_J1) printf("%s %c %s|",COLOR, lettre, NCOLOR);
			else printf(" %c |", (lettre == PAWN_J2) ? lettre : lettre + 32 ); /* Lettre + 32 car 32 est le code ascii de l'espace */
		}
		print_ligne();
	}
	
	printf("\n    Score %sX%s : %u   Score O : %u\n",COLOR, NCOLOR, othello->nb_pawn_p1, othello->nb_pawn_p2);
 
	return;
}


int verif_choix(char *phrase,int val_max) {

	int choix;
	while(1) {   
		while(scanf("%2d",&choix) == 0) { // Si l'utilisateur entre autre chose qu'un nombre
			printf("\t-- Erreur --\tLa valeur entrée n'est pas un nombre.\n%s",phrase); 
			videbuffer();
		}

		if( (choix <= val_max && choix > 0) || choix == -1)
			return choix;
		else
			printf("\t-- Erreur --\tLa valeur entrée est soit trop grande soit trop petite.\n%s",phrase);
  

	}
	return -1;
}

int pushPion(Othello *othello, int position, char player){
	if(good_move(othello, position, player)){
		change_value(othello, position, player);
		return 1;
	}

	return 0;
}

/* Libération de l'allocation mémoire de 
 * l'othello 
 */
void free_othello(Othello *othello){
	free(othello->grid);
	free(othello);

	return ;
}

void game(Othello *othello, char player, int nb_joueur_h) {
	int nb_tour = 0;
	int oops;
	while(othello->nb_pawn_p1 > 0 && othello->nb_pawn_p2 > 0 && (othello->nb_pawn_p2 + othello->nb_pawn_p1) != GRID_SIZE && oops) {
		if ( nb_tour % 2 == 0 ) oops = 2;
		print_othello(othello);  /* Affichage de l'othello */
		if ( nb_joueur_h == 2 || ( nb_joueur_h == 1 && player == 'X') ) 
			if ( ! othello_ask_choice(othello, player) )
				oops--;		
		if ( nb_joueur_h == 0 || ( nb_joueur_h == 1 && player == 'O') ) 
			if ( ! move_IA_minmax_alphabeta_pvs(othello, player) ) 
				oops--;
		player = SWITCH_PLAYER(player);
		printf("Tour n° %d\n", nb_tour);
		++nb_tour;
	}
	print_othello(othello);  /* Affichage de l'othello */
}


int gameOver(Othello *othello){
	if(othello->nb_pawn_p1 + othello->nb_pawn_p2 == GRID_SIZE){
		if(othello->nb_pawn_p1 > othello->nb_pawn_p2)
			return 1; /* Player 1 qui gagne */
		else 
			return 2; /* Player 2 qui gagne */
	}

	if(othello->nb_pawn_p2 == 0)
		return 1; /* Player 1 qui gagne */

	if(othello->nb_pawn_p1 == 0)
		return 2; /* Player 2 qui gagne */

	return 0; /* Partie pas encore terminée */
}
