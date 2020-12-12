#include "struct_const.h"
#include "monstre.h"


            //ATTENTION X ET Y NE SONT PAS EXACTEMENT LES COORDS MAIS LES COORDS-1 POUR COLLER AUX DONNEES DU TABLEAU ALLANT DE 0 à 13 ou 28
void CheckCasesVoisine_Monstre(int grillePerso[][LARGEUR_Map], int nbPist, int checkCases_nbChoix, int x, int y, booleanPerso *pcaseNonPisteur){
//BUT:checker si pisteur ou non sur les 8 cases lors de l'init, et sur les 4 cases lors de déplacement

    booleanPerso caseNonPisteur=vrai;
    //check lors de l'init, on check donc sur les 8 cases. On se base sur 4 cases pour éviter plantage et après on regarde si l'en des une cases possible, il y a un pisteur
    if(checkCases_nbChoix==0){

        if ((x>0) || (x<HAUTEUR_Map-1)){

            //or comme certaines positions ne disposent pas de quatres cases les entourant (les coins par exemple), il faut en tenir compte lors de la verification des
            // 'X' voisins et ainsi eviter le plantage du prog en placant des condtions
                if ((y>0) || (y<LARGEUR_Map-1)){

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

                if ((y>0) || (y<LARGEUR_Map-1)){

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

                if ((y>0) || (y<LARGEUR_Map-1)){

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


        if ((x>0) || (x<HAUTEUR_Map-1)){

            //or comme certaines positions ne disposent pas de quatres cases les entourant (les coins par exemple), il faut en tenir compte lors de la verification des
            // 'X' voisins et ainsi eviter le plantage du prog en placant des condtions
                if ((y>0) || (y<LARGEUR_Map-1)){

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

                if ((y>0) || (y<LARGEUR_Map-1)){

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

                if ((y>0) || (y<LARGEUR_Map-1)){

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


        x=8;
        y=8;


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
void AjoutTrace_Monstre(monster monstre, int grilleTraces[][LARGEUR_Map]){
//BUT: on ajoute le nb 16 à l'ancienne position du monstre
//ENTREE: les var du monstre, et le tableau qui fait l'historique des traces
//SORTIE:tab traces avec nb ajouté dedans

    grilleTraces[monstre.coords.x-1][monstre.coords.y-1]=monstre.tracesFraiches;

}

void EffacementTraces_Monstre(int grilleTraces[][LARGEUR_Map], int retire){
//BUT:enlever à chaque tour un pt de trace jusqu'à diparaitre quand la valeur 0 atteinte

    int i;
    int j;

    for(i=0;i<HAUTEUR_Map;i++){
        for(j=0;j<LARGEUR_Map;j++){

                if(grilleTraces[i][j]>0){

                    grilleTraces[i][j]=grilleTraces[i][j]-retire; //on retire 1
                }

        }
    }
}


//manger pisteur :--------------------------------------------------------------------
void MangerPisteur(){
//BUT:Si case avec pisteir, il le tue
}

//Déplacement du monstre après première position---------------------------------------
void Deplcmt_Monstre(){
//BUT:Le monstre se déplace. Pour cela il checke si pas pisteur voisin,puis pose trace(16) sur ancienne case : appel fcts
}


void MonstreTouche(){
//BUT: le monstre est touché, alors il perd un pt de vie, et indication dernier endroit séjourné pendant 4 tours de jeu
}
