#include "struct_const.h"
#include "pisteurs.h"


//SAISIE : INIT _________________________________________________


//Saisie NB Pisteurs :--------------------------------

void Init_Saisie_NBPisteurs(pisteur tab[], int *pNbPisteursChoisi, int min, int max, char carAttente, char carVerif, char carPisteur, int maxLettres,int nbPV){
//BUT:Demander en d�but de partie le nb de pisteurs qu'il y aura dans le jeu
//ENTREE:RAS
//SORTIE:Nb pisteurs

    int i;
    texteNb nbTexte;
    booleanPerso pisteurEnVie=vrai;
    int nbPisteursChoisi;
    int erreur_Scanf;



    //on demande � saisir le fameux nombre
    nbTexte=nbSaisie_TPisteur;
    AffichTexte(nbTexte,tab,0,0,0); //on param�tre la valeur corsspondant au texte � afficher ds proc : AfficTexte
    do{

       scanf("%d",&nbPisteursChoisi); //si renvoie 1 alors scanf a trouv� la saisie si non on reboucle
        if ((nbPisteursChoisi<min)||(nbPisteursChoisi>max)||(erreur_Scanf==0)){

            nbTexte=nb_TErreur;
            AffichTexte(nbTexte,tab,0,0,0);
        }

    }while((nbPisteursChoisi<min)||(nbPisteursChoisi>max));


    //on rempli le tab contenant les pisteurs du jeu : on l'initialise. On en profite pour initialiser aussi les coords x et de chaque pisteur
    for(i=0;i<nbPisteursChoisi;i++){

         tab[i].car_EnAttente=carAttente;
         tab[i].car_Pisteur=carPisteur;
         tab[i].car_Verifie=carVerif;
         tab[i].estVivant= pisteurEnVie;
         tab[i].vieRestante=nbPV;

         //on convertit le int i en char
         char tabNb[maxLettres-5];
         sprintf(tabNb, "%d", i+1);

         strcpy(tab[i].nom,"Pisteur");//on ajoute pisteur au nom de chaque var pisteur
         //puis on ajoute le int convertit en char au  nom : ce qui donne pisteur1, pisteur2 etc...
         strcat(tab[i].nom,tabNb);


         tab[i].coords.x=0;
         tab[i].coords.y=0;
    }
    //on met la valeur dans le pointeur coorspondant
    *pNbPisteursChoisi=nbPisteursChoisi;
}


//Saisie position pisteur en x et y-------------------

void Saisie_posPisteurs(int grillePersonnages[][LARGEUR_Map], pisteur tab[],int nbPisteursChoisi,char carDelimt, monster monstre){
//BUT : demander � choisir la position de d�part de chaque pisteurs
//ENTREE:NB de pisteurs
//SORTIE:coord position de chaque pisteur

    texteNb nbTexte;
    caseNb nbCase=nbPisteur;
    state etatJeu=debut_SaisieCoords;
    booleanPerso coordsIdentiques=faux;
    int x;
    int y;
    int i;
    int j;

    MsgConsignes_Jeu(etatJeu); // on affiche les consignes de l'�tat saisiCoords


    for(i=0;i<nbPisteursChoisi;i++){

        //on demande les coords :
        do{

            //X-----------------
            nbTexte=nbPos_TPisteurX;
            AffichTexte(nbTexte,tab,i,0,0);
            do{
                scanf("%d",&x);

                if((x>HAUTEUR_Map)||(x<1)){
                    nbTexte=nb_TErreur;
                    AffichTexte(nbTexte,tab,i);
                }

            }while((x>HAUTEUR_Map)||(x<1));


            //Y----------------
            nbTexte=nbPos_TPisteurY;
            AffichTexte(nbTexte,tab,i,0,0);
            do{
                scanf("%d",&y);
                if((y>LARGEUR_Map) ||(y<1)){
                    nbTexte=nb_TErreur;
                    AffichTexte(nbTexte,tab,i);
                }

            }while((y>LARGEUR_Map)||(y<1));



            //on v�rifie que les coordonn�es ne sont pas les m�mes que celles d'un autre pisteur
            //on reinit coordsIdentiques � faux:
            coordsIdentiques=faux;
            for(j=0;j<nbPisteursChoisi;j++){

                if((x==tab[j].coords.x)&&(y==tab[j].coords.y)){
                        coordsIdentiques=vrai;
                }
            }

            //on pr�vient l'utilisateur qu'il a entr� les m�mes coordoonn�es qu'un autre pisteur
            if(coordsIdentiques==vrai){
                nbTexte=erreur_CoordsIdentiques;
                AffichTexte(nbTexte,tab,0,0,0,0);
            }


        }while(coordsIdentiques==vrai);

        //on met en place les coords dans la grille :
        grillePersonnages[x-1][y-1]=nbCase;
        tab[i].coords.x=x;
        tab[i].coords.y=y;

        //on affiche la map avec � jour la position du pisteur :
        Maj_AffichMap(grillePersonnages,carDelimt,etatJeu,tab,monstre);

    }

}





//JEU _______________________________________________________________________

int Tirer_SurMonstre(int vieMonstre,int chanceTir){
//BUT:on peut tirer sur le monstre ou non. Au choix
//ENTREE:
//SORTIE:

    texteNb nbTexte;
    int  min=1;
    int max=10;
    int result;
    char car_TirerOuNon;

    //on demande au joueur s'il veut tirer dessus ou non :
    nbTexte=nbTirer_TMonstre;
    AffichTexte(nbTexte,0,0,0,0,0);
    do{
        scanf("%c",&car_TirerOuNon);
        if((car_TirerOuNon!='t')&&(car_TirerOuNon!='T')&&(car_TirerOuNon!='r')&&(car_TirerOuNon!='R')){
            nbTexte=nb_TErreur;
            AffichTexte(nbTexte,0,0,0,0,0);
        }
    }while((car_TirerOuNon!='t')&&(car_TirerOuNon!='T')&&(car_TirerOuNon!='r')&&(car_TirerOuNon!='R'));




    if((car_TirerOuNon=='t')||(car_TirerOuNon=='T')){

        //40% de chances de toucher

        //on en sort une valeur al�atoire
        result=(rand()%(max-min+1)) + min;

        if(result<=chanceTir/10){ //si on obtient soit 1,2,3 ou 4 alors on est dans les 40% de tir.
        //alors que si on tombe sur 5,6,7,8,9,10 on est dans les 60% d'�chouer
            //il r�ussi le tir
            nbTexte=nbTirReussi_TMonstre;
            //on enl�ve 1 pv au monstre :
            vieMonstre--;
            AffichTexte(nbTexte,0,0,0,0,vieMonstre);
        }
        else{
            //il loupe le tir
            nbTexte=nbTirLoupe_TMonstre;
            AffichTexte(nbTexte,0,0,0,0,0);
        }
    }

    return vieMonstre;

}

void CheckCaseVoisine_Pisteur(int grillePerso[][LARGEUR_Map], int grilleTraces[][LARGEUR_Map], pisteur tabPisteur[], int nbPisteurs, monster *monstre,int chanceTir,state etatJeu){
//BUT:checker toutes les cases voisines, les 8 et voir si monstre � c�t�, il y a des traces ou rien

    int i;
    int x;
    int y;
    int vieMonstre=monstre->vieRestante;
    int nbTraceMax=monstre->tracesFraiches;
    caseNb nbCase;
    texteNb nbTexte;
    booleanPerso monstreEstLa=faux;
    booleanPerso traceEstLa=faux;
    caseAutour autourCase;

    MsgConsignes_Jeu(etatJeu);

    for(i=0;i<nbPisteurs;i++){

        x=tabPisteur[i].coords.x;
        y=tabPisteur[i].coords.y;
        //on oublie pas que les tableaux commencent � 0 et non 1, du coup on retire 1
        x=x-1;
        y=y-1;
        nbCase=nbMonstre;
        //on affiche le pisteur avec un !
        majElement_SurMap(x,y,tabPisteur[i].car_Verifie,18+i);





        //le monstre est � c�t� :
        if((grillePerso[x-1][y]==nbMonstre)||(grillePerso[x+1][y]==nbMonstre) || (grillePerso[x][y-1]==nbMonstre) || (grillePerso[x][y+1]==nbMonstre)||(grillePerso[x-1][y-1]==nbMonstre)||(grillePerso[x-1][y+1]==nbMonstre)||(grillePerso[x+1][y+1]==nbMonstre)||(grillePerso[x+1][y-1]==nbMonstre)){

            monstreEstLa=vrai;
            nbTexte=nbMonstre_TCaseVoisine;

            AffichTexte(nbTexte,tabPisteur,i);

            vieMonstre=Tirer_SurMonstre(vieMonstre,chanceTir);
            monstre->vieRestante=vieMonstre;
        }




        //traces visibles :
        else if(monstreEstLa==faux){

            nbTexte=nbTraces_TCaseVoisine;

            if ((x>0) && (x<HAUTEUR_Map-1)){

                if ((y>0) && (y<LARGEUR_Map-1)){

                        //diagonaleH_G
                        if((grilleTraces[x-1][y-1]>0)&&(grilleTraces[x-1][y-1]<nbTraceMax)){
                            autourCase=diagH_G;
                            traceEstLa=vrai;
                            AffichTexte(nbTexte,tabPisteur,i,autourCase,grilleTraces[x-1][y-1],0);

                        }
                        //Haut
                        if((grilleTraces[x-1][y]>0)&&(grilleTraces[x-1][y]<nbTraceMax)){
                            autourCase=auDessus;
                            traceEstLa=vrai;
                            AffichTexte(nbTexte,tabPisteur,i,autourCase,grilleTraces[x-1][y],0);

                        }
                        //DiagonaleH_D
                        if((grilleTraces[x-1][y+1]>0)&&(grilleTraces[x-1][y+1]<nbTraceMax)){
                            autourCase=diagH_D;
                            traceEstLa=vrai;
                            AffichTexte(nbTexte,tabPisteur,i,autourCase,grilleTraces[x-1][y+1],0);

                        }
                        //Droite
                        if((grilleTraces[x][y+1]>0)&&(grilleTraces[x][y+1]<nbTraceMax)){
                            autourCase=aDroite;
                            traceEstLa=vrai;
                            AffichTexte(nbTexte,tabPisteur,i,autourCase,grilleTraces[x][y+1],0);
                        }
                        //DiagonaleB_D
                        if((grilleTraces[x+1][y+1]>0)&&(grilleTraces[x+1][y+1]<nbTraceMax)){
                            autourCase=diagB_D;
                            traceEstLa=vrai;
                            AffichTexte(nbTexte,tabPisteur,i,autourCase,grilleTraces[x+1][y+1],0);
                        }
                        //Bas
                        if((grilleTraces[x+1][y]>0)&&(grilleTraces[x+1][y]<nbTraceMax)){
                            autourCase=enBas;
                            traceEstLa=vrai;
                            AffichTexte(nbTexte,tabPisteur,i,autourCase,grilleTraces[x+1][y],0);
                        }
                        //DiagonaleB_G
                        if((grilleTraces[x+1][y-1]>0)&&(grilleTraces[x+1][y-1]<nbTraceMax)){
                            autourCase=diagB_G;
                            traceEstLa=vrai;
                            AffichTexte(nbTexte,tabPisteur,i,autourCase,grilleTraces[x+1][y-1],0);
                        }
                        //Gauche
                        if((grilleTraces[x][y-1]>0)&&(grilleTraces[x][y-1]<nbTraceMax)){
                            autourCase=aGauche;
                            traceEstLa=vrai;
                            AffichTexte(nbTexte,tabPisteur,i,autourCase,grilleTraces[x][y-1],0);
                        }
                }
                else if(y==0){

                        //Haut
                        if((grilleTraces[x-1][y]>0)&&(grilleTraces[x-1][y]<nbTraceMax)){
                            autourCase=auDessus;
                            traceEstLa=vrai;
                            AffichTexte(nbTexte,tabPisteur,i,autourCase,grilleTraces[x-1][y],0);

                        }
                        //DiagonaleH_D
                        if((grilleTraces[x-1][y+1]>0)&&(grilleTraces[x-1][y+1]<nbTraceMax)){
                            autourCase=diagH_D;
                            traceEstLa=vrai;
                            AffichTexte(nbTexte,tabPisteur,i,autourCase,grilleTraces[x-1][y+1],0);

                        }
                        //Droite
                        if((grilleTraces[x][y+1]>0)&&(grilleTraces[x][y+1]<nbTraceMax)){
                            autourCase=aDroite;
                            traceEstLa=vrai;
                            AffichTexte(nbTexte,tabPisteur,i,autourCase,grilleTraces[x][y+1],0);
                        }
                        //DiagonaleB_D
                        if((grilleTraces[x+1][y+1]>0)&&(grilleTraces[x+1][y+1]<nbTraceMax)){
                            autourCase=diagB_D;
                            traceEstLa=vrai;
                            AffichTexte(nbTexte,tabPisteur,i,autourCase,grilleTraces[x+1][y+1],0);
                        }
                        //Bas
                        if((grilleTraces[x+1][y]>0)&&(grilleTraces[x+1][y]<nbTraceMax)){
                            autourCase=enBas;
                            traceEstLa=vrai;
                            AffichTexte(nbTexte,tabPisteur,i,autourCase,grilleTraces[x+1][y],0);
                        }

                }
                else if (y==LARGEUR_Map-1){

                        //diagonaleH_G
                        if((grilleTraces[x-1][y-1]>0)&&(grilleTraces[x-1][y-1]<nbTraceMax)){
                            autourCase=diagH_G;
                            traceEstLa=vrai;
                            AffichTexte(nbTexte,tabPisteur,i,autourCase,grilleTraces[x-1][y-1],0);

                        }
                        //Haut
                        if((grilleTraces[x-1][y]>0)&&(grilleTraces[x-1][y]<nbTraceMax)){
                            autourCase=auDessus;
                            traceEstLa=vrai;
                            AffichTexte(nbTexte,tabPisteur,i,autourCase,grilleTraces[x-1][y],0);

                        }
                        //Bas
                        if((grilleTraces[x+1][y]>0)&&(grilleTraces[x+1][y]<nbTraceMax)){
                            autourCase=enBas;
                            traceEstLa=vrai;
                            AffichTexte(nbTexte,tabPisteur,i,autourCase,grilleTraces[x+1][y],0);
                        }
                        //DiagonaleB_G
                        if((grilleTraces[x+1][y-1]>0)&&(grilleTraces[x+1][y-1]<nbTraceMax)){
                            autourCase=diagB_G;
                            traceEstLa=vrai;
                            AffichTexte(nbTexte,tabPisteur,i,autourCase,grilleTraces[x+1][y-1],0);
                        }
                        //Gauche
                        if((grilleTraces[x][y-1]>0)&&(grilleTraces[x][y-1]<nbTraceMax)){
                            autourCase=aGauche;
                            traceEstLa=vrai;
                            AffichTexte(nbTexte,tabPisteur,i,autourCase,grilleTraces[x][y-1],0);
                        }



                }
            }
            else if (x==0){

                if ((y>0) && (y<LARGEUR_Map-1)){

                        //Droite
                        if((grilleTraces[x][y+1]>0)&&(grilleTraces[x][y+1]<nbTraceMax)){
                            autourCase=aDroite;
                            traceEstLa=vrai;
                            AffichTexte(nbTexte,tabPisteur,i,autourCase,grilleTraces[x][y+1],0);
                        }
                        //DiagonaleB_D
                        if((grilleTraces[x+1][y+1]>0)&&(grilleTraces[x+1][y+1]<nbTraceMax)){
                            autourCase=diagB_D;
                            traceEstLa=vrai;
                            AffichTexte(nbTexte,tabPisteur,i,autourCase,grilleTraces[x+1][y+1],0);
                        }
                        //Bas
                        if((grilleTraces[x+1][y]>0)&&(grilleTraces[x+1][y]<nbTraceMax)){
                            autourCase=enBas;
                            traceEstLa=vrai;
                            AffichTexte(nbTexte,tabPisteur,i,autourCase,grilleTraces[x+1][y],0);
                        }
                        //DiagonaleB_G
                        if((grilleTraces[x+1][y-1]>0)&&(grilleTraces[x+1][y-1]<nbTraceMax)){
                            autourCase=diagB_G;
                            traceEstLa=vrai;
                            AffichTexte(nbTexte,tabPisteur,i,autourCase,grilleTraces[x+1][y-1],0);
                        }
                        //Gauche
                        if((grilleTraces[x][y-1]>0)&&(grilleTraces[x][y-1]<nbTraceMax)){
                            autourCase=aGauche;
                            traceEstLa=vrai;
                            AffichTexte(nbTexte,tabPisteur,i,autourCase,grilleTraces[x][y-1],0);
                        }

                }
                else if(y==0){

                        //Droite
                        if((grilleTraces[x][y+1]>0)&&(grilleTraces[x][y+1]<nbTraceMax)){
                            autourCase=aDroite;
                            traceEstLa=vrai;
                            AffichTexte(nbTexte,tabPisteur,i,autourCase,grilleTraces[x][y+1],0);
                        }
                        //DiagonaleB_D
                        if((grilleTraces[x+1][y+1]>0)&&(grilleTraces[x+1][y+1]<nbTraceMax)){
                            autourCase=diagB_D;
                            traceEstLa=vrai;
                            AffichTexte(nbTexte,tabPisteur,i,autourCase,grilleTraces[x+1][y+1],0);
                        }
                        //Bas
                        if((grilleTraces[x+1][y]>0)&&(grilleTraces[x+1][y]<nbTraceMax)){
                            autourCase=enBas;
                            traceEstLa=vrai;
                            AffichTexte(nbTexte,tabPisteur,i,autourCase,grilleTraces[x+1][y],0);
                        }

                }
                else if (y==LARGEUR_Map-1){

                        //Bas
                        if((grilleTraces[x+1][y]>0)&&(grilleTraces[x+1][y]<nbTraceMax)){
                            autourCase=enBas;
                            traceEstLa=vrai;
                            AffichTexte(nbTexte,tabPisteur,i,autourCase,grilleTraces[x+1][y],0);
                        }
                        //DiagonaleB_G
                        if((grilleTraces[x+1][y-1]>0)&&(grilleTraces[x+1][y-1]<nbTraceMax)){
                            autourCase=diagB_G;
                            traceEstLa=vrai;
                            AffichTexte(nbTexte,tabPisteur,i,autourCase,grilleTraces[x+1][y-1],0);
                        }
                        //Gauche
                        if((grilleTraces[x][y-1]>0)&&(grilleTraces[x][y-1]<nbTraceMax)){
                            autourCase=aGauche;
                            traceEstLa=vrai;
                            AffichTexte(nbTexte,tabPisteur,i,autourCase,grilleTraces[x][y-1],0);
                        }


                }
            }
            else if (x==HAUTEUR_Map-1){

                if ((y>0) && (y<LARGEUR_Map-1)){
                            //diagonaleH_G
                        if((grilleTraces[x-1][y-1]>0)&&(grilleTraces[x-1][y-1]<nbTraceMax)){
                            autourCase=diagH_G;
                            traceEstLa=vrai;
                            AffichTexte(nbTexte,tabPisteur,i,autourCase,grilleTraces[x-1][y-1],0);

                        }
                        //Haut
                        if((grilleTraces[x-1][y]>0)&&(grilleTraces[x-1][y]<nbTraceMax)){
                            autourCase=auDessus;
                            traceEstLa=vrai;
                            AffichTexte(nbTexte,tabPisteur,i,autourCase,grilleTraces[x-1][y],0);

                        }
                        //DiagonaleH_D
                        if((grilleTraces[x-1][y+1]>0)&&(grilleTraces[x-1][y+1]<nbTraceMax)){
                            autourCase=diagH_D;
                            traceEstLa=vrai;
                            AffichTexte(nbTexte,tabPisteur,i,autourCase,grilleTraces[x-1][y+1],0);

                        }
                        //Droite
                        if((grilleTraces[x][y+1]>0)&&(grilleTraces[x][y+1]<nbTraceMax)){
                            autourCase=aDroite;
                            traceEstLa=vrai;
                            AffichTexte(nbTexte,tabPisteur,i,autourCase,grilleTraces[x][y+1],0);
                        }
                        //Gauche
                        if((grilleTraces[x][y-1]>0)&&(grilleTraces[x][y-1]<nbTraceMax)){
                            autourCase=aGauche;
                            traceEstLa=vrai;
                            AffichTexte(nbTexte,tabPisteur,i,autourCase,grilleTraces[x][y-1],0);
                        }
                }
               else if (y==0){
                        //Haut
                        if((grilleTraces[x-1][y]>0)&&(grilleTraces[x-1][y]<nbTraceMax)){
                            autourCase=auDessus;
                            traceEstLa=vrai;
                            AffichTexte(nbTexte,tabPisteur,i,autourCase,grilleTraces[x-1][y],0);

                        }
                        //DiagonaleH_D
                        if((grilleTraces[x-1][y+1]>0)&&(grilleTraces[x-1][y+1]<nbTraceMax)){
                            autourCase=diagH_D;
                            traceEstLa=vrai;
                            AffichTexte(nbTexte,tabPisteur,i,autourCase,grilleTraces[x-1][y+1],0);

                        }
                        //Droite
                        if((grilleTraces[x][y+1]>0)&&(grilleTraces[x][y+1]<nbTraceMax)){
                            autourCase=aDroite;
                            traceEstLa=vrai;
                            AffichTexte(nbTexte,tabPisteur,i,autourCase,grilleTraces[x][y+1],0);
                        }
               }
               else if (y==LARGEUR_Map-1){
                            //diagonaleH_G
                        if((grilleTraces[x-1][y-1]>0)&&(grilleTraces[x-1][y-1]<nbTraceMax)){
                            autourCase=diagH_G;
                            traceEstLa=vrai;
                            AffichTexte(nbTexte,tabPisteur,i,autourCase,grilleTraces[x-1][y-1],0);

                        }
                        //Haut
                        if((grilleTraces[x-1][y]>0)&&(grilleTraces[x-1][y]<nbTraceMax)){
                            autourCase=auDessus;
                            traceEstLa=vrai;
                            AffichTexte(nbTexte,tabPisteur,i,autourCase,grilleTraces[x-1][y],0);

                        }

                        //Gauche
                        if((grilleTraces[x][y-1]>0)&&(grilleTraces[x][y-1]<nbTraceMax)){
                            autourCase=aGauche;
                            traceEstLa=vrai;
                            AffichTexte(nbTexte,tabPisteur,i,autourCase,grilleTraces[x][y-1],0);
                        }
              }

            }

        }



        //il n'y a rien :
        if((monstreEstLa==faux)&&(traceEstLa==faux)){
            nbTexte=nbRAS_TCaseVoisine;
            AffichTexte(nbTexte,tabPisteur,i,0,0,0);
        }
        monstreEstLa=faux;
        traceEstLa=faux;

        getchar();
        //on remet l'affichage du pisteur par d�faut

        majElement_SurMap(x,y,tabPisteur[i].car_Pisteur,18+i);
    }





}



int ChoixDistance(int grillePersos[][LARGEUR_Map], pisteur tabPisteur[], int indexTab,int x,int y,int maxDistance,int nb_Direction){
//BUT:choisir la distance de cases qu'on veut atteindre. MAX:4



    texteNb nbTexte=nbChoix_TDistance;
    int nb_Distance;
    booleanPerso distancePossible=vrai;
    caseNb nbCase=nbPisteur;


    //demander quelle direction prendre :
    AffichTexte(nbTexte,tabPisteur,indexTab,0,0,0);


    do{

        //reinit
        distancePossible=vrai;
        nbTexte=nbChoix_TDistance;

        //demander quelle distance
        do{
            scanf("%d",&nb_Distance);
            if((nb_Distance<1)||(nb_Distance>maxDistance)){
                nbTexte=nb_TErreur;
                AffichTexte(nbTexte,tabPisteur,indexTab,0,0,0);
            }
        }while((nb_Distance<1)||(nb_Distance>maxDistance));



        //checker si la distance est possible : fait un check de la case de la distance prise
        if(nb_Direction==haut){
            if((x-nb_Distance<0)||(grillePersos[x-nb_Distance][y]==nbCase)){

                distancePossible=faux;
                nbTexte=nbChoix_Erreur_TDistance;
                AffichTexte(nbTexte,tabPisteur,indexTab,0,0,0);
                nbTexte=nb_TErreur;
                AffichTexte(nbTexte,tabPisteur,indexTab,0,0,0);
            }
        }
        else if(nb_Direction==droite){
            if((y+nb_Distance>=LARGEUR_Map)||(grillePersos[x][y+nb_Distance]==nbCase)){

                distancePossible=faux;
                nbTexte=nbChoix_Erreur_TDistance;
                AffichTexte(nbTexte,tabPisteur,indexTab,0,0,0);
                nbTexte=nb_TErreur;
                AffichTexte(nbTexte,tabPisteur,indexTab,0,0,0);
            }
        }
        else if(nb_Direction==bas){
            if((x+nb_Distance>=HAUTEUR_Map)||(grillePersos[x+nb_Distance][y]==nbCase)){

                distancePossible=faux;
                nbTexte=nbChoix_Erreur_TDistance;
                AffichTexte(nbTexte,tabPisteur,indexTab,0,0,0);
                nbTexte=nb_TErreur;
                AffichTexte(nbTexte,tabPisteur,indexTab,0,0,0);
            }
        }
        else if(nb_Direction==gauche){
            if((y-nb_Distance<0)||(grillePersos[x][y-nb_Distance]==nbCase)){

                distancePossible=faux;
                nbTexte=nbChoix_Erreur_TDistance;
                AffichTexte(nbTexte,tabPisteur,indexTab,0,0,0);
                nbTexte=nb_TErreur;
                AffichTexte(nbTexte,tabPisteur,indexTab,0,0,0);
            }
        }


    }while(distancePossible==faux);

    return nb_Distance;




}


int ChoixDirection(int grillePersos[][LARGEUR_Map], pisteur tabPisteur[], int indexTab,int x,int y){
//BUT:choix de la direction dans laquelle part le pisteur : soit H B G D

    texteNb nbTexte=nbChoix_TDirection;
    int nb_Direction;
    booleanPerso directionPossible=vrai;
    caseNb nbCase=nbPisteur;


    //demander quelle direction prendre :
    AffichTexte(nbTexte,tabPisteur,indexTab,0,0,0);


    do{

        //reinit
        directionPossible=vrai;
        nbTexte=nbChoix_TDirection;
        do{
            scanf("%d",&nb_Direction);
            if((nb_Direction!=haut)&&(nb_Direction!=droite)&&(nb_Direction!=bas)&&(nb_Direction!=gauche)){
                nbTexte=nb_TErreur;
                AffichTexte(nbTexte,tabPisteur,indexTab,0,0,0);
            }
        }while((nb_Direction!=haut)&&(nb_Direction!=droite)&&(nb_Direction!=bas)&&(nb_Direction!=gauche));



        //checker si la direction est possible : fait un check de la case juste voisine de la direction prise
        if(nb_Direction==haut){
            if((x-1<0)||(grillePersos[x-1][y]==nbCase)){

                directionPossible=faux;
                nbTexte=nbChoix_Erreur_TDirection;
                AffichTexte(nbTexte,tabPisteur,indexTab,0,0,0);
                nbTexte=nb_TErreur;
                AffichTexte(nbTexte,tabPisteur,indexTab,0,0,0);
            }
        }
        else if(nb_Direction==droite){
            if((y+1>=LARGEUR_Map)||(grillePersos[x][y+1]==nbCase)){

                directionPossible=faux;
                nbTexte=nbChoix_Erreur_TDirection;
                AffichTexte(nbTexte,tabPisteur,indexTab,0,0,0);
                nbTexte=nb_TErreur;
                AffichTexte(nbTexte,tabPisteur,indexTab,0,0,0);
            }
        }
        else if(nb_Direction==bas){
            if((x+1>=HAUTEUR_Map)||(grillePersos[x+1][y]==nbCase)){

                directionPossible=faux;
                nbTexte=nbChoix_Erreur_TDirection;
                AffichTexte(nbTexte,tabPisteur,indexTab,0,0,0);
                nbTexte=nb_TErreur;
                AffichTexte(nbTexte,tabPisteur,indexTab,0,0,0);
            }
        }
        else if(nb_Direction==gauche){
            if((y-1<0)||(grillePersos[x][y-1]==nbCase)){

                directionPossible=faux;
                nbTexte=nbChoix_Erreur_TDirection;
                AffichTexte(nbTexte,tabPisteur,indexTab,0,0,0);
                nbTexte=nb_TErreur;
                AffichTexte(nbTexte,tabPisteur,indexTab,0,0,0);
            }
        }


    }while(directionPossible==faux);

    return nb_Direction;



}


void Deplcmt_Pisteur(int grillePersos[][LARGEUR_Map],state etatJeu, pisteur tabPisteur[],int nbPisteurs, int maxDistance, char carDelimt,monster monstre){
//BUT:d�placer le pisteur

    int i;
    int x;
    int y;
    int nb_DirectionChoisie;
    int nb_DistanceChoisie;
    caseNb nbCase;

    //on affiche l'�tat de la situation : d�placement de chaque pisteur
    MsgConsignes_Jeu(etatJeu);



    for(i=0;i<nbPisteurs;i++){

        //-1 pour coller � la plage du tableau : 0 �... et non 1 �...
        x=tabPisteur[i].coords.x-1;
        y=tabPisteur[i].coords.y-1;
        majElement_SurMap(x,y,tabPisteur[i].car_EnAttente,18+i);

    //demander direction et distance
        //direction :
        nb_DirectionChoisie=ChoixDirection(grillePersos,tabPisteur,i,x,y);
        //distance :
        nb_DistanceChoisie=ChoixDistance(grillePersos,tabPisteur,i,x,y,maxDistance,nb_DirectionChoisie);
        //reinit
        majElement_SurMap(x,y,tabPisteur[i].car_Pisteur,18+i);



    //atribuer ces nouvelles informations
        nbCase=nbPisteur;
        switch(nb_DirectionChoisie){

            case haut:
                //attribuer les coords au pisteur
                tabPisteur[i].coords.x=tabPisteur[i].coords.x-nb_DistanceChoisie;
                //mettre le chiffre case grillePerso position coorrespondante
                grillePersos[x][y]=0;
                grillePersos[x-nb_DistanceChoisie][y]=nbCase;
                break;

            case droite :
                tabPisteur[i].coords.y=tabPisteur[i].coords.y+nb_DistanceChoisie;
                grillePersos[x][y]=0;
                grillePersos[x][y+nb_DistanceChoisie]=nbCase;
                break;

            case bas:
                tabPisteur[i].coords.x=tabPisteur[i].coords.x+nb_DistanceChoisie;
                grillePersos[x][y]=0;
                grillePersos[x+nb_DistanceChoisie][y]=nbCase;
                break;


            case gauche:
                tabPisteur[i].coords.y=tabPisteur[i].coords.y-nb_DistanceChoisie;
                grillePersos[x][y]=0;
                grillePersos[x][y-nb_DistanceChoisie]=nbCase;
                break;

        }
        //on reaffiche la map pour modifier l'affichage de la position du pisteur
        Maj_AffichMap(grillePersos,carDelimt,etatJeu,tabPisteur,monstre);

    }
}


