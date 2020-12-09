#ifndef DEFINE_H_INCLUDED
#define DEFINE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>


//CONSTANTES A MODIFIER_____________________________________________________

#define LARGEUR_Map 29
#define HAUTEUR_Map 14
#define NB_CasesMap 406
#define CAR_DelimitationMap '*'


#define CHANCE_ReussirTir 40
#define NB_DistanceMax 4
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


//ENUM:___________________________________________________________________
typedef enum state{

    debut,
    pisteurs_VerifVoisine,
    dplmtPisteurs,
    dplmtMonstre,
    fin

}state;

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

typedef enum boolean{

    faux=0,
    vrai

}boolean;

typedef enum caseNb{

    pisteur=0,
    monstre=1,
    pointPos_Monstre=2

}caseNb;


//TYPES STRUCTURES :______________________________________________________

typedef struct typeMap{

    int personnages[LARGEUR_Map][HAUTEUR_Map];
    int traces[LARGEUR_Map][HAUTEUR_Map];

}typeMap;


typedef struct coordXY{

    int x;
    int y;

}coordXY;


typedef struct pisteur{

    coordXY coords;
    boolean estVivant;
    char car_Pisteur;
    char car_Verifie;
    char car_EnAttente;
    char nom[NB_LettresNom];

}pisteur;


typedef struct monster{

    coordXY coords;
    int vieRestante;
    boolean estVivant;
    int toursBlessureRestante;
    char ptBlessure;
    char car_Monstre;

}monstre;














//PROTOTYPES PROCEDURES & FONCTIONS repartis en fichiers.h_____________________________________________

#include "pisteurs.h"
#include "monstre.h"
#include "vue.h"



#endif // DEFINE_H_INCLUDED
