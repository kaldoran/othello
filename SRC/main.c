#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "delay_sleep.h"
#include "othello.h"
#include "affichage.h"
#include "gestion_fichier.h"

int main(int argc, char *argv[]) {
	int choix;

	char player = 'X';
	srand(time(NULL));
//	Configuration *config = nouvelle_configuration();
//	charger_configuration(config);
//	printf("%s\n", config->pseudo);
//	free(config);

	do_pause();
	do {
		Othello *othello = new_othello(); /* Crée un nouvelle othello */
		_reset_term();
		menu_principal();
		choix = verif_choix("Quel est votre choix ? ",4);
		switch(choix) {
			case -1:
				free(othello->grid);
				free(othello);
				printf("\t\tAu revoir et a bientôt\n");
				pause_ms(1200);
				_reset_term(); 
				exit(EXIT_SUCCESS);
			break;
			case 1:
				while(othello->nb_pawn_p1 > 0 && othello->nb_pawn_p2 > 0 && (othello->nb_pawn_p2 + othello->nb_pawn_p1) != GRID_SIZE ) {
					print_othello(othello);  /* Affichage de l'othello */
					if ( player == 'X' ) othello_ask_choice(othello, player);
					else move_IA(othello, player);
					player = SWITCH_PLAYER(player);
				}
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
			break; 
			default:
				printf("-- Erreur --\tImpossible d'acceder au module %d.\n ",choix);
			break;
		}

	} while ( 1 );
	
	exit(EXIT_SUCCESS);
}
