#ifndef STRUCT_CONST_H_INCLUDED
#define STRUCT_CONST_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h> //on inclut une biblio pour utiliser la fct aléatoire


//CONSTANTES A MODIFIER_____________________________________________________

//donnees map
#define LARGEUR_Map 29
#define HAUTEUR_Map 14
#define NB_CasesMap 406
#define CAR_DelimitationMap '*'

//doonnes communes :
#define NB_NouvelleTrace 16
#define NB_RetireTrace 1

//donnees pisteurs
#define CHANCE_ReussirTir 40//40% de chance de toucher le monstre
#define NB_DistanceMax 4 //distance de déplacement maximal du pisteur
#define NB_PisteursMin 1    //nb de pisteurs minimal
#define NB_PisteursMax 10   //nb de pisteurs maximal
#define NB_Degat_Pisteur 1 //nb de degats que va donner le pisteur en tirant sur le monstre
#define NB_PisteurPV 1      //vie des pisteurs
#define NB_LettresNom 10       //longueur de caractères max pour le nom des pisteurs
#define CAR_Pisteur 'P'
#define CAR_PisteurVerifie '!'
#define CAR_PisteurEnAttente '?'

//donnees monstre
#define NB_Degat_Monstre 1      //degats que donne le monstre au pisteur
#define NB_MonstrePV 4  //vie du monstre
#define NB_ToursPoint_DernierePos 4
#define CAR_Blessure_DernierePos '.'
#define CAR_Monstre 'M'     //car monstre d'affichage dans le mode Debug


//ENUM:___________________________________________________________________
typedef enum state{

    debut,
    debut_SaisieCoords,
    pisteurs_VerifVoisine,
    dplmtPisteurs,
    dplmtMonstre,
    rebouclePartie,
    victoirePisteurs,
    victoireMonstre

}state;

typedef enum texteNb{

    nbSaisie_TPisteur=0,

    nbPos_TPisteurX,
    nbPos_TPisteurY,
    erreur_CoordsIdentiques,

    nbPos_TDepartMonstre,

    nbTirer_TMonstre,
    nbTirLoupe_TMonstre,
    nbTirReussi_TMonstre,

    nbMonstre_TCaseVoisine,
    nbTraces_TCaseVoisine,
    nbRAS_TCaseVoisine,

    nbChoix_TDistance,
    nbChoix_Erreur_TDistance,
    nbChoix_TDirection,
    nbChoix_Erreur_TDirection,
    nbDplmt_TPisteur,

    nbManger_TPisteur,
    nbDplmt_TMonstre,
    nbMonstre_TTouche,

    nbDebug_TMonstre,
    nb_TErreur

}texteNb;

typedef enum directions{

    haut=1,
    droite=2,
    bas=3,
    gauche=4

}directions;

typedef enum caseAutour{

    diagH_G=1,
    auDessus=2,
    diagH_D=3,
    aDroite=4,
    diagB_D=5,
    enBas=6,
    diagB_G=7,
    aGauche=8

}caseAutour;

typedef enum booleanPerso{

    faux=0,
    vrai

}booleanPerso;

typedef enum caseNb{

    nbInit=0,
    nbPisteur=1199,
    nbMonstre=2199,
    nbpointPos_Monstre=3199

}caseNb;


//TYPES STRUCTURES :______________________________________________________


typedef struct coordXY{

    int x;
    int y;

}coordXY;


typedef struct pisteur{

    coordXY coords;
    boolean estVivant;
    int vieRestante;
    int tracesFraiches;
    int tracesEnMoins;
    char car_Pisteur;
    char car_Verifie;
    char car_EnAttente;
    char nom[NB_LettresNom];

}pisteur;


typedef struct monster{

    coordXY coords;
    coordXY ancienCoords;
    int vieRestante;
    int tracesFraiches;
    int traceEnMoins;
    boolean estVivant;
    int toursBlessureRestante;
    boolean estBlesse;
    boolean debugMonstre;
    char ptBlessure;
    char car_Monstre;

}monster;

typedef struct historicTrace_Pisteur{
    int valeurTrace;
    coordXY coords;
}historicTrace_Pisteur;





#endif // STRUCT_CONST_H_INCLUDED
