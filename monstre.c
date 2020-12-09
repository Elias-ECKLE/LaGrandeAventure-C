#include "define.h"


void CheckCaseVoisine_Monstre(){
//BUT:checker si pisteur ou non sur les 8 cases lors de l'init, et sur les 4 cases lors de déplacement
}



//INIT Monstre________________________________________

//Position de départ MONSTRE--------------------------
void Pos_DepartMonstre(){
//BUT:positioner ke monstre sur une case différente et non voisine de celle des pisteurs
//ENTREE:
//SORTIE:
}





//JEU________________________________________________


//Traces du monstre à ajouter et enlever progressivement--------------------------
void AjoutTrace_Monstre(){
//BUT: on ajoute le nb 16 à l'ancienne position du monstre
}

void EffacementTraces_Monstre(){
//BUT:enlever à chaque tour un pt de trace jusqu'à diparaitre quand la valeur 0 atteinte
}


//manger pisteur :--------------------------------------------------------------------
void MangerPisteur(){
//BUT:Si case avec pisteir, il le tue
}

//Déplacement du monstre après première position---------------------------------------
void Deplcmt_Monstre(){
//BUT:Le monstre se déplace. Pour cela il checke si pas pisteur voisin,puis pose trace(16) sur ancienne case : appel fcts
}


void MonstreTouche(){
//BUT: le monstre est touché, alors il perd un pt de vie, et indication dernier endroit séjourné pendant 4 tours de jeu
}
