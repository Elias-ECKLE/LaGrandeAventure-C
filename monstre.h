#ifndef MONSTRE_H_INCLUDED
#define MONSTRE_H_INCLUDED
#include "struct_const.h"

extern void Init_Pos_DepartMonstre(int grillePersonnage[][LARGEUR_Map],int grilleTraces, monster *monstre, pisteur tabPisteur[], int nbPisteurChoisi, int monstrePV, int nouvelleTrace, int retireTrace, int nbToursPos, char carBlessure, char carMonstre);
extern void AjoutTrace_Monstre(monster monstre, int grilleTraces[][LARGEUR_Map]);
extern void EffacementTraces_Monstre(int grilleTraces[][LARGEUR_Map], int retire);

extern void PisteurEst_CaseMonstre(int grillePersos[][LARGEUR_Map], monster monstre, int nbDegatMonstre, pisteur tabPisteur[],int nbPisteursChoisi);
extern void MangerPisteur(int grillePersos[][LARGEUR_Map], pisteur tabPisteur[], int indexTab,monster monstre, int nbDegatMonstre);

#endif // MONSTRE_H_INCLUDED
