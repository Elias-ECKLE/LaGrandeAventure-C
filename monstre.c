#include "struct_const.h"
#include "monstre.h"


            //ATTENTION X ET Y NE SONT PAS EXACTEMENT LES COORDS MAIS LES COORDS-1 POUR COLLER AUX DONNEES DU TABLEAU ALLANT DE 0 à 13 ou 28
void CheckCasesVoisine_Monstre(int grillePerso[][LARGEUR_Map], int nbPist, int checkCases_nbChoix, int x, int y, booleanPerso *pcaseNonPisteur){
//BUT:checker si pisteur ou non sur les 8 cases lors de l'init, et sur les 4 cases lors de déplacement

    booleanPerso caseNonPisteur=vrai;
    //check lors de l'init, on check donc sur les 8 cases. On se base sur 4 cases pour éviter plantage et après on regarde si l'en des une cases possible, il y a un pisteur
    if(checkCases_nbChoix==0){

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

    }




    //que check sur 4 cases
    if(checkCases_nbChoix==1){


        if ((x>0) && (x<HAUTEUR_Map-1)){

            //or comme certaines positions ne disposent pas de quatres cases les entourant (les coins par exemple), il faut en tenir compte lors de la verification des
            // 'X' voisins et ainsi eviter le plantage du prog en placant des condtions
                if ((y>0) && (y<LARGEUR_Map-1)){

                    if((grillePerso[x-1][y]==nbPist)||(grillePerso[x+1][y]==nbPist) || (grillePerso[x][y-1]==nbPist) || (grillePerso[x][y+1]==nbPist)){
                        caseNonPisteur=faux;
                    }
                }
                else if(y==0){

                    if ((grillePerso[x-1][y]==nbPist) || (grillePerso[x+1][y]==nbPist) || (grillePerso[x][y+1]==nbPist)){
                        caseNonPisteur=faux;
                    }
                }
                else if (y==LARGEUR_Map-1){

                    if ((grillePerso[x-1][y]==nbPist) || (grillePerso[x+1][y]==nbPist) || (grillePerso[x][y-1]==nbPist)){
                        caseNonPisteur=faux;
                    }

                }
        }
        else if (x==0){

                if ((y>0) && (y<LARGEUR_Map-1)){

                     if  ((grillePerso[x+1][y]==nbPist) || (grillePerso[x][y-1]==nbPist) || (grillePerso[x][y+1]==nbPist)){
                        caseNonPisteur=faux;
                     }
                }
                else if(y==0){

                      if ((grillePerso[x+1][y]==nbPist) || (grillePerso[x][y+1]==nbPist)){
                        caseNonPisteur=faux;
                      }
                }
                else if (y==LARGEUR_Map-1){

                      if  ((grillePerso[x+1][y]==nbPist) || (grillePerso[x][y-1]==nbPist)){
                        caseNonPisteur=faux;
                      }
                }
        }
        else if (x==HAUTEUR_Map-1){

                if ((y>0) && (y<LARGEUR_Map-1)){

                     if  ((grillePerso[x-1][y]==nbPist) || (grillePerso[x][y-1]==nbPist) || (grillePerso[x][y+1]==nbPist)){
                        caseNonPisteur=faux;
                     }
                }
               else if (y==0){

                     if  ((grillePerso[x-1][y]==nbPist) || (grillePerso[x][y+1]==nbPist)){
                        caseNonPisteur=faux;
                     }
              }
              else if (y==LARGEUR_Map-1){

                     if  ((grillePerso[x-1][y]==nbPist) || (grillePerso[x][y-1]==nbPist)){
                        caseNonPisteur=faux;
                     }
              }

         }
    }
    *pcaseNonPisteur=caseNonPisteur;

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
    monstre->estVivant=enVie;
    monstre->vieRestante=monstrePV;
    monstre->tracesFraiches=nouvelleTrace;
    monstre->traceEnMoins=retireTrace;
    monstre->toursBlessureRestante=nbToursPos;
    monstre->car_Monstre=carMonstre;
    monstre->ptBlessure=carBlessure;


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
        //sinon on check qu'il n'y a pas de pisteur sur les cases voisines
        CheckCasesVoisine_Monstre(grillePersonnage,nbPisteurChoisi,0,x-1,y-1,&caseNonPisteur);



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
void Deplcmt_Monstre(){
//BUT:Le monstre se déplace. Pour cela il checke si pas pisteur voisin,puis pose trace(16) sur ancienne case : appel fcts

    //on CHECK les quatre cases autour

    //DEPLACEMENT
    //si case voisine il y a pisteur on va dessus et on appelle PisteurEst_CaseMonstre

    //si traces on va sur la plus fraiche, numero le plus près de 16 dans la limite du tableau

    //sinon on prend une des quatre cases au pif et on va dessus

}


void MonstreTouche(){
//BUT: le monstre est touché, alors il perd un pt de vie (dans proc TirerMonstre->pisteurs.c) , et indication dernier endroit séjourné pendant 4 tours de jeu
}
