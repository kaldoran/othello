// -------------------------------------------------------- 
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : affichage.c                                    |
// DATE : 13/03/14                                          |
//                                                          |
// - Définition des fonctions de affichage.h                |
// - pour plus de detaile C.F affichage.h                   |
// -------------------------------------------------------- 

#include "affichage.h"

void menu_principal() {
	printf("Choissisez le type de jeu :\n\n");
	printf("\t[1] Humain Vs Humain\n");
	printf("\t[2] Humain Vs Ordi\n");
	printf("\t[3] Ordi Vs Ordi\n");
	printf("\t[4] Connection serveur\n");
	printf("\t[5] Regles\n");
	printf("\t[-1] Quitter\n\n");  

	printf("Quel est votre choix ? ");

}

void msg_H_vs_H() {
	printf("\t\t\t  ------------------------\n\t\t\t| Humain contre Humain |\n\t\t\t  ------------------------\n\n");
}

void msg_IA_vs_H() {
	printf("\t\t\t  ----------------------------\n\t\t\t| Ordinateur contre Humain |\n\t\t\t  ----------------------------\n\n");
}


void menu_IA_vs_H() {
	printf("Choissez une difficulter :\n");
	printf("\t[1] Tres facile \t[L'ordi joue au hasard]\n");
	printf("\t[2] Facile \t\t[Profondeur 3]\n");
	printf("\t[3] Moyen  \t\t[Profondeur 5]\n");
	printf("\t[4] Difficile \t\t[Profondeur 7]\n");
	printf("\t[5] Très Difficile \t[Profondeur 9]\n");
	printf("\t[-1] Retour\n\n");
	printf("Quel niveau voulez vous ? ");

}

void msg_IA_vs_IA() {
	printf("\t\t\t  ---------------------------------\n\t\t\t| Ordinateur contre Ordinateur |\n\t\t\t  ---------------------------------\n\n");
}

void choix_tcp() {
	printf("Choissez le type d'inscription au serveur :\n");
	printf("\t[1] - PS\n");
	printf("\t[2] - PS IA\n");
	printf("\t[3] - TOURNAMENT\n");
	#if DEBUG
	printf("\t[4] - TEST\n");
	#endif
	printf("\t[-1] Retour\n\n");
}

void choix_serv() {
	printf("Choissez le serveur :\n");
	printf("\t[1] - Serveur Aurélien\n");
	printf("\t[2] - Serveur Anas hakim\n");
	printf("\t[-1] Retour\n\n");
}
