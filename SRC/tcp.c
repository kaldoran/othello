#include "tcp.h"

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
