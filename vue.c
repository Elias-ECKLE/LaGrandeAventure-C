#include "struct_const.h"
#include "vue.h"
/*Code réalisé par Elias Ecklé*/


void gotoxy(short x, short y)
{
	HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Pos={x,y};
	SetConsoleCursorPosition(hConsole,Pos);
}

//color :
/*
0 : Noir
1 : Bleu foncé
2 : Vert foncé
3 : Turquoise
4 : Rouge foncé
5 : Violet
6 : Vert caca d'oie
7 : Gris clair
8 : Gris foncé
9 : Bleu fluo
10 : Vert fluo
11 : Turquoise
12 : Rouge fluo
13 : Violet 2
14 : Jaune
15 : Blanc
*/
void Color(int couleurDuTexte,int couleurDeFond) // fonction d'affichage de couleurs
{
        HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}


//AFFICHAGE EN TEXTUEL______________________________________________________________________________

        //INIT MAP-------------------------------------------------------------------------

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

    //affichage Map SDL:
    //SDL_AffichMap(grillePersonnages,monstre);

//caracts délimitation map

    system("cls");

    int i;
    int j;
    caseNb nbCase;

    Color(9,0);
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
    Color(15,0);
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
            if((grillePersonnages[i][j]==nbCase)&&(monstre.debugMonstre==vrai)){

                gotoxy(j+1,i+1);
                printf("%c",monstre.car_Monstre);
            }

        //caracts blessure monstre
            nbCase=nbpointPos_Monstre;
            if(grillePersonnages[i][j]==nbCase){
                gotoxy(j+1,i+1);
                printf("%c",monstre.ptBlessure);

            }

        }

        printf("\n");
    }

    printf("\n\n");



}

void majElement_SurMap(int x, int y, char car,int decalageY_Goto,char carType_PtExclm, char carType_PtInterog){
//BUT: mettre à jour l'affichage d'un élément en particulier et non toute la map (éviter de la reécrire en entier) ex: point d'exclamation pisteur

    gotoxy(y+1,x+1);

    if(car==carType_PtExclm){
        Color(2,0); //green
    }
    if(car==carType_PtInterog){
        Color(5,0); //blue
    }


    printf("%c\n",car);
    //on remet un goto en dessous du tableau, sinon va écrire par dessus le tabl
    printf("\n");
    gotoxy(0,decalageY_Goto);


    //couleur par défaut :
    Color(15,0);
}

        //AFFICHAGE TEXTE JEU---------------------------------------------------------------
void MsgConsignes_Jeu(state etatJeu){
//BUT:Afficher message d'accueil, règles expliquées & qui a gagné/perdu
//ENTREE: état du jeu pour voir quelle consigne énoncer
//SORTIE: RAS



    if(etatJeu==debut){
         //message début :
        printf("Bienvenue dans le jeu de La Grande Aventure. Arriverez-vous a eliminer le terrible monstre qui rode dans les parages.\n");
        printf("Bon courage, vous en aurez bien besoin. Et tachez de ne pas mourir...");
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
    else if(etatJeu==dplmtMonstre){
        printf("\nC est au tour du monstre de se deplacer. Attention a ne pas tomber sur la meme case que ce dernier sous peine d'en faire qu une bouchee");
    }
    else if(etatJeu==rebouclePartie){
        printf("\nLe monstre a fini son deplacement. Ni la totalite des pisteurs, ni le monstre ne sont morts, la partie alors continue");
    }
    else if(etatJeu==victoirePisteurs){
        system("cls");
        printf("La partie est terminee. Les pisteurs ont reussis a tuer le monstre");
    }
    else if(etatJeu==victoireMonstre){
        system("cls");
        printf("La partie est terminee ! Le monstre a mange tous les pisteurs");
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
        printf("Vous avez loupe votre tir\n");
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
        printf("\n\nMalheureusement le monstre se trouve sur la meme case que l un de vos pisteurs. Le %s est donc mange par la bete, il ne reviendra pas de ses entrailles...",tab[indexTab].nom);


    }

        //texte:void Deplcmt_Monstre();
    if(nbTexte==nbDplmt_TMonstre){

    }

        //texte void MonstreTouche(
    if(nbTexte==nbMonstre_TTouche){

    }



    //mode debug---------------------------------------------
    if(nbTexte==nbDebug_TMonstre){
        printf("\nVoulez vous entrez dans le mode debug. Celui-ci permettra d'afficher le monstre (o:oui/n:non): ");

    }

    //-------------------------------------------------------
        //si il y a une erreur dans la saisie d'une valeur par l'utilisateur ou autre même, afficher ce msg
    if(nbTexte==nb_TErreur){

        printf("\nErreur, veuillez reessayer : ");
    }


}



//AFFICHAGE EN SDL__________________________________________________________________________________

    //Init SDL---------------------------------------------------------------
void SDL_Initialisation(int window_width, int window_height){

    //INIT SDL________________________________________________________________________________________________________________
    if(SDL_Init(SDL_INIT_EVERYTHING)!=0){

        SDL_Log("Unable to initialize : %s",SDL_GetError());
        return 1; //il y a un probleme on retourne 1
    }
    else{ //creation de la fenetre : afficher fenetre graphique : 0,0 position coin gauche, ensuite taille et enfin l'afficher

        pWindow=SDL_CreateWindow("Map du jeu graphique",10,50,window_width,window_height,SDL_WINDOW_OPENGL);
        if(pWindow){ //creation du rendu : si la fenetre est bien crée alors
            pRenderer=SDL_CreateRenderer(pWindow,-1,SDL_RENDERER_PRESENTVSYNC);
        }
    }

}

void SDL_InitImg(){
        //initialisation des flags (comme au dessus) avec les img
    int flags=IMG_INIT_JPG|IMG_INIT_PNG;
        int initted=IMG_Init(flags);
        if((initted&flags)!=flags){
             SDL_Log("IMG_Init:Failed to init required jpg and png support !\n");
             SDL_Log("IMG_Init: %s\n", IMG_GetError());
             return 1;
        }
}

    //maj affichage map SDL---------------------------------------------------

void SDL_AffichMap(int grillePersonnages[][LARGEUR_Map],monster monstre){

    int i;
    int j;
    caseNb nbCase;
    char imageEtoile[]=SDL_IMAGE_Etoile;
    char imagePpisteur[]=SDL_IMAGE_Pisteur;
    char imageMonstre[]=SDL_IMAGE_Monstre;
    char imagePtBlessure[]=SDL_IMAGE_PtBlessure;
    int tailleImage=TAILLE_IMAGE;

    SDL_Surface *pSurfaceEtoile=NULL;
    SDL_Surface *pSurfaceP_Pisteur=NULL;
    SDL_Surface *pSurfaceMonstre=NULL;
    SDL_Surface *pSurfacePtBlessure=NULL;

    SDL_Texture *pTextureEtoile=NULL;
    SDL_Texture *pTextureP_Pisteur=NULL;
    SDL_Texture *pTextureMonstre=NULL;
    SDL_Texture *pTexturePtBlessure=NULL;



  //INIT ---------------------------------------------------
    //LOad images :
    pSurfaceEtoile = IMG_Load(imageEtoile);
    pSurfaceP_Pisteur= IMG_Load(imagePpisteur);
    pSurfaceMonstre=IMG_Load(imageMonstre);
    pSurfacePtBlessure= IMG_Load(imagePtBlessure);

    //Si pas de reference
    if((!pSurfaceEtoile)||(!pSurfaceP_Pisteur)||(!pSurfaceMonstre)||(!pSurfacePtBlessure)){
            SDL_Log("Unable to set surface: %s", SDL_GetError());
            return 1;
    }
    else{
        pTextureEtoile=SDL_CreateTextureFromSurface(pRenderer,pSurfaceEtoile);
        pTextureP_Pisteur=SDL_CreateTextureFromSurface(pRenderer,pSurfaceP_Pisteur);
        pTextureMonstre=SDL_CreateTextureFromSurface(pRenderer,pSurfaceMonstre);
        pTexturePtBlessure=SDL_CreateTextureFromSurface(pRenderer,pSurfacePtBlessure);

        SDL_FreeSurface(pSurfaceEtoile);
        SDL_FreeSurface(pSurfaceP_Pisteur);
        SDL_FreeSurface(pSurfaceMonstre);
        SDL_FreeSurface(pSurfacePtBlessure);


        if((!pTextureEtoile)||(!pTextureP_Pisteur)||(!pTextureMonstre)||(!pTexturePtBlessure)){
            SDL_Log("Unable SDL_CreatetextureFromSurface %s", SDL_GetError());
            return 1;
        }
        else{

            //tracé horizontal haut
            for(i=0;i<LARGEUR_Map+1;i++){
                SDL_Rect dst_Img={i*tailleImage,0,tailleImage,tailleImage};
                SDL_RenderCopy(pRenderer,pTextureEtoile,NULL,&dst_Img);
            }

            //tracé horizontal bas
            for(i=0;i<LARGEUR_Map+1;i++){
                SDL_Rect dst_Img={i*tailleImage+tailleImage,HAUTEUR_Map*tailleImage+tailleImage,tailleImage,tailleImage};
                SDL_RenderCopy(pRenderer,pTextureEtoile,NULL,&dst_Img);
            }

            //tracé vetical gauche
            for(i=0;i<HAUTEUR_Map+1;i++){
                SDL_Rect dst_Img={0,i*tailleImage+tailleImage,tailleImage,tailleImage};
                SDL_RenderCopy(pRenderer,pTextureEtoile,NULL,&dst_Img);
            }

            //tracé vertical droit
            for(i=0;i<HAUTEUR_Map+1;i++){
                SDL_Rect dst_Img={LARGEUR_Map*tailleImage+tailleImage,i*tailleImage,tailleImage,tailleImage};
                SDL_RenderCopy(pRenderer,pTextureEtoile,NULL,&dst_Img);
            }



            for(i=0;i<HAUTEUR_Map;i++){

                for(j=0;j<LARGEUR_Map;j++){

                //caracts pisteurs
                    nbCase=nbPisteur;
                    if(grillePersonnages[i][j]==nbCase){

                        SDL_Rect dst_Img={j*tailleImage+tailleImage,i*tailleImage+tailleImage,tailleImage,tailleImage};
                        SDL_RenderCopy(pRenderer,pTextureP_Pisteur,NULL,&dst_Img);
                    }

                //caracts monstre

                    nbCase=nbMonstre;
                    if((grillePersonnages[i][j]==nbCase)&&(monstre.debugMonstre==vrai)){

                       // gotoxy(j+1,i+1);
                        SDL_Rect dst_Img={j*tailleImage+tailleImage,i*tailleImage+tailleImage,tailleImage,tailleImage};
                        SDL_RenderCopy(pRenderer,pTextureMonstre,NULL,&dst_Img);
                    }

                //caracts blessure monstre
                    nbCase=nbpointPos_Monstre;
                    if(grillePersonnages[i][j]==nbCase){
                        //gotoxy(j+1,i+1);
                        SDL_Rect dst_Img={j*tailleImage+tailleImage,i*tailleImage+tailleImage,tailleImage,tailleImage};
                        SDL_RenderCopy(pRenderer,pTexturePtBlessure,NULL,&dst_Img);

                    }
                }
            }


        }


    }
        SDL_RenderPresent(pRenderer);

               //Destruction de la texture
        if(pTextureEtoile){
            SDL_DestroyTexture(pTextureEtoile);
        }
        if(pTextureP_Pisteur){
            SDL_DestroyTexture(pTextureP_Pisteur);
        }
        if(pTextureMonstre){
            SDL_DestroyTexture(pTextureMonstre);
        }
        if(pTexturePtBlessure){
            SDL_DestroyTexture(pTexturePtBlessure);
        }

}

void SDL_NettoieEcran(){

    SDL_RenderClear(pRenderer);
    SDL_SetRenderDrawColor(pRenderer,0,0,0,SDL_ALPHA_OPAQUE);
    SDL_RenderPresent(pRenderer);

}

void SDL_MajElement_Map(int x, int y, char car,char carType_PtExclm, char carType_PtInterog){

    int i;
    int j;
    caseNb nbCase;
    char imagePtIntero[]=SDL_IMAGE_PtIntero;
    char imagePtExclam[]=SDL_IMAGE_PtExclam;

    int tailleImage=TAILLE_IMAGE;

    SDL_Surface *pSurfacePtIntero=NULL;
    SDL_Surface *pSurfacePtExclam=NULL;
    SDL_Texture *pTexturePtIntero=NULL;
    SDL_Texture *pTexturePtExclam=NULL;




  //INIT ---------------------------------------------------
    //LOad images :
    pSurfacePtIntero = IMG_Load(imagePtIntero);
    pSurfacePtExclam= IMG_Load(imagePtExclam);


    //Si pas de reference
    if((!pSurfacePtIntero)||(!pSurfacePtExclam)){
            SDL_Log("Unable to set surface: %s", SDL_GetError());
            return 1;
    }
    else{
        pTexturePtIntero=SDL_CreateTextureFromSurface(pRenderer,pSurfacePtIntero);
        pTexturePtExclam=SDL_CreateTextureFromSurface(pRenderer,pSurfacePtExclam);
        SDL_FreeSurface(pSurfacePtIntero);
        SDL_FreeSurface(pSurfacePtExclam);



        if((!pTexturePtIntero)||(!pTexturePtExclam)){
            SDL_Log("Unable SDL_CreatetextureFromSurface %s", SDL_GetError());
            return 1;
        }
        else{

                if(car==carType_PtInterog){

                    SDL_Rect dst_Img={y*tailleImage+tailleImage,x*tailleImage+tailleImage,tailleImage,tailleImage};
                    SDL_RenderCopy(pRenderer,pTexturePtIntero,NULL,&dst_Img);
                }
                if(car==carType_PtExclm){

                    SDL_Rect dst_Img={y*tailleImage+tailleImage,x*tailleImage+tailleImage,tailleImage,tailleImage};
                    SDL_RenderCopy(pRenderer,pTexturePtExclam,NULL,&dst_Img);
                }

        }
    }
    SDL_RenderPresent(pRenderer);

               //Destruction de la texture
    if(pTexturePtIntero){
        SDL_DestroyTexture(pTexturePtIntero);
    }
    if(pTexturePtExclam){
        SDL_DestroyTexture(pTexturePtExclam);
    }

}


