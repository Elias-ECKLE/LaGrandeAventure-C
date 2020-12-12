#ifndef MONSTRE_H_INCLUDED
#define MONSTRE_H_INCLUDED
#include "struct_const.h"

extern void Init_Pos_DepartMonstre(int grillePersonnage[][LARGEUR_Map],int grilleTraces, monster *monstre, pisteur tabPisteur[], int nbPisteurChoisi, int monstrePV, int nouvelleTrace, int retireTrace, int nbToursPos, char carBlessure, char carMonstre);
extern void AjoutTrace_Monstre(monster monstre, int grilleTraces[][LARGEUR_Map]);
extern void EffacementTraces_Monstre(int grilleTraces[][LARGEUR_Map], int retire);

#endif // MONSTRE_H_INCLUDED
