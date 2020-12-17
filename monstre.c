#include "struct_const.h"
#include "monstre.h"


            //ATTENTION X ET Y NE SONT PAS EXACTEMENT LES COORDS MAIS LES COORDS-1 POUR COLLER AUX DONNEES DU TABLEAU ALLANT DE 0 à 13 ou 28
void Check8CasesVoisine_Monstre(int grillePerso[][LARGEUR_Map], int nbPist, int x, int y, booleanPerso *pcaseNonPisteur){
//BUT:checker si pisteur ou non sur les 8 cases lors de l'init

    booleanPerso caseNonPisteur=vrai;


    //check lors de l'init, on check donc sur les 8 cases. On se base sur 4 cases pour éviter plantage et après on regarde si l'en des une cases possible, il y a un pisteur


        if ((x>0) && (x<HAUTEUR_Map-1)){

            //or comme certaines positions ne disposent pas de quatres cases les entourant (les coins par exemple), il faut en tenir compte lors de la verification des
            // 'X' voisins et ainsi eviter le plantage du prog en placant des condtions
                if ((y>0) && (y<LARGEUR_Map-1)){

                    if((grillePerso[x-1][y]==nbPist)||(grillePerso[x+1][y]==nbPist) || (grillePerso[x][y-1]==nbPist) || (grillePerso[x][y+1]==nbPist)||(grillePerso[x-1][y-1]==nbPist)||(grillePerso[x-1][y+1]==nbPist)||(grillePerso[x+1][y+1]==nbPist)||(grillePerso[x+1][y-1]==nbPist)){
                        caseNonPisteur=faux;
                    }
                }
                else if(y==0){

                    if ((grillePerso[x-1][y]==nbPist) || (grillePerso[x+1][y]==nbPist) || (grillePerso[x][y+1]==nbPist)||(grillePerso[x-1][y+1]==nbPist)||(grillePerso[x+1][y+1]==nbPist)){
                        caseNonPisteur=faux;
                    }
                }
                else if (y==LARGEUR_Map-1){

                    if ((grillePerso[x-1][y]==nbPist) || (grillePerso[x+1][y]==nbPist) || (grillePerso[x][y-1]==nbPist)||(grillePerso[x-1][y-1]==nbPist)||(grillePerso[x+1][y-1]==nbPist)){
                        caseNonPisteur=faux;
                    }

                }
        }
        else if (x==0){

                if ((y>0) && (y<LARGEUR_Map-1)){

                     if  ((grillePerso[x+1][y]==nbPist) || (grillePerso[x][y-1]==nbPist) || (grillePerso[x][y+1]==nbPist)||(grillePerso[x+1][y+1]==nbPist)||(grillePerso[x+1][y-1]==nbPist)){
                        caseNonPisteur=faux;
                     }
                }
                else if(y==0){

                      if ((grillePerso[x+1][y]==nbPist) || (grillePerso[x][y+1]==nbPist)||(grillePerso[x+1][y+1]==nbPist)){
                        caseNonPisteur=faux;
                      }
                }
                else if (y==LARGEUR_Map-1){

                      if  ((grillePerso[x+1][y]==nbPist) || (grillePerso[x][y-1]==nbPist)||(grillePerso[x+1][y-1]==nbPist)){
                        caseNonPisteur=faux;
                      }
                }
        }
        else if (x==HAUTEUR_Map-1){

                if ((y>0) && (y<LARGEUR_Map-1)){

                     if  ((grillePerso[x-1][y]==nbPist) || (grillePerso[x][y-1]==nbPist) || (grillePerso[x][y+1]==nbPist)||(grillePerso[x-1][y-1]==nbPist)||(grillePerso[x-1][y+1]==nbPist)){
                        caseNonPisteur=faux;
                     }
                }
               else if (y==0){

                     if  ((grillePerso[x-1][y]==nbPist) || (grillePerso[x][y+1]==nbPist)||(grillePerso[x-1][y+1]==nbPist)){
                        caseNonPisteur=faux;
                     }
              }
              else if (y==LARGEUR_Map-1){

                     if  ((grillePerso[x-1][y]==nbPist) || (grillePerso[x][y-1]==nbPist)||(grillePerso[x-1][y-1]==nbPist)){
                        caseNonPisteur=faux;
                     }
              }

        }




      *pcaseNonPisteur=caseNonPisteur;


}


void Check4CasesVoisine_Monstre(int grillePerso[][LARGEUR_Map],int grilleTraces_Pisteurs[][LARGEUR_Map], historicTrace_Pisteur tabHistoricPist[], booleanPerso *pisteurEstLa,booleanPerso *traceEstLa,int nbTraceMax, int x,int y,int *pX, int *pY){

    //que check sur 4 cases. par contre on regarde si présence de pisteur ou de traces !!!
    *pisteurEstLa=faux;
    *traceEstLa=faux;

    //le pisteur se situe sur l'une des cases voisine
            //haut
        if(grillePerso[x-1][y]==nbPisteur){
            *pisteurEstLa=vrai;
            *pX=x;
            *pY=y+1;
        }
            //bas
        if(grillePerso[x+1][y]==nbPisteur){
            *pisteurEstLa=vrai;
            *pX=x+2;
            *pY=y+1;
        }
            //gauche
        if(grillePerso[x][y-1]==nbPisteur){
            *pisteurEstLa=vrai;
            *pX=x+1;
            *pY=y;
        }
            //droite
        if(grillePerso[x][y+1]==nbPisteur){
            *pisteurEstLa=vrai;
            *pX=x+1;
            *pY=y+2;
        }


        //Si ce n'est pas le cas, on regarde s'il y a des traces visibles de pisteurs:
        else if(*pisteurEstLa==faux){

            if ((x>0) && (x<HAUTEUR_Map-1)){

                if ((y>0) && (y<LARGEUR_Map-1)){

                        //Haut
                        if((grilleTraces_Pisteurs[x-1][y]>0)&&(grilleTraces_Pisteurs[x-1][y]<nbTraceMax)){
                            *traceEstLa=vrai;
                            tabHistoricPist[0].valeurTrace=grilleTraces_Pisteurs[x-1][y];
                            tabHistoricPist[0].coords.x=x;
                            tabHistoricPist[0].coords.y=y+1;

                        }

                        //Droite
                        if((grilleTraces_Pisteurs[x][y+1]>0)&&(grilleTraces_Pisteurs[x][y+1]<nbTraceMax)){
                            *traceEstLa=vrai;
                            tabHistoricPist[1].valeurTrace=grilleTraces_Pisteurs[x][y+1];
                            tabHistoricPist[1].coords.x=x+1;
                            tabHistoricPist[1].coords.y=y+2;

                        }

                        //Bas
                        if((grilleTraces_Pisteurs[x+1][y]>0)&&(grilleTraces_Pisteurs[x+1][y]<nbTraceMax)){
                            *traceEstLa=vrai;
                            tabHistoricPist[2].valeurTrace=grilleTraces_Pisteurs[x+1][y];
                            tabHistoricPist[2].coords.x=x+2;
                            tabHistoricPist[2].coords.y=y+1;
                        }

                        //Gauche
                        if((grilleTraces_Pisteurs[x][y-1]>0)&&(grilleTraces_Pisteurs[x][y-1]<nbTraceMax)){
                            *traceEstLa=vrai;
                            tabHistoricPist[3].valeurTrace=grilleTraces_Pisteurs[x][y-1];
                            tabHistoricPist[3].coords.x=x+1;
                            tabHistoricPist[3].coords.y=y;
                        }
                }
                else if(y==0){

                        //Haut
                        if((grilleTraces_Pisteurs[x-1][y]>0)&&(grilleTraces_Pisteurs[x-1][y]<nbTraceMax)){
                            *traceEstLa=vrai;
                            tabHistoricPist[0].valeurTrace=grilleTraces_Pisteurs[x-1][y];
                            tabHistoricPist[0].coords.x=x;
                            tabHistoricPist[0].coords.y=y+1;

                        }

                        //Droite
                        if((grilleTraces_Pisteurs[x][y+1]>0)&&(grilleTraces_Pisteurs[x][y+1]<nbTraceMax)){
                            *traceEstLa=vrai;
                            tabHistoricPist[1].valeurTrace=grilleTraces_Pisteurs[x][y+1];
                            tabHistoricPist[1].coords.x=x+1;
                            tabHistoricPist[1].coords.y=y+2;
                        }

                        //Bas
                        if((grilleTraces_Pisteurs[x+1][y]>0)&&(grilleTraces_Pisteurs[x+1][y]<nbTraceMax)){
                            *traceEstLa=vrai;
                            tabHistoricPist[2].valeurTrace=grilleTraces_Pisteurs[x+1][y];
                            tabHistoricPist[2].coords.x=x+2;
                            tabHistoricPist[2].coords.y=y+1;
                        }

                }
                else if (y==LARGEUR_Map-1){

                        //Haut
                        if((grilleTraces_Pisteurs[x-1][y]>0)&&(grilleTraces_Pisteurs[x-1][y]<nbTraceMax)){
                            *traceEstLa=vrai;
                            tabHistoricPist[0].valeurTrace=grilleTraces_Pisteurs[x-1][y];
                            tabHistoricPist[0].coords.x=x;
                            tabHistoricPist[0].coords.y=y+1;

                        }
                        //Bas
                        if((grilleTraces_Pisteurs[x+1][y]>0)&&(grilleTraces_Pisteurs[x+1][y]<nbTraceMax)){
                            *traceEstLa=vrai;
                            tabHistoricPist[1].valeurTrace=grilleTraces_Pisteurs[x+1][y];
                            tabHistoricPist[1].coords.x=x+2;
                            tabHistoricPist[1].coords.y=y+1;
                        }

                        //Gauche
                        if((grilleTraces_Pisteurs[x][y-1]>0)&&(grilleTraces_Pisteurs[x][y-1]<nbTraceMax)){
                            *traceEstLa=vrai;
                            tabHistoricPist[2].valeurTrace=grilleTraces_Pisteurs[x][y-1];
                            tabHistoricPist[2].coords.x=x+1;
                            tabHistoricPist[2].coords.y=y;
                        }



                }
            }
            else if (x==0){

                if ((y>0) && (y<LARGEUR_Map-1)){

                        //Droite
                        if((grilleTraces_Pisteurs[x][y+1]>0)&&(grilleTraces_Pisteurs[x][y+1]<nbTraceMax)){
                            *traceEstLa=vrai;
                            tabHistoricPist[0].valeurTrace=grilleTraces_Pisteurs[x][y+1];
                            tabHistoricPist[0].coords.x=x+1;
                            tabHistoricPist[0].coords.y=y+2;
                        }
                        //Bas
                        if((grilleTraces_Pisteurs[x+1][y]>0)&&(grilleTraces_Pisteurs[x+1][y]<nbTraceMax)){
                            *traceEstLa=vrai;
                            tabHistoricPist[1].valeurTrace=grilleTraces_Pisteurs[x+1][y];
                            tabHistoricPist[1].coords.x=x+2;
                            tabHistoricPist[1].coords.y=y+1;
                        }

                        //Gauche
                        if((grilleTraces_Pisteurs[x][y-1]>0)&&(grilleTraces_Pisteurs[x][y-1]<nbTraceMax)){
                            *traceEstLa=vrai;
                            tabHistoricPist[2].valeurTrace=grilleTraces_Pisteurs[x][y-1];
                            tabHistoricPist[2].coords.x=x+1;
                            tabHistoricPist[2].coords.y=y;
                        }

                }
                else if(y==0){

                        //Droite
                        if((grilleTraces_Pisteurs[x][y+1]>0)&&(grilleTraces_Pisteurs[x][y+1]<nbTraceMax)){
                            *traceEstLa=vrai;
                            tabHistoricPist[0].valeurTrace=grilleTraces_Pisteurs[x][y+1];
                            tabHistoricPist[0].coords.x=x+1;
                            tabHistoricPist[0].coords.y=y+2;
                        }

                        //Bas
                        if((grilleTraces_Pisteurs[x+1][y]>0)&&(grilleTraces_Pisteurs[x+1][y]<nbTraceMax)){
                            *traceEstLa=vrai;
                            tabHistoricPist[1].valeurTrace=grilleTraces_Pisteurs[x+1][y];
                            tabHistoricPist[1].coords.x=x+2;
                            tabHistoricPist[1].coords.y=y+1;
                        }

                }
                else if (y==LARGEUR_Map-1){

                        //Bas
                        if((grilleTraces_Pisteurs[x+1][y]>0)&&(grilleTraces_Pisteurs[x+1][y]<nbTraceMax)){
                            *traceEstLa=vrai;
                            tabHistoricPist[0].valeurTrace=grilleTraces_Pisteurs[x+1][y];
                            tabHistoricPist[0].coords.x=x+2;
                            tabHistoricPist[0].coords.y=y+1;
                        }

                        //Gauche
                        if((grilleTraces_Pisteurs[x][y-1]>0)&&(grilleTraces_Pisteurs[x][y-1]<nbTraceMax)){
                            *traceEstLa=vrai;
                            tabHistoricPist[1].valeurTrace=grilleTraces_Pisteurs[x][y-1];
                            tabHistoricPist[1].coords.x=x+1;
                            tabHistoricPist[1].coords.y=y;
                        }


                }
            }
            else if (x==HAUTEUR_Map-1){

                if ((y>0) && (y<LARGEUR_Map-1)){

                        //Haut
                        if((grilleTraces_Pisteurs[x-1][y]>0)&&(grilleTraces_Pisteurs[x-1][y]<nbTraceMax)){
                            *traceEstLa=vrai;
                            tabHistoricPist[0].valeurTrace=grilleTraces_Pisteurs[x-1][y];
                            tabHistoricPist[0].coords.x=x;
                            tabHistoricPist[0].coords.y=y+1;

                        }

                        //Droite
                        if((grilleTraces_Pisteurs[x][y+1]>0)&&(grilleTraces_Pisteurs[x][y+1]<nbTraceMax)){
                            *traceEstLa=vrai;
                            tabHistoricPist[1].valeurTrace=grilleTraces_Pisteurs[x][y+1];
                            tabHistoricPist[1].coords.x=x+1;
                            tabHistoricPist[1].coords.y=y+2;
                        }
                        //Gauche
                        if((grilleTraces_Pisteurs[x][y-1]>0)&&(grilleTraces_Pisteurs[x][y-1]<nbTraceMax)){
                            traceEstLa=vrai;
                            tabHistoricPist[2].valeurTrace=grilleTraces_Pisteurs[x][y-1];
                            tabHistoricPist[2].coords.x=x+1;
                            tabHistoricPist[2].coords.y=y;
                        }
                }
               else if (y==0){
                        //Haut
                        if((grilleTraces_Pisteurs[x-1][y]>0)&&(grilleTraces_Pisteurs[x-1][y]<nbTraceMax)){
                            *traceEstLa=vrai;
                            tabHistoricPist[0].valeurTrace=grilleTraces_Pisteurs[x-1][y];
                            tabHistoricPist[0].coords.x=x;
                            tabHistoricPist[0].coords.y=y+1;

                        }

                        //Droite
                        if((grilleTraces_Pisteurs[x][y+1]>0)&&(grilleTraces_Pisteurs[x][y+1]<nbTraceMax)){
                            *traceEstLa=vrai;
                            tabHistoricPist[1].valeurTrace=grilleTraces_Pisteurs[x][y+1];
                            tabHistoricPist[1].coords.x=x+1;
                            tabHistoricPist[1].coords.y=y+2;
                        }
               }
               else if (y==LARGEUR_Map-1){

                        //Haut
                        if((grilleTraces_Pisteurs[x-1][y]>0)&&(grilleTraces_Pisteurs[x-1][y]<nbTraceMax)){
                            *traceEstLa=vrai;
                            tabHistoricPist[0].valeurTrace=grilleTraces_Pisteurs[x-1][y];
                            tabHistoricPist[0].coords.x=x;
                            tabHistoricPist[0].coords.y=y+1;

                        }

                        //Gauche
                        if((grilleTraces_Pisteurs[x][y-1]>0)&&(grilleTraces_Pisteurs[x][y-1]<nbTraceMax)){
                            *traceEstLa=vrai;
                            tabHistoricPist[1].valeurTrace=grilleTraces_Pisteurs[x][y-1];
                            tabHistoricPist[1].coords.x=x+1;
                            tabHistoricPist[1].coords.y=y;
                        }
              }

            }

        }

}






//INIT Monstre________________________________________

//Position de départ MONSTRE--------------------------
void Init_Pos_DepartMonstre(int grillePersonnage[][LARGEUR_Map],int grilleTraces, monster *monstre, pisteur tabPisteur[], int nbPisteurChoisi, int monstrePV, int nouvelleTrace, int retireTrace, int nbToursPos, char carBlessure, char carMonstre){
//BUT:positioner ke monstre sur une case différente et non voisine de celle des pisteurs
//ENTREE:
//SORTIE:

    boolean enVie=vrai;
    int nbAleatoire;
    int x;
    int y;
    int i;
    int j;
    int min;
    int max;
    booleanPerso casesVoisines_vides=vrai;
    booleanPerso caseNonPisteur=vrai;
    caseNb nbCase=nbMonstre;
    texteNb nbTexte;


    //init des variables associées au monstre : chiffres et car
    //monstre->estVivant=enVie;
    monstre->vieRestante=monstrePV;
    monstre->tracesFraiches=nouvelleTrace;
    monstre->traceEnMoins=retireTrace;
    monstre->toursBlessureRestante=nbToursPos;
    monstre->car_Monstre=carMonstre;
    monstre->ptBlessure=carBlessure;
    monstre->estBlesse=faux;
    monstre->ancienCoords.x=-1;
    monstre->ancienCoords.y=-1;



    //puis on passe à la création des coordoonées de départ
        //on génère des coods et on check si celles-ci ne sont pas voisines ou autour de celles des pisteurs


    do{
        casesVoisines_vides=vrai;
        caseNonPisteur=vrai;

                //X:
        max=HAUTEUR_Map;
        min=1;
        x=(rand()%(max-min+1)) + min;//nb aléatoire entre 1 et 14

                //Y:
        max=LARGEUR_Map;
        min=1;
        y=(rand()%(max-min+1)) + min;//nb aléatoire entre 1 et 29



                //check cases :
        for(i=0;i<nbPisteurChoisi;i++){
            //on check si case select il n'y a pas de pisteurs
            if((tabPisteur[i].coords.x==x) && (tabPisteur[i].coords.y==y)){

                caseNonPisteur=faux;// si les coordoonéees générées tombent sur une case de pisteur alors faux
            }
        }
        //sinon on check qu'il n'y a pas de pisteur sur les 8 cases voisines
        Check8CasesVoisine_Monstre(grillePersonnage,nbPisteur,x-1,y-1,&caseNonPisteur);



    }while(caseNonPisteur==faux);





    //position de départ du monstre validée :
    monstre->coords.x=x;
    monstre->coords.y=y;

    //on ajoute le monstre dans la grille :
    grillePersonnage[x-1][y-1]=nbCase;

    //enfin on appose la première trace du monstre:
    AjoutTrace_Monstre(*monstre,grilleTraces);

    //on précise au joueur que le monstre est entré :
    nbTexte=nbPos_TDepartMonstre;
    AffichTexte(nbTexte);
}





//JEU________________________________________________


//Traces du monstre à ajouter et enlever progressivement--------------------------
void AjoutTrace_Monstre(monster monstre, int grilleTraces_Monstre[][LARGEUR_Map]){
//BUT: on ajoute le nb 16 à l'ancienne position du monstre
//ENTREE: les var du monstre, et le tableau qui fait l'historique des traces
//SORTIE:tab traces avec nb ajouté dedans

    grilleTraces_Monstre[monstre.coords.x-1][monstre.coords.y-1]=monstre.tracesFraiches;

}

void EffacementTraces_Monstre(int grilleTraces_Monstre[][LARGEUR_Map], int retire){
//BUT:enlever à chaque tour un pt de trace jusqu'à diparaitre quand la valeur 0 atteinte

    int i;
    int j;

    for(i=0;i<HAUTEUR_Map;i++){
        for(j=0;j<LARGEUR_Map;j++){

                if(grilleTraces_Monstre[i][j]>0){

                    grilleTraces_Monstre[i][j]=grilleTraces_Monstre[i][j]-retire; //on retire 1
                }

        }
    }
}



//manger pisteur :--------------------------------------------------------------------
void MangerPisteur(int grillePersos[][LARGEUR_Map], pisteur tabPisteur[], int indexTab,monster monstre, int nbDegatMonstre){
//BUT:Si case avec pisteir, le monstre le tue et prend sa place

    caseNb nbCase;
    texteNb nbTexte;

    //on retire 1 PV au pisteur
    tabPisteur[indexTab].vieRestante=tabPisteur[indexTab].vieRestante-nbDegatMonstre;


    //si il n'a plus de pv on indique qu'il est mort
    if(tabPisteur[indexTab].vieRestante==0){

        tabPisteur[indexTab].estVivant=faux;
            //on mets les ccoords du pisteur en question en off
        tabPisteur[indexTab].coords.x=-1;
        tabPisteur[indexTab].coords.y=-1;
            //on affiche la mort du pisteur en question :
        nbTexte=nbManger_TPisteur;
        AffichTexte(nbTexte,tabPisteur,indexTab,0,0,0);
        getchar();
    }


    //on n'oublie pas de mettre le monstre sur la grillePersonnages s'il a été écrasé par le pisteur
    nbCase=nbMonstre;
    grillePersos[monstre.coords.x-1][monstre.coords.y-1]=nbCase; //-1 car plage allant de 0 à ... et non commence à ppartir de 1

}

void PisteurEst_CaseMonstre(int grillePersos[][LARGEUR_Map], monster monstre, int nbDegatMonstre, pisteur tabPisteur[],int nbPisteursChoisi){
//BUT:on vérifie si le pisteur se trouve sur la même case du monstre ou que le monstre a bien atterit sur sa case

    int i;

    for(i=0;i<nbPisteursChoisi;i++){

        if((tabPisteur[i].coords.x==monstre.coords.x)&&(tabPisteur[i].coords.y==monstre.coords.y)){
            //si les coordoonnees coorespondent c'est que le pisteur et le monstre se rencontrent face à face et se fait manger par ce dernier
            MangerPisteur(grillePersos,tabPisteur,i,monstre,nbDegatMonstre);
        }
    }


}


//Déplacement du monstre après première position---------------------------------------
void Deplcmt_Monstre(int grillePersos[][LARGEUR_Map], int grilleTracesPist[][LARGEUR_Map],int grilleTracesMonstre[][LARGEUR_Map], int tabPisteurs[], int nbPisteursChoisi, int nbTracesMax,int nbDegats_Monstre, monster monstre, monster *pMonstre,state etatJeu){
//BUT:Le monstre se déplace. Pour cela il checke si pas pisteur voisin,puis pose trace(16) sur ancienne case : appel fcts

    int i;
    int x;
    int y;
    int xNew=0;
    int yNew=0;
    int minDirection=1;
    int maxDirection=4;
    directions nbDirection;
    caseNb nbCase;
    booleanPerso caseVoisine_Pisteur=faux;
    booleanPerso caseVoisine_Trace=faux;
    booleanPerso directionEstPossible=faux;



    //on affiche la consigne de déplacement du monstre
    MsgConsignes_Jeu(etatJeu);
    getchar();
        getchar();


    //init :
    x=monstre.coords.x;
    y=monstre.coords.y;

    historicTrace_Pisteur tabHistoric_Pisteurs[4];
    for(i=0;i<4;i++){
        tabHistoric_Pisteurs[i].valeurTrace=0;
        tabHistoric_Pisteurs[i].coords.x=0;
        tabHistoric_Pisteurs[i].coords.y=0;
    }




    //on CHECK les quatre cases autour
        //on appelel fct x-1,y-1,&caseVoisine_Pisteur/&caseVoisine_Trace,&xNew,&yNew
    Check4CasesVoisine_Monstre(grillePersos,grilleTracesPist,tabHistoric_Pisteurs,&caseVoisine_Pisteur,&caseVoisine_Trace,nbTracesMax,x-1,y-1,&xNew,&yNew);






    //pisteur sur direction voisine
    if(caseVoisine_Pisteur==vrai){

        nbCase=nbMonstre;
        grillePersos[xNew-1][yNew-1]=nbMonstre;

        pMonstre->coords.x=xNew;
        pMonstre->coords.y=yNew;
        monstre.coords.x=xNew;//on rempli aussi le monsre non pointeur pour l'envoyer dans la fct ci-dessous
        monstre.coords.y=yNew;

        PisteurEst_CaseMonstre(grillePersos,monstre,nbDegats_Monstre,tabPisteurs,nbPisteursChoisi);
    }



    //trace voisine
    else if(caseVoisine_Pisteur==faux && caseVoisine_Trace==vrai){
        //on a un tableau prenant la valeur trace de chaque case voisine et leurs coordoonéees, on les compare et celui ayant la valeur la plus grande on en tire les coords
        int V=0;
        for(i=0;i<4;i++){

            if(V<tabHistoric_Pisteurs[i].valeurTrace){
                    //on compare le plus petit au plus grand et on stocke le plus grand
                V=tabHistoric_Pisteurs[i].valeurTrace;
                xNew=tabHistoric_Pisteurs[i].coords.x;
                yNew=tabHistoric_Pisteurs[i].coords.y;
            }
        }
        grillePersos[xNew-1][yNew-1]=nbMonstre;
        pMonstre->coords.x=xNew;
        pMonstre->coords.y=yNew;
        monstre.coords.x=xNew;//on rempli aussi le monsre non pointeur pour l'envoyer dans la fct ci-dessous
        monstre.coords.y=yNew;
    }



    //rien donc direction aléatoire prise
    else{
        //random des quatre directions
        do{
            nbDirection=(rand()%(maxDirection-minDirection+1)) + minDirection;//nb aléatoire entre 1 et 4
            switch (nbDirection){

                case haut://1
                    xNew=x-1;
                    yNew=y;
                break;

                case droite://2
                    xNew=x;
                    yNew=y+1;
                break;

                case bas://3
                    xNew=x+1;
                    yNew=y;
                break;

                case gauche://4
                    xNew=x;
                    yNew=y-1;
                break;
            }
            //on verifie si coord possible
            if(((xNew>0) && (xNew<HAUTEUR_Map+1))  &&  ((yNew>0)&&(yNew<LARGEUR_Map+1))){
                directionEstPossible=vrai;
            }
        }while(directionEstPossible==faux);

        //on stocke tout
        nbCase=nbMonstre;
        grillePersos[xNew-1][yNew-1]=nbMonstre;
        pMonstre->coords.x=xNew;
        pMonstre->coords.y=yNew;
        monstre.coords.x=xNew;//on rempli aussi le monsre non pointeur pour l'envoyer dans la fct ci-dessous
        monstre.coords.y=yNew;

    }

    //on enleve le nbMonstre sur l'ancienne position du tableau grille :
    grillePersos[x-1][y-1]=0;
    //on ajoute l'ancienne pos au cas ou si le monstre se fait blesser : affichage point blessure derniere pos
    pMonstre->ancienCoords.x=x;
    pMonstre->ancienCoords.y=y;
    //on ajoute la nouvelle trace du monstre
    AjoutTrace_Monstre(monstre,grilleTracesMonstre);

}


void MonstreTouche(int grillePersos[][LARGEUR_Map], monster monstre, monster *pMonstre,int nbToursBlessure){
//BUT: le monstre est touché, alors il perd un pt de vie (dans proc TirerMonstre->pisteurs.c) , et indication dernier endroit séjourné pendant 4 tours de jeu
    int i;
    int j;
    caseNb nbCase=nbpointPos_Monstre;


    if(monstre.estBlesse==vrai){
        pMonstre->toursBlessureRestante=monstre.toursBlessureRestante-1;
        grillePersos[monstre.ancienCoords.x-1][monstre.ancienCoords.y-1]=nbCase;
    }

    if(monstre.toursBlessureRestante<=0){
        pMonstre->estBlesse=faux;
        pMonstre->toursBlessureRestante=nbToursBlessure;

        for(i=0;i<HAUTEUR_Map;i++){
            for(j=0;j<LARGEUR_Map;j++){
                if(grillePersos[i][j]==nbCase){
                    grillePersos[i][j]=0;
                }
            }
        }
    }


}

void MonstreEnVie(monster *monstre){

    if(monstre->vieRestante<=0){
        monstre->estVivant=faux;
    }
}


void ModeDebug_Monstre(monster *monstre){
//BUT:Activer ou non le debug du monstre : cararctere visible ou non

    char car;
    texteNb nbTexte=nbDebug_TMonstre;

    AffichTexte(nbTexte,0,0,0,0,0);
    do{
        scanf("%c",&car);
        if((car!='o')&&(car!='O')&&(car!='n')&&(car!='N')){
            nbTexte=nb_TErreur;
            AffichTexte(nbTexte,0,0,0,0,0);
        }
    }while((car!='o')&&(car!='O')&&(car!='n')&&(car!='N'));



    if((car=='o')||(car=='O')){
         monstre->debugMonstre=vrai;
    }
    else{
       monstre->debugMonstre=faux;
    }




}
