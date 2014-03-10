#include "ia.h"



static const int grid_eval[] = { 500, -150, 30, 10, 10, 30, -150,  500,
				-150, -250,  0,  0,  0,  0, -250, -150,
				30,    0,  1,  2,  2,  1,    0,   30,
				10,    0,  2, 16, 16,  2,    0,   10,
				10,    0,  2, 16, 16,  2,    0,   10,
				30,    0,  1,  2,  2,  1,    0,   30,
				-150, -250,  0,  0,  0,  0, -250, -150,
				500, -150, 30, 10, 10, 30, -150,   500};


/* Fonction qui évalue tous les coups possibles à jouer
 * et qui choisit le coup ayant l'évalution la plus petite
 * évaluation
 */
int eval_min (Othello *othello, char player, int depth){
	int i, min = INT_MAX, score_other_player;

	Othello *copy = NULL;

	if(depth == 0){
		return eval_grid(othello, player);
	}

	copy = new_othello();


	/* Copie de la grille pour évaluer tous les coups possibles */
	for(i = 0; i < GRID_SIZE; ++i){
		copy->grid[i] = othello->grid[i];
	}

	/* Le i me sert pour les lignes */
	for(i = 0; i < GRID_SIZE; ++i){

		/* Si ce coups est un bon coup je vais chercher dans le 
		 * coups suivant le meilleur des coups possibles
		 * et je le teste avec mon min actuel
		 */
		if(good_move(copy, i, player)){

			if((score_other_player = eval_max(copy, SWITCH_PLAYER(player), depth -1)) < min){
				min = score_other_player;
			}
		}
		
	}

	return min;
}


/* Fonction qui évalue tous les coups possibles à jouer
 * et qui choisit le coup ayant l'évalution la plus haute
 * évaluation
 */
int eval_max (Othello *othello, char player, int depth){
	int i, max = INT_MIN, score_other_player;

	Othello *copy = NULL;

	if(depth == 0){
		return eval_grid(othello, player);
	}

	copy = new_othello();


	/* Copie de la grille pour évaluer tous les coups possibles */
	for(i = 0; i < GRID_SIZE; ++i){
		copy->grid[i] = othello->grid[i];
	}

	/* Le i me sert pour les lignes */
	for(i = 0; i < W_SIDE; ++i){

		/* Si ce coups est un bon coup je vais chercher dans le 
		 * coups suivant le moins bon des coups possibles
		 * et je le teste avec mon max actuel
		 */
		if(good_move(copy, i, player)){

			if((score_other_player = eval_min(copy, SWITCH_PLAYER(player), depth -1)) > max){
				max = score_other_player;
			}
		}

	}

	return max;
}

int eval_grid(Othello *othello, char player){
	int i, eval;
	if ( player == PAWN_J1 )
		eval = othello->nb_pawn_j1 - nb_pawn_j2; 
	else 
		eval = othello->nb_pawn_j2 - nb_pawn_j1;
	return eval;
}
