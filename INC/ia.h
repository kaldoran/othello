#ifndef _IA_H_
#define _IA_H_

#include <limits.h>
#include "othello.h"
#include "global.h"

/* constante */
#define DEPTH 5 /* profondeur max pour la recherche du minMax */


/* Prototype de fonction */
Othello* cpy_othello(Othello *othello);
int minMax(Othello *othello, char player);
int eval_min(Othello *othello, char player, int depth);
int eval_max(Othello *othello, char player, int depth);
int eval_grid(Othello *othello, char player, int move);

#endif /* _IA_H_ included */