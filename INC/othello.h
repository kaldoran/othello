/* ---------------------------------------------------------------------- */
/* Filename: othello.h                                                    */
/* Author: REYNAUD Nicolas                                                */
/* Date: 2013-02-22 - 19:01:16                                            */
/*                                                                        */
/* ---------------------------------------------------------------------- */



/* FICHIER NON COMPLET */
#ifndef OTHELLO_H
#define OTHELLO_H

#include "global.h"
#include "struct_othello.h"

/* Alloue la structure 
 * Ajout les pions au centre et initaliser les valeurs 
 */
Othello *new_othello();

int othello_ask_choice(Othello *othello, char player);

void change_value(Othello *othello, int position, char player);

int good_move(Othello *othello, int position, char player);

int move_left (Othello *othello, char player );

void move_IA (Othello *othello, char player );
/* Affiche la grille d'othello
 */
void print_othello(Othello *othello);

/* Verifi si le choix est entre 0 et val_max 
 * Ou égale a -1 , si oui la valeur est retourner
 * Sinon la question est reposée
 */
int verif_choix(char *phrase,int val_max);

#endif
