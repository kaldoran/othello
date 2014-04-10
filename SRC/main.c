#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "tcp.h"
#include "delay_sleep.h"
#include "othello.h"
#include "affichage.h"
#include "gestion_fichier.h"

int main(int argc, char *argv[]) {
	int choix;
	Othello *othello;
	char player = 'X';
	srand(time(NULL));

	if ( 0 ) {
		/* Chargement de la configuration */
		Configuration *config = nouvelle_configuration();
		charger_configuration(config);
		
		new_socket(config);
		if (tcp_start(config)) {
			/* Oubli pas de lancer le serveur si tu veux tester tournier */
			printf("SEND : Envoi de données %d\n",tcp_action(config, config->pseudo, 64, SEND));
			printf("SEND : Je veux jouer en 20 - %d\n",tcp_action(config, "20", 2, SEND));
			close(config->id_socket);
			free(config);
		}
		else {
			free(config);
			QUIT_MSG("Probleme lors de la création de la socket\n");
		}

		do_pause();
	}	

	do {

		_reset_term();
		menu_principal();
		choix = verif_choix("Quel est votre choix ? ",4);
		videbuffer();

		if ( choix == 1 || choix == 2 || choix == 3)
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
				printf("Connection\n");
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
		
		if ( choix == 1 || choix == 2 || choix == 3)
			free_othello(othello);

	} while ( 1 );
	
	exit(EXIT_SUCCESS);
}
