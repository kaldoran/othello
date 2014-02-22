#include <stdio.h>
#include <stdlib.h>
#include "othello.h"

int main() {


	Othello *othello;

	othello = new_othello(); /* Crée un nouvelle othello */
	char player = 'X';

	while(1) {
		print_othello(othello);  /* Affichage de l'othello */
		othello_ask_choice(othello, player);
		player = SWITCH_PLAYER(player);
	}	
	print_othello(othello);  /* Affichage de l'othello */
	/* Il a free il a tout compris */
	free(othello->grid);
	free(othello);
	return 1;
}
