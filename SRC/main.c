#include <stdio.h>
#include <stdlib.h>
#include "othello.h"
#include "time.h"

int main() {
	srand(time(NULL));

	Othello *othello;

	othello = new_othello(); /* Crée un nouvelle othello */
	char player = 'X';
	int pos = 15;
	printf("%d - %c - %d\n", pos, COLUMN(pos), ROW(pos));
	while(othello->nb_pawn_p1 > 0 && othello->nb_pawn_p2 > 0 && (othello->nb_pawn_p2 + othello->nb_pawn_p1) != GRID_SIZE ) {
		print_othello(othello);  /* Affichage de l'othello */
		if ( player == 'X' ) othello_ask_choice(othello, player);
		else move_IA(othello, player);
		player = SWITCH_PLAYER(player);
	}

	print_othello(othello);  /* Affichage de l'othello */
	/* Il a free il a tout compris */
	free(othello->grid);
	free(othello);
	return 1;
}
