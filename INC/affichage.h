//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : affiche.h                                      |
// DATE : 13/03/14                                          |
//                                                          |
// - Prototypes des fonctions de affiche.c                  |
// - Fonction d'affichage du titre d'accueil                |
// - Fonction d'affichage du menu                           |
// - Fonction d'affichage du sous menu humain               |
// - Fonction d'affichage du sous menu pour la difficulté   |
//   De l'IA                                                |
//----------------------------------------------------------


#ifndef AFFICHE_H
#define AFFICHE_H

#include "global.h"

/* Affiche le menu principal */
void menu_principal();

/* Affiche l'encadrer Humain contre Humain */
void msg_H_vs_H();

/* Affiche l'encadrer Ordinateur contre humain */ 
void msg_IA_vs_H();

/* Affiche le menu de l'ordinateur contre l'humain */ 
void menu_IA_vs_H();

/* Affiche l'encadrer Ordinateur contre Ordinateur */ 
void msg_IA_vs_IA();

/* Affiche les choix possibles pour une partie en réseau */
void choix_tcp();

/* Affiche les choix possible pour les serveur */
void choix_serv();


#endif /* AFFICHAGE_H inclu */
