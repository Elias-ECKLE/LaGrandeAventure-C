#ifndef VUE_H_INCLUDED
#define VUE_H_INCLUDED
#include "struct_const.h"



extern void gotoxy(short x, short y);
extern void Color(int couleurDuTexte,int couleurDeFond);

extern void MsgConsignes_Jeu(state etatJeu);
extern void Init_MapVide(int grille[HAUTEUR_Map][LARGEUR_Map]);
extern void Maj_AffichMap(int grillePersonnages[][LARGEUR_Map],char delimtMap, state etatJeu, pisteur tabPisteur[], monster monstre);
extern void AffichTexte(texteNb nbTexte, pisteur tab[], int indexTab, int nbCase, int nbFraicheurTrace, int vieMonstre);
extern void majElement_SurMap(int x, int y, char car,int decalageY_Goto,char carType_PtExclm, char carType_PtInterog);

extern void SDL_Initialisation(int window_width, int window_height);
extern void SDL_InitImg();
extern void SDL_AffichMap(int grillePersonnages[][LARGEUR_Map],monster monstre);

#endif // VUE_H_INCLUDED
