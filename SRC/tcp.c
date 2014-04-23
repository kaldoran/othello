#include "tcp.h"
#include "ia.h"
#include "affichage.h"
#include "gestion_fichier.h"

#define LG_TAB 66

#if DEBUG
	#define AFFICHE(DATA) printf("Recu : %s.\n", (char *)DATA);
#else 
	#define AFFICHE(DATA) ;
#endif
	
	
void new_socket(Configuration *config) {
	/* creation de la socket */
	config->id_socket = socket(AF_INET,SOCK_STREAM,0); /* socket internet TCP */ 
    	if (config->id_socket == -1) 
		QUIT_MSG("Erreur : Probleme lors de la création de la socket");
}

int tcp_start(Configuration *config) {
	struct sockaddr_in serv;
	size_t serv_length = sizeof serv;
	
	memset(&serv, 0, serv_length);
	serv.sin_family = AF_INET;
	serv.sin_port = config->port;
	serv.sin_addr.s_addr = config->ip;

	if (connect(config->id_socket, (struct sockaddr *)&serv, serv_length) < 0){
		close(config->id_socket);
		return 0;
	}
	
	return 1;
}

int tcp_action(Configuration *config, void *data, int data_length, int type) {
	
	if ( type == SEND ) 
		return send(config->id_socket, data, data_length, 0);
	else if ( type == RECEIVED ) {
		return recv(config->id_socket, data, data_length, 0);
	}
	else 
		return -1;
}

int serveur(Othello *othello, int serv) {
	Configuration *config = nouvelle_configuration();
	charger_configuration(config);

	char received[LG_TAB];
	int choix;
	new_socket(config);
	
	if ( serv == 1 ) {
		printf("Ajout \\n\n");
		strcat(config->pseudo, "\n");
		strcat(config->password, "\n");
	}
	
	printf("Début tcp\n");
	if (tcp_start(config)) {
		if ( serv != 3 ) {
			printf("User - RECEIVED %d\n", tcp_action(config, &received, sizeof(received), RECEIVED)); 
			AFFICHE(received);
			reinit_tab(&received);
		}
		
		printf("\nSEND : Envoi de données Pseudo %d\n",tcp_action(config, config->pseudo, 64, SEND));

		if ( serv != 3 ) {
			printf("Password - RECEIVED %d\n", tcp_action(config, &received, sizeof(received), RECEIVED)); 
			AFFICHE(received);
			reinit_tab(&received);
		
			printf("SEND : Envoi de données Mdp : %d\n", tcp_action(config, config->password, 64, SEND));

			printf("[connect ou type] RECEIVED %d\n", tcp_action(config, &received, sizeof(received), RECEIVED));
			AFFICHE(received);
			reinit_tab(&received);	
		
			if ( serv == 1 ) {
				if (strcmp(received, "connecte") > 0)
					return -1;
			
				while ( (choix = tcp_action(config, &received, sizeof(received), RECEIVED)) == LG_TAB )
					reinit_tab(&received);
			}
		
			choix_tcp();
			#if DEBUG 
				choix = verif_choix("Quel est votre choix ? ",4);
			#else
				choix = verif_choix("Quel est votre choix ? ",3);
			#endif
			switch (choix ) {
				case 1:
					printf("SEND : Envoi de données Type : %d\n",tcp_action(config, "PS\n", 3, SEND));
					break;
				case 2:
					printf("SEND : Envoi de données Type : %d\n",tcp_action(config, "PS IA\n", 6, SEND));
					break;
				case 3:
					printf("SEND : Envoi de données Type : %d\n",tcp_action(config, "TOURNAMENT\n", 11, SEND));
					break;
				#if DEBUG
				case 4:
					printf("SEND : Envoi de donnée type : %d\n", tcp_action(config, "TEST\n", 5, SEND));
					break;
				#endif
				default:
					return 0;
					break;
			}

			printf("RECEIVED %d\n", tcp_action(config, &received, sizeof(received), RECEIVED)); 
			AFFICHE(received);

			if (strcmp(received, "OK"))
				return -1;
		}
		
		do{
			choix = 0;
			/* +1 ici pour cause, un \0 a été ajouté, ce qui fait ... 67 caracteres
			 * Et si je ne le lis pas, je l'aurais au prochain tour de boucle 
			 */
			if ( serv == 1 )
				printf("RECEIVED %d\n", tcp_action(config, &received, sizeof(received) + 1, RECEIVED));
			else 
				printf("RECEIVED %d\n", tcp_action(config, &received, sizeof(received), RECEIVED));
				
			AFFICHE(received);
			
			if ( received[1] != 'F' && received[0] != 'T' ) {
				othello = convert(othello, received);
				
/*		VERSION SELON LES NORMES 		*/
				if ( serv == 3 ) {
					received[0] = minMax_alphabeta(othello, received[0]);
					DEBUG_PRINTF("Je joue en %c %d - %d - Je suis : %c\n", COLUMN((int)received[0]) ,ROW((int)received[0]), (int)received[0], othello->iam);	
					if ( tcp_action(config, &received, 1, SEND) <= 0 )
						return -1;
				} 
				else {
					choix = minMax_alphabeta(othello, received[0]);
					DEBUG_PRINTF("Je joue en %c %d - %d - Je suis : %c\n", COLUMN(choix) ,ROW(choix), choix, othello->iam);
					snprintf(received, 4, "%d\n", choix);
					
					if ( tcp_action(config, &received, 4, SEND) <= 0 )
						return -1;
				}

				reinit_tab(&received);
			}
		}while( received[1] != 'F' && received[0] != 'T' );
		/* Fin transmission */
		close(config->id_socket);
		free(config);
	}
	else {
		free(config);
		QUIT_MSG("Probleme lors de la création de la socket\n");
	}

	return 1;
}

/* Converti un plateau recu en tcp en un plateau pour l'ia */
Othello* convert(Othello *othello, char received[66]) {
	int i;
	othello->iam = received[0];
	othello->nb_pawn_p1 = 0;
	othello->nb_pawn_p2 = 0;
	memset(othello->grid, 0, sizeof(othello->grid));
	
	for ( i = 2; i != GRID_SIZE + 2; i++ ) {
		if ( received[i] == PAWN_J1) ++othello->nb_pawn_p1;
		if ( received[i] == PAWN_J2) ++othello->nb_pawn_p2;
		if ( received[i] == '0' )
			received[i] = '\0';
			
		othello->grid[i - 2] = received[i]; /* un memcpy aurait fait de meme mais vu que je compte le nombre de pion au passage ..... */
	}
	
	#if DEBUG 
		print_othello(othello);
	#endif
	
	return othello;
}

void reinit_tab(void *data) {
	memset(data, 0, sizeof(data));
}
