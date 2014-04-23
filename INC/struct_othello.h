/* ---------------------------------------------------------------------- */
/* Filename: struct_othello.h                                             */
/* Author: REYNAUD Nicolas                                                */
/* Date: 2013-02-22 - 19:01:16                                            */
/*                                                                        */
/* ---------------------------------------------------------------------- */


#ifndef STRUCT_OTHELLO_H
#define STRUCT_OTHELLO_H

typedef struct Othello {
	unsigned int nb_pawn_p1;
	unsigned int nb_pawn_p2;
	char iam;
	char *grid;
} Othello;



#endif
