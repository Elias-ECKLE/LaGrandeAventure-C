#ifndef PISTEURS_H_INCLUDED
#define PISTEURS_H_INCLUDED
#include "struct_const.h"


extern void Init_Saisie_NBPisteurs(pisteur tab[], int *pNbPisteursChoisi, int min, int max, char carAttente, char carVerif, char carPisteur, int maxLettres);
extern void Saisie_posPisteurs(int grillePersonnages[][LARGEUR_Map], pisteur tab[],int nbPisteursChoisi);


#endif // PISTEURS_H_INCLUDED
