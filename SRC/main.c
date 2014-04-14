#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "tcp.h"
#include "delay_sleep.h"
#include "othello.h"
#include "affichage.h"
#include "gestion_fichier.h"
#include "ia.h" 

void convert(Othello *othello, char received[66]) {
	int i = 0;
	for ( i = 0; i != GRID_SIZE; i++ ) {
		if ( received[i] == PAWN_J1) ++othello->nb_pawn_p1;
		if ( received[i] == PAWN_J2) ++othello->nb_pawn_p2;
		
		othello->grid[i] = received[i]; /* un memcpy aurait fait de meme mais vu que je compte le nombre de pion au passage ..... */
	}
	
}

int main(int argc, char *argv[]) {
	int choix;
	Othello *othello;
	char player = 'X';
	srand(time(NULL));
	char received[66];

	if ( 1 ) {
	
		/* A supprimer lorsque ce sera une fonction */
		othello = new_othello(); 
		/* Chargement de la configuration */
		Configuration *config = nouvelle_configuration();
		charger_configuration(config);
		
		new_socket(config);
		if (tcp_start(config)) {

			printf("SEND : Envoi de données Pseudo %d\n",tcp_action(config, config->pseudo, 64, SEND));

			printf("SEND : Envoi de données Mdp : %d\n", tcp_action(config, config->password, 64, SEND));
			/* récuperer données Connecte */
			/* Si connecte continuer sinon return */
			choix_tcp();
			choix = verif_choix("Quel est votre choix ? ",3);
			switch (choix ) {
				case 1:
					printf("SEND : Envoi de données Type : %d\n",tcp_action(config, "PS", 2, SEND));
					break;
				case 2:
					printf("SEND : Envoi de données Type : %d\n",tcp_action(config, "PS IA", 5, SEND));
					break;
				case 3:
					printf("SEND : Envoi de données Type : %d\n",tcp_action(config, "TOURNAMENT", 10, SEND));
					break;
				default:
					return -1;
					break;
			}
				
			do{
				printf("RECEIVED %d\n", tcp_action(config, &received, sizeof(received), RECEIVED)); 
				for ( choix = 0; choix != 66; choix ++)
					printf("%c", received[choix]);
				
				if ( received[0] != 'F' ) {
					convert(othello, received);
					received[0] = minMax_alphabeta(othello, received[0]);
				
					/* Calcul IA */
					if ( tcp_action(config, &received[0], 1, SEND) <= 0 )
						return -1;
				}
			}while(received[0] != 'F' );
			/* Fin transmission */
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
