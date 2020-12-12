#ifndef PISTEURS_H_INCLUDED
#define PISTEURS_H_INCLUDED
#include "struct_const.h"


extern void Init_Saisie_NBPisteurs(pisteur tab[], int *pNbPisteursChoisi, int min, int max, char carAttente, char carVerif, char carPisteur, int maxLettres,int nbPV);
extern void Saisie_posPisteurs(int grillePersonnages[][LARGEUR_Map], pisteur tab[],int nbPisteursChoisi);
extern void CheckCaseVoisine_Pisteur(int grillePerso[][LARGEUR_Map], int grilleTraces[][LARGEUR_Map], pisteur tabPisteur[], int nbPisteurs, monster *monstre,int chanceTir,state etatJeu);
extern int Tirer_SurMonstre(int vieMonstre,int chanceTir);

extern void Deplcmt_Pisteur(int grillePersos[][LARGEUR_Map],state etatJeu, pisteur tabPisteur[],int nbPisteurs, int maxDistance, char carDelimt,monster monstre);
extern int ChoixDirection(int grillePersos[][LARGEUR_Map], pisteur tabPisteur[], int indexTab,int x,int y);
extern int ChoixDistance(int grillePersos[][LARGEUR_Map], pisteur tabPisteur[], int indexTab,int x,int y,int maxDistance,int nb_Direction);
#endif // PISTEURS_H_INCLUDED
