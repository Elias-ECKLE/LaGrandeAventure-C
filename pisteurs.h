#ifndef PISTEURS_H_INCLUDED
#define PISTEURS_H_INCLUDED
#include "struct_const.h"


extern void Init_Saisie_NBPisteurs(pisteur tab[], int *pNbPisteursChoisi, int min, int max, char carAttente, char carVerif, char carPisteur, int maxLettres,int nbPV,int traceFraiche,int traceEnMoins);
extern void Saisie_posPisteurs(int grillePersonnages[][LARGEUR_Map],int grilleTraces_Pisteur[][LARGEUR_Map], pisteur tab[],int nbPisteursChoisi,char carDelimt, monster monstre);
extern void CheckCaseVoisine_Pisteur(int grillePerso[][LARGEUR_Map], int grilleTraces[][LARGEUR_Map], pisteur tabPisteur[], int nbPisteurs, monster *monstre,int chanceTir,state etatJeu, int nbDegats_Pisteur,char delimtMap);
extern int Tirer_SurMonstre(int vieMonstre,int chanceTir, int nbDegats_Pisteur, monster *monstre);

extern int ChoixDirection(int grillePersos[][LARGEUR_Map], pisteur tabPisteur[], int indexTab,int x,int y);
extern int ChoixDistance(int grillePersos[][LARGEUR_Map], pisteur tabPisteur[], int indexTab,int x,int y,int maxDistance,int nb_Direction);
extern void Deplcmt_Pisteur(int grillePersos[][LARGEUR_Map], int grillesTraces_Pisteur[][LARGEUR_Map], state etatJeu, pisteur tabPisteur[],int nbPisteurs, int maxDistance, char carDelimt,monster monstre,int nbDegatsMonstre);

extern void PisteursRestant_EnVie(pisteur tabPisteur[],int nbPisteursChoisi, booleanPerso *pisteursSontEnVie);

#endif // PISTEURS_H_INCLUDED
