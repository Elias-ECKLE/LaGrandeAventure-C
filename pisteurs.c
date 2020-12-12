#include "struct_const.h"
#include "pisteurs.h"


//SAISIE : INIT _________________________________________________


//Saisie NB Pisteurs :--------------------------------

void Init_Saisie_NBPisteurs(pisteur tab[], int *pNbPisteursChoisi, int min, int max, char carAttente, char carVerif, char carPisteur, int maxLettres){
//BUT:Demander en début de partie le nb de pisteurs qu'il y aura dans le jeu
//ENTREE:RAS
//SORTIE:Nb pisteurs

    int i;
    texteNb nbTexte;
    booleanPerso pisteurEnVie=vrai;
    int nbPisteursChoisi;
    int erreur_Scanf;



    //on demande à saisir le fameux nombre
    nbTexte=nbSaisie_TPisteur;
    AffichTexte(nbTexte,tab,0,0,0); //on paramètre la valeur corsspondant au texte à afficher ds proc : AfficTexte
    do{

       scanf("%d",&nbPisteursChoisi); //si renvoie 1 alors scanf a trouvé la saisie si non on reboucle
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

void Saisie_posPisteurs(int grillePersonnages[][LARGEUR_Map], pisteur tab[],int nbPisteursChoisi){
//BUT : demander à choisir la position de départ de chaque pisteurs
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

    MsgConsignes_Jeu(etatJeu); // on affiche les consignes de l'état saisiCoords

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



            //on vérifie que les coordonnées ne sont pas les mêmes que celles d'un autre pisteur
            //on reinit coordsIdentiques à faux:
            coordsIdentiques=faux;
            for(j=0;j<nbPisteursChoisi;j++){

                if((x==tab[j].coords.x)&&(y==tab[j].coords.y)){
                        coordsIdentiques=vrai;
                }
            }

            //on prévient l'utilisateur qu'il a entré les mêmes coordoonnées qu'un autre pisteur
            if(coordsIdentiques==vrai){
                nbTexte=erreur_CoordsIdentiques;
                AffichTexte(nbTexte,tab,0,0,0,0);
            }


        }while(coordsIdentiques==vrai);

        //on met en place les coords dans la grille :
        grillePersonnages[x-1][y-1]=nbCase;
        tab[i].coords.x=x;
        tab[i].coords.y=y;


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

        //on en sort une valeur aléatoire
        result=(rand()%(max-min+1)) + min;

        if(result<=chanceTir/10){ //si on obtient soit 1,2,3 ou 4 alors on est dans les 40% de tir.
        //alors que si on tombe sur 5,6,7,8,9,10 on est dans les 60% d'échouer
            //il réussi le tir
            nbTexte=nbTirReussi_TMonstre;
            //on enlève 1 pv au monstre :
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

void CheckCaseVoisine_Pisteur(int grillePerso[][LARGEUR_Map], int grilleTraces[][LARGEUR_Map], pisteur tabPisteur[], int nbPisteurs, monster *monstre,int chanceTir){
//BUT:checker toutes les cases voisines, les 8 et voir si monstre à côté, il y a des traces ou rien

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

    for(i=0;i<nbPisteurs;i++){

        x=tabPisteur[i].coords.x;
        y=tabPisteur[i].coords.y;
        //on oublie pas que les tableaux commencent à 0 et non 1, du coup on retire 1
        x=x-1;
        y=y-1;
        nbCase=nbMonstre;
        //on affiche le pisteur avec un !
        majElement_SurMap(x,y,tabPisteur[i].car_Verifie,16+i);





        //le monstre est à côté :
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
        //on remet l'affichage du pisteur par défaut

        majElement_SurMap(x,y,tabPisteur[i].car_Pisteur,16+i);
    }





}



void ChoixDistance(){
//BUT:choisir la distance de cases qu'on veut atteindre. MAX:4
}


void ChoixDirection(){
//BUT:choix de la direction dans laquelle part le pisteur : soit H B G D
}


void Deplcmt_Pisteur(){
//BUT:déplacer le pisteur
}


