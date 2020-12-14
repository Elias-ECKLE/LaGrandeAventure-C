#ifndef MONSTRE_H_INCLUDED
#define MONSTRE_H_INCLUDED
#include "struct_const.h"

extern void Check8CasesVoisine_Monstre(int grillePerso[][LARGEUR_Map], int nbPist, int x, int y, booleanPerso *pcaseNonPisteur);
extern void Init_Pos_DepartMonstre(int grillePersonnage[][LARGEUR_Map],int grilleTraces, monster *monstre, pisteur tabPisteur[], int nbPisteurChoisi, int monstrePV, int nouvelleTrace, int retireTrace, int nbToursPos, char carBlessure, char carMonstre);
extern void AjoutTrace_Monstre(monster monstre, int grilleTraces[][LARGEUR_Map]);
extern void EffacementTraces_Monstre(int grilleTraces[][LARGEUR_Map], int retire);

extern void PisteurEst_CaseMonstre(int grillePersos[][LARGEUR_Map], monster monstre, int nbDegatMonstre, pisteur tabPisteur[],int nbPisteursChoisi);
extern void MangerPisteur(int grillePersos[][LARGEUR_Map], pisteur tabPisteur[], int indexTab,monster monstre, int nbDegatMonstre);

extern void Check4CasesVoisine_Monstre(int grillePerso[][LARGEUR_Map],int grilleTraces_Pisteurs[][LARGEUR_Map], historicTrace_Pisteur tabHistoricPist[], booleanPerso *pisteurEstLa,booleanPerso *traceEstLa,int nbTraceMax, int x,int y,int *pX, int *pY);
extern void Deplcmt_Monstre(int grillePersos[][LARGEUR_Map], int grilleTracesPist[][LARGEUR_Map], int tabPisteurs[], int nbPisteursChoisi, int nbTracesMax,int nbDegats_Monstre, monster monstre, monster *pMonstre);

#endif // MONSTRE_H_INCLUDED
