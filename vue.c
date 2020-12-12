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
//ENTREE:grille, nb à init
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
//BUT:Affiche les caractères correspondants aux nbs stockés dans le tab. A terme affiche la SDL correspondante aux nbs
//ENTREE:
//SORTIE:

//caracts délimitation map

    system("cls");

    int i;
    int j;
    caseNb nbCase;

    //tracé horizontal haut
    for(i=0;i<LARGEUR_Map+1;i++){
        gotoxy(i,0);
        printf("%c",delimtMap);
    }

    //tracé horizontal bas
    for(i=0;i<LARGEUR_Map+1;i++){
        gotoxy(i,HAUTEUR_Map+1);
        printf("%c",delimtMap);
    }

    //tracé vetical gauche
    for(i=0;i<HAUTEUR_Map+1;i++){
        gotoxy(0,i);
        printf("%c",delimtMap);
    }

    //tracé vertical droit
    for(i=0;i<HAUTEUR_Map+1;i++){
        gotoxy(LARGEUR_Map+1,i);
        printf("%c",delimtMap);
    }
    //--------------------------------------------

    gotoxy(0,0);
    for(i=0;i<HAUTEUR_Map;i++){

        for(j=0;j<LARGEUR_Map;j++){


        //caracts pisteurs
            nbCase=nbPisteur;
            if(grillePersonnages[i][j]==nbCase){

                gotoxy(j+1,i+1);
                printf("%c",tabPisteur[0].car_Pisteur);
            }

        //caracts monstre
            nbCase=nbMonstre;
            if(grillePersonnages[i][j]==nbCase){

                gotoxy(j+1,i+1);
                printf("%c",monstre.car_Monstre);
            }


        }

        printf("\n");
    }

    printf("\n\n");





}

void majElement_SurMap(int x, int y, char car,int decalageY_Goto){
//BUT: mettre à jour l'affichage d'un élément en particulier et non toute la map (éviter de la reécrire en entier) ex: point d'exclamation pisteur

    gotoxy(y+1,x+1);
    printf("%c\n",car);
    //on remet un goto en dessous du tableau, sinon va écrire par dessus le tabl
    gotoxy(0,decalageY_Goto);
}







//AFFICHAGE TEXTE JEU__________________________________________________________
void MsgConsignes_Jeu(state etatJeu){
//BUT:Afficher message d'accueil, règles expliquées & qui a gagné/perdu
//ENTREE: état du jeu pour voir quelle consigne énoncer
//SORTIE: RAS



    if(etatJeu==debut){
         //message début :
        printf("Bienvenue dans le jeu de La Grande Aventure. Arriverez-vous a eliminer le terrible monstre qui rode dans les parages.\n");
        printf("Bon courage, vous en aurez bien besoin. Et tachez de ne pas mourir");
    }
    else if(etatJeu==debut_SaisieCoords){
        //message début saisi de coord
        printf("Avant de commencer la partie, vous devez positioner chacun de vos pisteurs en saisissant une coordoonee X et Y ci-apres\n");
    }
    else if(etatJeu==pisteurs_VerifVoisine){
        //moment ou les pisteus disent ce qu'ils voient dans les cases voisines
        printf("\nIl est l heure du compte rendu des pisteurs : \n\n");
    }
    else if(etatJeu==dplmtPisteurs){
        printf("\nLe deplacement des pisteurs commence  : \n\n");
    }
    else if(etatJeu==fin){

    }

}



void AffichTexte(texteNb nbTexte, pisteur tab[], int indexTab, int nbCase, int nbFraicheurTrace, int vieMonstre){
//BUT : afficher tous les printf et à terme font SDL2 ici pour mieux s'y retrouver
    //Chaque num coorespond à un message différent à afficher



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
    if(nbTexte==erreur_CoordsIdentiques){
        printf("\nCes coordonnees sont deja prises par un autre pisteur : ");
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
        printf("\nVous avez loupe votre tir\n");
    }
    if(nbTexte==nbTirReussi_TMonstre){
        printf("Vous avez reussi votre tir. Il reste %d PV au monstre\n",vieMonstre);

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
        printf("\n %s",tab[indexTab].nom);
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
        printf("Quelle distance pour le %s (entre 1 et 4 au maximum) ? ",tab[indexTab].nom);
    }
    if(nbTexte==nbChoix_Erreur_TDistance){
        printf("Impossible de valider la distance choisie. Il semble qu'un obstacle empeche la validation");
    }

        //texte  :  void ChoixDirection
    if(nbTexte==nbChoix_TDirection){

        printf("Quelle direction pour le %s (1=haut/ 2=droite/ 3=bas/ 4=gauche/): ",tab[indexTab].nom);
    }
    if(nbTexte==nbChoix_Erreur_TDirection){
        printf("Impossible de valider la direction choisie. Il semble qu'un obstacle empeche la validation");
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
        //si il y a une erreur dans la saisie d'une valeur par l'utilisateur ou autre même, afficher ce msg
    if(nbTexte==nb_TErreur){

        printf("\nErreur, veuillez reessayer : ");
    }














}
