#ifndef TCP_H
#define TCP_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "global.h"
#include "struct_config.h"

#define SEND 0
#define RECEIVED 1

/* Crée une nouvelle socket et met a jours l'id dans la socket */
void new_socket(Configuration *config);

/* Demarre une connection TCP avec la configuration config */
int tcp_start(Configuration *config);

/* 
 * Effectue une action en rapport avec la socket presente dans la config 
 * Si type = SEND, envoi de donnée
 * Sinon si type = RECEIVED , reception
 */

int tcp_action(Configuration *config, void *data, int data_length, int type);

#endif
