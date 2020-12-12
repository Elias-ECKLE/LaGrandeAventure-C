#ifndef STRUCT_CONST_H_INCLUDED
#define STRUCT_CONST_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h> //on inclut une biblio pour utiliser la fct aléatoire


//CONSTANTES A MODIFIER_____________________________________________________

#define LARGEUR_Map 29
#define HAUTEUR_Map 14
#define NB_CasesMap 406
#define CAR_DelimitationMap '*'



#define CHANCE_ReussirTir 40
#define NB_DistanceMax 4
#define NB_PisteursMin 1
#define NB_PisteursMax 10
#define NB_PisteurPV 1
#define NB_LettresNom 10
#define CAR_Pisteur 'P'
#define CAR_PisteurVerifie '!'
#define CAR_PisteurEnAttente '?'


#define NB_MonstrePV 4
#define NB_NouvelleTrace 16
#define NB_RetireTrace 1
#define NB_ToursPoint_DernierePos 4
#define CAR_Blessure_DernierePos '.'
#define CAR_Monstre 'M'


//ENUM:___________________________________________________________________
typedef enum state{

    debut,
    debut_SaisieCoords,
    pisteurs_VerifVoisine,
    dplmtPisteurs,
    dplmtMonstre,
    fin

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

    nb_TErreur

}texteNb;

typedef enum directions{

    haut=1,
    droite=2,
    bas=3,
    gauche=4

}direction;

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
    pointPos_Monstre=3

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
    char car_Pisteur;
    char car_Verifie;
    char car_EnAttente;
    char nom[NB_LettresNom];

}pisteur;


typedef struct monster{

    coordXY coords;
    int vieRestante;
    int tracesFraiches;
    int traceEnMoins;
    boolean estVivant;
    int toursBlessureRestante;
    char ptBlessure;
    char car_Monstre;

}monster;





#endif // STRUCT_CONST_H_INCLUDED
