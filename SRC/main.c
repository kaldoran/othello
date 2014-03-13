#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "delay_sleep.h"
#include "othello.h"
#include "affichage.h"
#include "gestion_fichier.h"

int main(int argc, char *argv[]) {
	int choix;
	srand(time(NULL));
	
	do {
		menu_principal();
		choix = verif_choix("Quel est votre choix ? ",4);
		switch(choix) {
			case -1:
				printf("\t\tAu revoir et a bientôt\n");
				pause_ms(1200);
				_reset_term(); 
				exit(EXIT_SUCCESS);
			break;
			case 1:
				printf("\tCase 1 \n");
				do_pause();
			break;
			case 2:
				printf("\tCase 2 \n");
				do_pause();
			break;
			case 3:
				printf("\tCase 3 \n");
				do_pause();
			break;
			case 4:
				_clean();
				afficher_regles();
				do_pause();
			break; /* break case 5 - menu_humain */
			default:
				printf("-- Erreur --\tImpossible d'acceder au module %d.\n ",choix);
			break;
		}
	_reset_term();
	} while ( 1 );
	
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
	
	
	exit(EXIT_SUCCESS);
}
