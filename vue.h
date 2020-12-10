#ifndef VUE_H_INCLUDED
#define VUE_H_INCLUDED
#include "struct_const.h"



extern void gotoxy(short x, short y);

extern void MsgConsignes_Jeu(state etatJeu);
extern void Init_MapVide(int grille[HAUTEUR_Map][LARGEUR_Map]);
extern void Maj_AffichMap(int grille[][LARGEUR_Map],char delimtMap);
extern void AffichTexte(texteNb nbTexte, pisteur tab[], int indexTab);


#endif // VUE_H_INCLUDED
