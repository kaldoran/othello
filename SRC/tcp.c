#include "tcp.h"
#include "ia.h"
#include "affichage.h"
#include "gestion_fichier.h"

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

	char received[66];
	int choix;
	new_socket(config);
	if (tcp_start(config)) {

		printf("User - RECEIVED %d\n", tcp_action(config, &received, sizeof(received), RECEIVED)); 
		printf("SEND : Envoi de données Pseudo %d\n",tcp_action(config, config->pseudo, 64, SEND));
		
		printf("Password - RECEIVED %d\n", tcp_action(config, &received, sizeof(received), RECEIVED)); 
		printf("SEND : Envoi de données Mdp : %d\n", tcp_action(config, config->password, 64, SEND));

		printf("[connect ou type] RECEIVED %d\n", tcp_action(config, &received, sizeof(received), RECEIVED)); 
		if ( serv == 1 )
			if (strcasecmp(received, "connecte"))
				return -1;

		choix_tcp();
		#if DEBUG 
			choix = verif_choix("Quel est votre choix ? ",4);
		#else
			choix = verif_choix("Quel est votre choix ? ",3);
		#endif
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
			#if DEBUG
			case 4:
				printf("SEND : Envoi de donnée tupe : %d\n", tcp_action(config, "TEST", 4, SEND));
				break;
			#endif
			default:
				return 0;
				break;
		}
		
		printf("RECEIVED %d\n", tcp_action(config, &received, sizeof(received), RECEIVED)); 
		if (strcasecmp(received, "ok"))
			return -1;
				
		do{
			printf("RECEIVED %d\n", tcp_action(config, &received, sizeof(received), RECEIVED)); 
			for ( choix = 0; choix != 66; choix ++)
				printf("%c", received[choix]);
			
			if ( received[0] != 'F' ) {
				convert(othello, received);
				received[0] = minMax_alphabeta(othello, received[0]);
				DEBUG_PRINTF("Je joue en %c", received[0]);	

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
	return 1;
}

/* Converti un plateau recu en tcp en un plateau pour l'ia */
void convert(Othello *othello, char received[66]) {
	int i = 0;
	for ( i = 0; i != GRID_SIZE; i++ ) {
		if ( received[i] == PAWN_J1) ++othello->nb_pawn_p1;
		if ( received[i] == PAWN_J2) ++othello->nb_pawn_p2;
		
		othello->grid[i] = received[i]; /* un memcpy aurait fait de meme mais vu que je compte le nombre de pion au passage ..... */
	}
	
}
