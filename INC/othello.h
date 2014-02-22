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

int videbuffer();

int othello_ask_choice(Othello *othello, char player);

int good_move(Othello *othello, int position, char player, int return_or_not);

int move_left (Othello *othello, char player );

/* Affiche la grille d'othello
 */
void print_othello(Othello *othello);

#endif
