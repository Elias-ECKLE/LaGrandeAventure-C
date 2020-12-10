#include "struct_const.h"
#include "vue.h"


void gotoxy(short x, short y)
{
	HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Pos={x,y};
	SetConsoleCursorPosition(hConsole,Pos);
}







//INIT MAP____________________________________________________________________

void Init_MapVide(int grille[][LARGEUR_Map]){
//BUT:Initialiser la grille
//ENTREE:grille, nb � init
//SORTIE:grille init

    int i;
    int j;
    caseNb nbCase=nbInit;


    for(i=0;i<HAUTEUR_Map;i++){

        for(j=0;j<LARGEUR_Map;j++){

            grille[i][j]=nbInit;
        }
    }
}





void Maj_AffichMap(int grille[][LARGEUR_Map],char delimtMap){
//BUT:Affiche les caract�res correspondants aux nbs stock�s dans le tab. A terme affiche la SDL correspondante aux nbs
//ENTREE:
//SORTIE:

//caracts d�limitation map

    int i;
    int j;

    //trac� horizontal haut
    for(j=0;j<LARGEUR_Map+1;j++){
        gotoxy(j,0);
        printf("%c",delimtMap);
    }

    //trac� horizontal bas
    for(j=0;j<LARGEUR_Map+1;j++){
        gotoxy(j,HAUTEUR_Map+1);
        printf("%c",delimtMap);
    }

    //trac� vetical gauche
    for(j=0;j<HAUTEUR_Map+1;j++){
        gotoxy(0,j);
        printf("%c",delimtMap);
    }

    //trac� vertical droit
    for(j=0;j<HAUTEUR_Map+1;j++){
        gotoxy(LARGEUR_Map+1,j);
        printf("%c",delimtMap);
    }

//caracts pisteurs

//caracts monstre

}







//AFFICHAGE TEXTE JEU__________________________________________________________
void MsgDebut_FinJeu(state etatJeu){
//BUT:Afficher message d'accueil, r�gles expliqu�es & qui a gagn�/perdu


    if(etatJeu==debut){
         //message d�but :
        printf("Bienvenue dans le jeu de La Grande Aventure. Arriverez-vous a eliminer le terrible monstre qui rode dans les parages.\n");
        printf("Bon courage, vous en aurez bien besoin. Et tachez de ne pas mourir");
    }
    else if(etatJeu==debut_SaisieCoords){

        //message d�but saisi de coord
        printf("Avant de commencer la partie, vous devez positioner chacun de vos pisteurs en saissisant une coordoonee X et Y ci-apr�s :\n");
    }
    else if(etatJeu==fin){

    }

}



void AffichTexte(texteNb nbTexte){
//BUT : afficher tous les printf et � terme font SDL2 ici pour mieux s'y retrouver
    //Chaque num coorespond � un message diff�rent � afficher



        //texte: void Saisie_NBPisteurs();
    if(nbTexte==nbSaisie_TPisteur){

        printf("\nCombien de pisteurs voulez-vous ? Vous pouvez choisir de 1 a 10 au maximum : ");
    }


        //texte: void Saisie_posPisteursX();
    if(nbTexte==nbPos_TPisteurX){

        printf("\nVeuillez entrer la coordoonee x: ");
    }

        //texte: void Saisie_posPisteursY();
    if(nbTexte==nbPos_TPisteurY){
        printf("\nVeuillez entrer la coordoonee y: ");
    }

        //texte: void Pos_DepartMonstre();
    if(nbTexte==nbPos_TDepartMonstre){

    }

        //void Tirer_SurMonstre();
    if(nbTexte==nbTirer_TMonstre){

    }

        //texte : void CheckCaseVoisine_Pisteur();
    if(nbTexte==nbCheckCasVoisine_TPisteur){

    }

        //texte : vvoid ChoixDistance();
    if(nbTexte==nbChoix_TDistance){

    }

        //texte  :  void ChoixDirection
    if(nbTexte==nbChoix_TDirection){

    }

        //texte ; void Deplcmt_Pisteur()
    if(nbTexte==nbDplmt_TPisteur){

    }

        //texte:void MangerPisteur();
    if(nbTexte==nbManger_TPisteur){


    }

        //texte:void Deplcmt_Monstre();
    if(nbTexte==nbDplmt_TMonstre){

    }

        //texte void MonstreTouche(
    if(nbTexte==nbMonstre_TTouche){

    }

        //si il y a une erreur dans la saisie d'une valeur par l'utilisateur ou autre m�me, afficher ce msg
    if(nbTexte==nb_TErreur){

        printf("\nErreur, veuillez reessayer : ");
    }














}
