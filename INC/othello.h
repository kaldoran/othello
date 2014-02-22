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

int good_move(Othello *othello, int position, char player, int return_or_not);

/* Affiche la grille d'othello
 */
void print_othello(Othello *othello);

#endif
