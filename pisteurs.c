#include "struct_const.h"
#include "pisteurs.h"


//SAISIE : INIT _________________________________________________


//Saisie NB Pisteurs :--------------------------------

void Saisie_NBPisteurs(pisteur tab[], int *nbPisteursChoisi, int min, int max, char carAttente, char carVerif, char carPisteur, int maxLettres){
//BUT:Demander en début de partie le nb de pisteurs qu'il y aura dans le jeu
//ENTREE:RAS
//SORTIE:Nb pisteurs

    int i;
    texteNb nbTexte;
    booleanPerso pisteurEnVie=vrai;


    //on demande à saisir le fameux nombre
    nbTexte=nbSaisie_TPisteur;
    AffichTexte(nbTexte); //on paramètre la valeur corsspondant au texte à afficher ds proc : AfficTexte
    do{

        scanf("%d",&nbPisteursChoisi);
        if ((nbPisteursChoisi<min)||(nbPisteursChoisi>max)){

            nbTexte=nb_TErreur;
            AffichTexte(nbTexte);
        }

    }while((nbPisteursChoisi<min)||(nbPisteursChoisi>max));


    //on rempli le tab contenant les pisteurs du jeu
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

         printf("%s",tab[i].nom);
    }


}

//Saisie position pisteur en x et y-------------------

void Saisie_posPisteurs(int grillePersonnages[][LARGEUR_Map], pisteur tab[],int nbPisteursChoisi){
//BUT : demander à choisir la position de départ de chaque pisteurs
//ENTREE:NB de pisteurs
//SORTIE:coord position de chaque pisteur

    texteNb nbTexte;
    caseNb nbCase=nbPisteur;
    int x;
    int y;
    int i;


    for(i=0;i<nbPisteursChoisi;i++){
        //on demande les coords :

            //X
            nbTexte=nbPos_TPisteurX;
            AffichTexte(nbTexte);
            do{
                scanf("%d",&x);
                if((x>HAUTEUR_Map)||(x<1)){
                    nbTexte=nb_TErreur;
                    AffichTexte(nbTexte);
                }

            }while((x>HAUTEUR_Map)||(x<1));


            //Y
            nbTexte=nbPos_TPisteurY;
            AffichTexte(nbTexte);
            do{
                scanf("%d",&y);
                if((y>LARGEUR_Map) ||(y<1)){
                    nbTexte=nb_TErreur;
                    AffichTexte(nbTexte);
                }

            }while((y>LARGEUR_Map)||(y<1));




        //on met en place les coords dans la grille :

            grillePersonnages[x-1][y-1]=nbCase;
            tab[i].coords.x=x;
            tab[i].coords.y=y;

    }

}





//JEU _______________________________________________________________________

void Tirer_SurMonstre(){
//BUT:on peut tirer sur le monstre ou non. Au choix
}

void CheckCaseVoisine_Pisteur(){
//BUT:checker toutes les cases voisines, les 8


    //il n'y a rien :

    //traces visibles

    //le monstre est à côté :
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


