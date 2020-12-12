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





void Maj_AffichMap(int grillePersonnages[][LARGEUR_Map],char delimtMap, state etatJeu, pisteur tabPisteur[], monster monstre){
//BUT:Affiche les caract�res correspondants aux nbs stock�s dans le tab. A terme affiche la SDL correspondante aux nbs
//ENTREE:
//SORTIE:

//caracts d�limitation map

    int i;
    int j;
    caseNb nbCase;

    //trac� horizontal haut
    for(i=0;i<LARGEUR_Map+1;i++){
        gotoxy(i,0);
        printf("%c",delimtMap);
    }

    //trac� horizontal bas
    for(i=0;i<LARGEUR_Map+1;i++){
        gotoxy(i,HAUTEUR_Map+1);
        printf("%c",delimtMap);
    }

    //trac� vetical gauche
    for(i=0;i<HAUTEUR_Map+1;i++){
        gotoxy(0,i);
        printf("%c",delimtMap);
    }

    //trac� vertical droit
    for(i=0;i<HAUTEUR_Map+1;i++){
        gotoxy(LARGEUR_Map+1,i);
        printf("%c",delimtMap);
    }

    gotoxy(0,0);
    for(i=0;i<HAUTEUR_Map;i++){

        for(j=0;j<LARGEUR_Map;j++){


        //caracts pisteurs
            nbCase=nbPisteur;
            if(grillePersonnages[i][j]==nbCase){

                gotoxy(i,j);
                if(etatJeu==pisteurs_VerifVoisine){

                    printf("%c",tabPisteur[0].car_Verifie);
                }
                else if(etatJeu==dplmtPisteurs){

                    printf("%c",tabPisteur[0].car_EnAttente);
                }
                else{
                    printf("%c",tabPisteur[0].car_Pisteur);
                }
            }

        //caracts monstre
            nbCase=nbMonstre;
            if(grillePersonnages[i][j]==nbCase){

                gotoxy(i,j);
                printf("%c",monstre.car_Monstre);
            }


        }

        printf("\n");
    }





}







//AFFICHAGE TEXTE JEU__________________________________________________________
void MsgConsignes_Jeu(state etatJeu){
//BUT:Afficher message d'accueil, r�gles expliqu�es & qui a gagn�/perdu
//ENTREE: �tat du jeu pour voir quelle consigne �noncer
//SORTIE: RAS

    system("cls");

    if(etatJeu==debut){
         //message d�but :
        printf("Bienvenue dans le jeu de La Grande Aventure. Arriverez-vous a eliminer le terrible monstre qui rode dans les parages.\n");
        printf("Bon courage, vous en aurez bien besoin. Et tachez de ne pas mourir");
    }
    else if(etatJeu==debut_SaisieCoords){

        //message d�but saisi de coord
        printf("Avant de commencer la partie, vous devez positioner chacun de vos pisteurs en saisissant une coordoonee X et Y ci-apres\n");
    }
    else if(etatJeu==pisteurs_VerifVoisine){
        //moment ou les pisteus disent ce qu'ils voient dans les cases voisines
        printf("\n\nIl est l heure du compte rendu des pisteurs : \n");
    }
    else if(etatJeu==fin){

    }

}



void AffichTexte(texteNb nbTexte, pisteur tab[], int indexTab, int nbCase, int nbFraicheurTrace, int vieMonstre){
//BUT : afficher tous les printf et � terme font SDL2 ici pour mieux s'y retrouver
    //Chaque num coorespond � un message diff�rent � afficher



        //texte: void Saisie_NBPisteurs();
    if(nbTexte==nbSaisie_TPisteur){

        printf("\n\nCombien de pisteurs voulez-vous ? Vous pouvez choisir de 1 a 10 au maximum : ");
    }


   //--------------------------------------------------------------

        //texte: void Saisie_posPisteursX();
    if(nbTexte==nbPos_TPisteurX){

        printf("\nVeuillez entrer la coordoonee x du %s (entre 1 & 14): ",tab[indexTab].nom);
    }

        //texte: void Saisie_posPisteursY();
    if(nbTexte==nbPos_TPisteurY){
        printf("\nVeuillez entrer la coordoonee y du %s (entre 1 & 29): ",tab[indexTab].nom);
    }

    //-------------------------------------------------------------

        //texte: void Pos_DepartMonstre();
    if(nbTexte==nbPos_TDepartMonstre){
        printf("Le monstre est entre dans l'arene");
    }


    //--------------------------------------------------------------

        //void Tirer_SurMonstre();
    if(nbTexte==nbTirer_TMonstre){

        printf(" (t pour tirer /r pour ne rien faire) : ");
    }
    if(nbTexte==nbTirLoupe_TMonstre){
        printf("\nVous avez loupe votre tir");
    }
    if(nbTexte==nbTirReussi_TMonstre){
        printf("Vous avez reussi votre tir. Il reste %d PV au monstre",vieMonstre);

    }

    //-------------------------------------------------------
        //texte : void CheckCaseVoisine_Pisteur();

            //monstre est dans une case voisine
    if(nbTexte==nbMonstre_TCaseVoisine){
        printf("\n\n %s",tab[indexTab].nom);
        printf(": Je le vois");
    }
            //il y a des traces autour
    if(nbTexte==nbTraces_TCaseVoisine){
        printf("\n\n %s",tab[indexTab].nom);
        printf(": traces en %d de valeur %d",nbCase,nbFraicheurTrace);
    }
            //il n'y a rien
    if(nbTexte==nbRAS_TCaseVoisine){
        printf("\n\n %s",tab[indexTab].nom);
        printf(": Rien en 1,2,3,4,5,6,7,8");
    }
    //-------------------------------------------------------



    //------------------------------------------------------
        //texte : vvoid ChoixDistance();
    if(nbTexte==nbChoix_TDistance){

    }

        //texte  :  void ChoixDirection
    if(nbTexte==nbChoix_TDirection){

    }

        //texte ; void Deplcmt_Pisteur()
    if(nbTexte==nbDplmt_TPisteur){

    }
    //------------------------------------------------------



        //texte:void MangerPisteur();
    if(nbTexte==nbManger_TPisteur){


    }

        //texte:void Deplcmt_Monstre();
    if(nbTexte==nbDplmt_TMonstre){

    }

        //texte void MonstreTouche(
    if(nbTexte==nbMonstre_TTouche){

    }




    //-------------------------------------------------------
        //si il y a une erreur dans la saisie d'une valeur par l'utilisateur ou autre m�me, afficher ce msg
    if(nbTexte==nb_TErreur){

        printf("\nErreur, veuillez reessayer : ");
    }














}
