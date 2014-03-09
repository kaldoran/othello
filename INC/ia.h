#ifndef _IA_H_
#define _IA_H_

#include <limits.h>
#include "othello.h"
#include "global.h"

/* Prototype de fonction */

int eval_min(Othello *othello, char player, int depth);
int eval_max(Othello *othello, char player, int depth);
int eval_grid(Othello *othello, char player);

#endif /* _IA_H_ included */