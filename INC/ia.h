#ifndef _IA_H_
#define _IA_H_

#include <limits.h>
#include "othello.h"
#include "global.h"

/* constante */
#define DEPTH 10 /* profondeur max pour la recherche du minMax */
#define WIN 100000

/* Prototype de fonction */
Othello* cpy_othello(Othello *othello);
int minMax(Othello *othello, char player);
int MinMax_negamax(Othello *othello, char player);
int negamax(Othello *othello, char player, int depth);
int eval_min(Othello *othello, char player, int depth);
int eval_max(Othello *othello, char player, int depth);
int eval_grid(Othello *othello, char player, int move);
int eval_grid2(Othello *othello, char player, int move);
int alphabeta(Othello *othello, char player, int depth, int alpha, int beta);
int minMax_alphabeta(Othello *othello, char player);
int alphabeta_pvs(Othello *othello, char player, int depth, int alpha, int beta);
int minMax_alphabeta_pvs(Othello *othello, char player);

#endif /* _IA_H_ included */
