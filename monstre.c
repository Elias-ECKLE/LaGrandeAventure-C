#include "define.h"


void CheckCaseVoisine_Monstre(){
//BUT:checker si pisteur ou non sur les 8 cases lors de l'init, et sur les 4 cases lors de d�placement
}



//INIT Monstre________________________________________

//Position de d�part MONSTRE--------------------------
void Pos_DepartMonstre(){
//BUT:positioner ke monstre sur une case diff�rente et non voisine de celle des pisteurs
//ENTREE:
//SORTIE:
}





//JEU________________________________________________


//Traces du monstre � ajouter et enlever progressivement--------------------------
void AjoutTrace_Monstre(){
//BUT: on ajoute le nb 16 � l'ancienne position du monstre
}

void EffacementTraces_Monstre(){
//BUT:enlever � chaque tour un pt de trace jusqu'� diparaitre quand la valeur 0 atteinte
}


//manger pisteur :--------------------------------------------------------------------
void MangerPisteur(){
//BUT:Si case avec pisteir, il le tue
}

//D�placement du monstre apr�s premi�re position---------------------------------------
void Deplcmt_Monstre(){
//BUT:Le monstre se d�place. Pour cela il checke si pas pisteur voisin,puis pose trace(16) sur ancienne case : appel fcts
}


void MonstreTouche(){
//BUT: le monstre est touch�, alors il perd un pt de vie, et indication dernier endroit s�journ� pendant 4 tours de jeu
}
