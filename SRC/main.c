#include <stdio.h>
#include <stdlib.h>
#include "othello.h"

int main() {


	Othello *othello;

	othello = new_othello(); /* Crée un nouvelle othello */
	print_othello(othello);  /* Affichage de l'othello */

	printf("%d", othello_ask_choice(othello, 'X'));
	/* Il a free il a tout compris */
	free(othello->grid);
	free(othello);
	return 1;
}
