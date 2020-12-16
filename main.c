
/*FEATURES :

    //INIT :
- afficher map aves ses d�limitations : 29x14cases=406 cases entour�es de "*"
- demander au joueur combien de pisteurs il veut : pr�f�rable d'en prendre 3 ou 4->on peut choisir entre 1 et 10
- demander au joueur une valeur en x et en y pour chaque pisteur. Puis � chaque fois faire apparaitre un "P" sur la case choisie
- positioner au hasard le monstre sur une case(apposer nb 16), et le cacher. Si case tir�e est voisine � un pisteur, alors refaire le tirage



    //PARTIE :


- -1 sur les nb des traces
- chaque pisteur va dire ce qu'il voit autour de lui (sur les 8 cases) � tour de r�le.(Il est affich� sur la map d'un "!")
    3 possibilit�s :
        a. il n'y a rien autour de lui et affiche "RIEN en 1,,2,3,4,5,6,7,8"
        b. certaines cases ont des traces du monstre : il affiche "traces en 'nbCaseVoisine' de valeur 'nbTraces'" pour chaque case concern�e l'une apr� l'autre
        c. Le monstre est dans l'une des cases voisine : le pisteur annonce juste "je le vois". on peut tirer ou soit ne rien faire
    -->40% de chances de le toucher � savoir qu'il a 4 points de vie et on l'indique � l'�cran

- Sur la map affich� avec "?". On d�place ensuite les pisteurs � tour de r�le : d'abord distance de d�placement demand�es : de 1 � 4 puis direction de d�placement : quatre directions possibles : 1 pour haut, 2pour droite, 3pour bas et 4 pour gauche
/*COde r�alis� par Elias Eckl�


- le monstre se d�place d'une case � chaque tour et marque sur la case auquel il se trouve le nb 16. Il se d�place en l'une des 4 cases diff�rentes, H B G D  al�atoirement(ou flaire les traces des pisteurs)
    et s'il tombe sur m�me case que pisteur alors il le mange et l'indique � l'�cran
- A noter qu'il check les 4 cases autour de lui pour savoir s'il y a un pisteur et si oui, il va sur cette case en question pour le manger
    Si touch� par coup de tir alors pendant quatre tours un point appara�t au dernier endroit s�journ� avt d�placement et perd 1 pv


    //CONDITION de victoire : les pv du monstres ont atteints 0
    //CONDITION de d�faite  : tous les pisteurs sont morts
    //du coup on boucle les 3 phases de la partie autant de fois jusqu'� qu'il arrive une de ces condtions



    //FIN DE PARTIE :
- on affiche si le monstre a mang� tous les pisteurs
- ou si les pisteurs ont tu�s le monstre

*/


#include "define.h"


//SDL declaration pointeurs :
SDL_Window *pWindow=NULL; //pointeur pointant sur param�tres window
SDL_Renderer *pRenderer=NULL;//pointeur pointant sur param�tres renderer

int main(int argc,char *argv[])
{



  //INIT variables :____________________________________________________________

        //vars declar
   state etatJeu=debut;
   srand(time(0)); //init de la fct rand
   pisteur tabPisteur[NB_PisteursMax];
   monster monstre;
   booleanPerso pisteursSontEnVie=vrai;
        //tabs declar et init:
   int grillePersonnages[HAUTEUR_Map][LARGEUR_Map];
   int grilleTraces_Monstre[HAUTEUR_Map][LARGEUR_Map];//du monstre
   int grilleTraces_Pisteurs[HAUTEUR_Map][LARGEUR_Map];
   Init_MapVide(grillePersonnages);
   Init_MapVide(grilleTraces_Monstre);
   Init_MapVide(grilleTraces_Pisteurs);



        //afficher debut jeu
    MsgConsignes_Jeu(etatJeu);
    getchar();
        //activer ou non le mode debogage du jeu : carmonstre visible ou non
    ModeDebug_Monstre(&monstre);
    getchar();
    //init affichage map
    Maj_AffichMap(grillePersonnages,CAR_DelimitationMap,etatJeu,tabPisteur,monstre);


        //Init SDL------------------------------------------
    pWindow=NULL; //pointeur pointant sur param�tres window
    pRenderer=NULL;//pointeur pointant sur param�tres renderer
    isOpen=SDL_TRUE; //global
    SDL_Initialisation(WINDOW_WIDTH,WINDOW_HEIGHT);
    SDL_InitImg();
       //refresh SDL :
        SDL_refreshEvent(monstre.estVivant,pisteursSontEnVie);
        //affichage Map SDL:
    SDL_AffichMap(grillePersonnages,monstre,SDL_IMAGE_Etoile,SDL_IMAGE_Pisteur,SDL_IMAGE_Monstre,SDL_Image_PtBlessure,TAILLE_IMAGE);



        //init des PISTEURS :-------------------------------
    int nbPisteurChoisi;
            //init nombre de pisteurs :
    Init_Saisie_NBPisteurs(tabPisteur,&nbPisteurChoisi,NB_PisteursMin,NB_PisteursMax,CAR_PisteurEnAttente,CAR_PisteurVerifie,CAR_Pisteur,NB_LettresNom,NB_PisteurPV,NB_NouvelleTrace,NB_RetireTrace);
            //init position de d�part des pisteurs
    Maj_AffichMap(grillePersonnages,CAR_DelimitationMap,etatJeu,tabPisteur,monstre);
    Saisie_posPisteurs(grillePersonnages,grilleTraces_Pisteurs,tabPisteur,nbPisteurChoisi,CAR_DelimitationMap,monstre);

        //init MONSTRE :-------------------------------------
    Init_Pos_DepartMonstre(grillePersonnages,grilleTraces_Monstre,&monstre,tabPisteur,nbPisteurChoisi,NB_MonstrePV,NB_NouvelleTrace,NB_RetireTrace,NB_ToursPoint_DernierePos,CAR_Blessure_DernierePos,CAR_Monstre);







   //JEU______________________________________________
    getchar();
    getchar();


    do{


        //on commence par effacer d'un pt les traces du monstre et des pisteurs:
        EffacementTraces_Monstre(grilleTraces_Monstre,NB_RetireTrace);
        EffacementTraces_Pisteur(grilleTraces_Pisteurs,NB_RetireTrace);




        //compte rendu des pisteurs :
        etatJeu=pisteurs_VerifVoisine;
        Maj_AffichMap(grillePersonnages,CAR_DelimitationMap,etatJeu,tabPisteur,monstre);
        CheckCaseVoisine_Pisteur(grillePersonnages,grilleTraces_Monstre,tabPisteur,nbPisteurChoisi,&monstre,CHANCE_ReussirTir,etatJeu,NB_Degat_Pisteur,CAR_DelimitationMap);

        //deplacement des pisteurs :
        etatJeu=dplmtPisteurs;
        Maj_AffichMap(grillePersonnages,CAR_DelimitationMap,etatJeu,tabPisteur,monstre);
        Deplcmt_Pisteur(grillePersonnages,grilleTraces_Pisteurs,etatJeu,tabPisteur,nbPisteurChoisi,NB_DistanceMax,CAR_DelimitationMap,monstre,NB_Degat_Monstre);



        //on v�rifie s'il reste des pisteurs en vie ou non, idem pour le monstre
            //pisteurs:
        PisteursRestant_EnVie(tabPisteur,nbPisteurChoisi,&pisteursSontEnVie);
            //monstre
        MonstreEnVie(&monstre);



        if((monstre.estVivant==vrai)&&(pisteursSontEnVie==vrai)){
            //deplacement du monstre :
            etatJeu=dplmtMonstre;
            Maj_AffichMap(grillePersonnages,CAR_DelimitationMap,etatJeu,tabPisteur,monstre);
            Deplcmt_Monstre(grillePersonnages,grilleTraces_Pisteurs,grilleTraces_Monstre,tabPisteur,nbPisteurChoisi,NB_NouvelleTrace,NB_Degat_Monstre,monstre,&monstre,etatJeu);
            Maj_AffichMap(grillePersonnages,CAR_DelimitationMap,etatJeu,tabPisteur,monstre);
        }

        //on enleve 1 au nb de tours de blessure du monstre s'il y a :
        MonstreTouche(grillePersonnages,monstre,&monstre,NB_ToursPoint_DernierePos);




        //on v�rifie � nouveau s'il reste des pisteurs en vie ou non, idem pour le monstre
            //pisteurs:
        PisteursRestant_EnVie(tabPisteur,nbPisteurChoisi,&pisteursSontEnVie);
            //monstre
        MonstreEnVie(&monstre);

        //message de reboucle du jeu
        if((monstre.estVivant==vrai)&&(pisteursSontEnVie==vrai)){
            etatJeu=rebouclePartie;
            MsgConsignes_Jeu(etatJeu);
        }
        getchar();



    }while((monstre.estVivant==vrai)&&(pisteursSontEnVie==vrai));






    //FIN DU JEU______________________________________________________
    if((pisteursSontEnVie==vrai)&&(monstre.estVivant==faux)){
        etatJeu=victoirePisteurs;

    }
    else if((pisteursSontEnVie==faux)&&(monstre.estVivant==vrai)){
        etatJeu=victoireMonstre;
    }
    MsgConsignes_Jeu(etatJeu);



    getchar();



    //on lib�re tout :
        //Destruction des ressources du rendu
    if(pRenderer){
        SDL_DestroyRenderer(pRenderer);
    }

    if(pWindow){
      SDL_DestroyWindow(pWindow);
    }
    IMG_Quit();
    SDL_Quit();
    return 0;

/*COde r�alis� par Elias Eckl�*/
}
