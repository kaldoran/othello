/* ---------------------------------------------------------------------- */
/* Filename: othello.h                                                    */
/* Author: REYNAUD Nicolas                                                */
/* Date: 2013-02-22 - 19:01:16                                            */
/*                                                                        */
/* ---------------------------------------------------------------------- */

#ifndef OTHELLO_H
#define OTHELLO_H

#include "global.h"
#include "struct_othello.h"

/* Alloue la structure 
 * Ajout les pions au centre et initaliser les valeurs 
 */
Othello *new_othello();


/* Affiche la grille d'othello
 */
void print_othello(Othello *othello);

#endif
