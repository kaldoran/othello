//----------------------------------------------------------
// AUTEUR : REYNAUD Nicolas                                 |
// FICHIER : gestion_fichier.h                 		     |
// DATE : 13/03/14					                    |
//                                                          |
// - Prototypes des fonctions de gestion_fichier.c          |
//                                                          |
// - Fonction d'affichage des regles                        |
//----------------------------------------------------------




#ifndef GESTION_FICHIER_H
#define GESTION_FICHIER_H

#include "global.h"

#define ADRESSE_REGLES "BDD/regles.txt" /* adresse fichier texte des regles */

/* Affiche les regles presentent dans le fichiers regles.txt */
void afficher_regles();

#endif /* GESTION_FICHIER_H inclu */
