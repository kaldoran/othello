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

#include <netinet/in.h>
#include <string.h>

#include "struct_config.h"
#include "global.h"


#define TAILLE_LIGNE 512
#define ADRESSE_REGLES "BDD/regles.txt" /* adresse fichier texte des regles */
#define ADRESSE_CONFIG "BDD/config.txt" /* adresse fichier texte de la configuration */

/* Affiche les regles presentent dans le fichiers regles.txt */
void afficher_regles();

/* Alloue la structure configuration */
Configuration *nouvelle_configuration();

/* Charge la configuration depuis un fichier */
void charger_configuration(Configuration *config);

#endif /* GESTION_FICHIER_H inclu */
