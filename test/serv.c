/*
                       serveur :

                socket TCP

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 16384   /* numero du port serveur (a communiquer aux clients) */

#define MAX_CONNEXIONS 1 /* nombre max de connexions entrantes */

int main (int argc, char *argv[], char *envp[]){
  int i, l, n, sock, sock_client;
  struct sockaddr_in s_serveur;        /* adresse serveur */
  struct sockaddr_in s_client;         /* adresse client  */
  char Rep[80];

  /* creation de la socket */
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1){
      perror("serveur-socket");
      exit(-1);
  }
  
  l = sizeof(struct sockaddr_in);

  /* assignation de l'adresse */
  s_serveur.sin_family      = AF_INET;
  s_serveur.sin_addr.s_addr = INADDR_ANY;
  s_serveur.sin_port        = htons(PORT);

  /* branchement de la socket     */
  if (bind(sock, (struct sockaddr *)&s_serveur, l) == -1){
      perror("serveur-bind");
      exit(-1);
  }

  /* on veut écouter, MAX_CONNEXIONS connexions au max */
  if (listen(sock,MAX_CONNEXIONS)==-1){
      perror("serveur-listen");
      exit(-1);
  }
      /* attente d'une connexion */
  sock_client = accept(sock, (struct sockaddr *) &s_client, (socklen_t *) &l);
  if (sock_client == -1){
      perror("serveur-accept");
     exit(-1);
  }
  /* boucle lecture et renvoi du message, jusqu'au stop */
  do {
 
      for ( i = 0; i != 80; i++)
      	Rep[i] = '\0';
      	
      /* lecture du message dans la socket */
      n = read(sock_client, Rep, 80);
      if (n == -1){
          perror("serveur-read");
          exit(-1);
        }
      

      /* affichage du message recu */
      printf(" serveur : message recu <%s> sur le port %d\n",Rep,
             ntohs(s_client.sin_port));

      /* renvoi du message, attention a strlen + 1 pour envoyer \0 */
      n = write(sock_client,Rep,strlen(Rep)+1);
      if (n == -1){
          perror("serveur-write");
          exit(-1);
        }

    }
  while (strcmp(Rep,"stop"));
  close(sock_client);
  /* fermeture de la socket */
  close(sock);
  exit(0);
}
