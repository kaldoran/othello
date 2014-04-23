#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "tcp.h"
#include "delay_sleep.h"
#include "othello.h"
#include "affichage.h"
#include "gestion_fichier.h"
#include "ia.h" 

int main(int argc, char *argv[]) {
	int choix;
	Othello *othello;
	char player = 'X';
	srand(time(NULL));

	do {
		_reset_term();
		menu_principal();
		choix = verif_choix("Quel est votre choix ? ",4);

		if ( choix >= 1 || choix <= 4)
			othello = new_othello(); /* Crée un nouvelle othello */
			
		switch(choix) {
			case -1:
				printf("\t\tAu revoir et a bientôt\n");
				pause_ms(1200);
				_reset_term(); 
				exit(EXIT_SUCCESS);
			break;
			case 1:
				game(othello, player, 2);
				do_pause();
			break;
			case 2:
				game(othello, player, 1);
				do_pause();
			break;
			case 3:
				game(othello, player, 0);
				do_pause();
			break;
			case 4:
				_clean();
				printf("Pensez a changer les infos de BDD/config.txt avant de continuer\n");
				choix_serv();
				choix = verif_choix("Quel est votre choix ? ", 3);

				if ( choix != -1 ) 
					if (serveur(othello, choix) == -1 ) 
						fprintf(stderr,"Probleme avec le serveur\n");
				do_pause();
			break;
			case 5:
				_clean();
				afficher_regles();
				do_pause();
			break; 
			default:
				printf("-- Erreur --\tImpossible d'acceder au module %d.\n ",choix);
			break;
		}
		
		if ( choix >= 1 || choix <= 4)
			free_othello(othello);

	} while ( 1 );
	
	exit(EXIT_SUCCESS);
}
