
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



int main()
{



  //INIT variables :____________________________________________________________
  state etatJeu=debut;
  srand(time(0)); //init de la fct rand
  pisteur tabPisteur[NB_PisteursMax];
  monster monstre;


        //tabs :
   int grillePersonnages[HAUTEUR_Map][LARGEUR_Map];
   int grilleTraces[HAUTEUR_Map][LARGEUR_Map];
   Init_MapVide(grillePersonnages);
   Init_MapVide(grilleTraces);
        //init affichage map
    Maj_AffichMap(grillePersonnages,CAR_DelimitationMap,etatJeu,tabPisteur,monstre);




        //init des PISTEURS :-------------------------------
    int nbPisteurChoisi;
            //init nombre de pisteurs :
    Init_Saisie_NBPisteurs(tabPisteur,&nbPisteurChoisi,NB_PisteursMin,NB_PisteursMax,CAR_PisteurEnAttente,CAR_PisteurVerifie,CAR_Pisteur,NB_LettresNom,NB_PisteurPV);
            //init position de d�part des pisteurs
    Maj_AffichMap(grillePersonnages,CAR_DelimitationMap,etatJeu,tabPisteur,monstre);
    Saisie_posPisteurs(grillePersonnages,tabPisteur,nbPisteurChoisi,CAR_DelimitationMap,monstre);


        //init MONSTRE :-------------------------------------
    Init_Pos_DepartMonstre(grillePersonnages,grilleTraces,&monstre,tabPisteur,nbPisteurChoisi,NB_MonstrePV,NB_NouvelleTrace,NB_RetireTrace,NB_ToursPoint_DernierePos,CAR_Blessure_DernierePos,CAR_Monstre);




    getchar();
    getchar();

   //JEU______________________________________________



    //on commence par effacer d'un pt les traces du monstre :
    EffacementTraces_Monstre(grilleTraces,NB_RetireTrace);

    etatJeu=pisteurs_VerifVoisine;
    Maj_AffichMap(grillePersonnages,CAR_DelimitationMap,etatJeu,tabPisteur,monstre);
    CheckCaseVoisine_Pisteur(grillePersonnages,grilleTraces,tabPisteur,nbPisteurChoisi,&monstre,CHANCE_ReussirTir,etatJeu);


    //deplacement des pisteurs :
    etatJeu=dplmtPisteurs;
    Maj_AffichMap(grillePersonnages,CAR_DelimitationMap,etatJeu,tabPisteur,monstre);
    Deplcmt_Pisteur(grillePersonnages,etatJeu,tabPisteur,nbPisteurChoisi,NB_DistanceMax,CAR_DelimitationMap,monstre);













    getchar();
    return 0;


}
