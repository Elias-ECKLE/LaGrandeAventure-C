#ifndef PISTEURS_H_INCLUDED
#define PISTEURS_H_INCLUDED
#include "struct_const.h"


extern void Init_Saisie_NBPisteurs(pisteur tab[], int *pNbPisteursChoisi, int min, int max, char carAttente, char carVerif, char carPisteur, int maxLettres);
extern void Saisie_posPisteurs(int grillePersonnages[][LARGEUR_Map], pisteur tab[],int nbPisteursChoisi);
extern void CheckCaseVoisine_Pisteur(int grillePerso[][LARGEUR_Map], int grilleTraces[][LARGEUR_Map], pisteur tabPisteur[], int nbPisteurs, monster *monstre,int chanceTir);
extern int Tirer_SurMonstre(int vieMonstre,int chanceTir);

#endif // PISTEURS_H_INCLUDED
