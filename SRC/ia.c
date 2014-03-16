#include "ia.h"



static const int grid_eval[] = { 500, -150, 30, 10, 10, 30, -150,  500,
				-150, -250,  0,  0,  0,  0, -250, -150,
				30,    0,  1,  2,  2,  1,    0,   30,
				10,    0,  2, 16, 16,  2,    0,   10,
				10,    0,  2, 16, 16,  2,    0,   10,
				30,    0,  1,  2,  2,  1,    0,   30,
				-150, -250,  0,  0,  0,  0, -250, -150,
				500, -150, 30, 10, 10, 30, -150,   500};


Othello* cpy_othello(Othello *othello){
	Othello *copy = new_othello();
	memcpy(copy->grid, othello->grid, GRID_SIZE * sizeof(char));

	copy->nb_pawn_p1 = othello->nb_pawn_p1;
	copy->nb_pawn_p2 = othello->nb_pawn_p2;

	return copy;
}

/* Fonction MinMax qui retourne le meilleur coup à jouer */
int minMax(Othello *othello, char player){
	int bestMove = INT_MIN, bestScore = INT_MIN, depth = DEPTH, i, tmp;
	Othello *copy = NULL;

	for( i = 0; i < GRID_SIZE; ++i ){

		if(good_move(othello, i, player)){

			copy = cpy_othello(othello);

			change_value(copy, i, player);

			if( (tmp = eval_min(copy, player, depth)) >= bestScore){
				bestScore = tmp;
				bestMove = i;
			}
			DEBUG_PRINTF("Tmp %d \n", tmp); 
			free_othello(copy);

		}

	}
	DEBUG_PRINTF("Error ici3 %d - i : %d\n", bestScore, bestMove); 
	return bestMove;
}

/* Fonction qui évalue tous les coups possibles à jouer
 * et qui choisit le coup ayant l'évalution la plus petite
 * évaluation
 */
int eval_min (Othello *othello, char player, int depth){
	int i, min = INT_MAX, score_other_player, move = 0;
	if ( othello->nb_pawn_p1 == 0 )
		return (player == PAWN_J1) ? -WIN : WIN;
	else if ( othello->nb_pawn_p2 == 0 )
		return (player == PAWN_J1) ? WIN : -WIN;
		
	Othello *copy = NULL;

	if(depth == 0){
		return eval_grid(othello, player, move);
	}	

	/* Le i me sert pour les lignes */
	for(i = 0; i < GRID_SIZE; ++i){

		/* Copie de la grille pour évaluer tous les coups possibles 
   		 * donc pour que je puisse évaluer tous les coups je 
   		 * crée une copy de ma grille j'ajoute le coup que je veux jouer
   		 * puis j'effectue la récursivité, une fois mon score
   		 * récupéré je libère ma grille 
   		 * de cette façon sa me permet d'annuler le coup 
   		 * que je viens de jouer
		 *
		 * Je joue mon coup, si il est possible alors je vais  
		 * chercher dans le coups suivant le meilleur des coups possibles
		 * et je le teste avec mon min actuel
		 */
		 	
		if(good_move(othello, i, player)){
		
			copy = cpy_othello(othello);

			change_value(copy, i, player);
			if((score_other_player = eval_max(copy, SWITCH_PLAYER(player), depth -1)) < min ){
				min = score_other_player;
				move = i;
			}

			free_othello(copy);
		}


		
	}

	return min;
}


/* Fonction qui évalue tous les coups possibles à jouer
 * et qui choisit le coup ayant l'évalution la plus haute
 * évaluation
 */
int eval_max (Othello *othello, char player, int depth){
	int i, max = INT_MIN, score_other_player, move = 0;
	
	if ( othello->nb_pawn_p1 == 0 )
		return (player == PAWN_J1) ? WIN : -WIN;
	else if ( othello->nb_pawn_p2 == 0 )
		return (player == PAWN_J1) ? -WIN : WIN;
		
	Othello *copy = NULL;

	if(depth == 0){
		return eval_grid(othello, player, move);
	}


	/* Le i me sert pour les lignes */
	for(i = 0; i < GRID_SIZE; ++i){

		/* Copie de la grille pour évaluer tous les coups possibles 
   		 * donc pour que je puisse évaluer tous les coups je 
   		 * crée une copy de ma grille j'ajoute le coup que je veux jouer
   		 * puis j'effectue la récursivité, une fois mon score
   		 * récupéré je libère ma grille 
   		 * de cette façon sa me permet d'annuler le coup 
   		 * que je viens de jouer
		 *
		 * Si ce coups est un bon coup je le fais et 
		 * coups suivant le moins bon des coups possibles
		 * et je le teste avec mon max actuel
		 */
		 if(good_move(othello, i, player)){
			
			copy = cpy_othello(othello);

			change_value(copy, i, player);

			if((score_other_player = eval_min(copy, SWITCH_PLAYER(player), depth -1)) > max){
				max = score_other_player;
				move = i;
			}

			free_othello(copy);
		}
	}

	return max;
}


/* Fonction qui évalue l'état de la grille
 * si la tendance est favorable au joueur player
 * ou alors à l'autre joueur
 */
int eval_grid(Othello *othello, char player, int position_jouee){
	int eval, g_eval;
	if ( othello->nb_pawn_p1 + othello->nb_pawn_p2 < 30 ) {
		if ( player == PAWN_J2 )
			eval = 50 * ( othello->nb_pawn_p1 - othello->nb_pawn_p2);
		else
			eval = 50 * ( othello->nb_pawn_p2 - othello->nb_pawn_p1);
	}
	else {
		if ( player == PAWN_J2 )
			eval = 100 * ( othello->nb_pawn_p2 - othello->nb_pawn_p1);
		else
			eval = 100 * ( othello->nb_pawn_p1 - othello->nb_pawn_p2);
	}
     
	g_eval = 120 * grid_eval[position_jouee];
	return g_eval + eval;
}
