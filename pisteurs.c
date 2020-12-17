#include "struct_const.h"
#include "pisteurs.h"


//SAISIE : INIT _________________________________________________


//Saisie NB Pisteurs :--------------------------------

void Init_Saisie_NBPisteurs(pisteur tab[], int *pNbPisteursChoisi, int min, int max, char carAttente, char carVerif, char carPisteur, int maxLettres,int nbPV,int traceFraiche,int traceEnMoins){
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
        fflush(stdin);
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
         tab[i].tracesFraiches=traceFraiche;
         tab[i].tracesEnMoins=traceEnMoins;

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

void Saisie_posPisteurs(int grillePersonnages[][LARGEUR_Map],int grilleTraces_Pisteur[][LARGEUR_Map], pisteur tab[],int nbPisteursChoisi,char carDelimt, monster monstre){
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


    while (SDL_PollEvent(&events)){
        for(i=0;i<nbPisteursChoisi;i++){

                //on demande les coords :
                do{

                    //X-----------------
                    nbTexte=nbPos_TPisteurX;
                    AffichTexte(nbTexte,tab,i,0,0);
                    do{
                        scanf("%d",&x);
                          fflush(stdin);

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
                          fflush(stdin);
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

                //on mets la trace du pisteur � son �tat initial :
                AjoutTrace_Pisteur(tab,i,grilleTraces_Pisteur);

                //on affiche la map avec � jour la position du pisteur :
                SDL_NettoieEcran();
                SDL_AffichMap(grillePersonnages,monstre);
                Maj_AffichMap(grillePersonnages,carDelimt,etatJeu,tab,monstre);


           }

            if(i==nbPisteursChoisi){
                SDL_Quit();
            }
            switch (events.type)
                {
                    case SDL_QUIT:
                    isOpen = SDL_FALSE ;
                    break;
                }
    }

}





//JEU _______________________________________________________________________

    //traces pisteurs ajouter et enlever :

void AjoutTrace_Pisteur(pisteur tabPisteur[], int indexTab, int grilleTraces_Pisteur[][LARGEUR_Map]){
//BUT: on ajoute le nb 16 � l'ancienne position du pisteur
//ENTREE: les var du monstre, et le tableau qui fait l'historique des traces
//SORTIE:tab traces avec nb ajout� dedans

    grilleTraces_Pisteur[tabPisteur[indexTab].coords.x-1][tabPisteur[indexTab].coords.y-1]=tabPisteur[indexTab].tracesFraiches;

}

void EffacementTraces_Pisteur(int grilleTraces_Pisteur[][LARGEUR_Map], int retire){
//BUT:enlever � chaque tour un pt de trace jusqu'� diparaitre quand la valeur 0 atteinte

    int i;
    int j;

    for(i=0;i<HAUTEUR_Map;i++){
        for(j=0;j<LARGEUR_Map;j++){

                if(grilleTraces_Pisteur[i][j]>0){

                    grilleTraces_Pisteur[i][j]=grilleTraces_Pisteur[i][j]-retire; //on retire 1
                }

        }
    }
}



    //compte rendu des pisteurs

int Tirer_SurMonstre(int vieMonstre,int chanceTir, int nbDegats_Pisteur, monster *monstre){
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
            vieMonstre=vieMonstre-nbDegats_Pisteur;
            AffichTexte(nbTexte,0,0,0,0,vieMonstre);

            //on indique su'il est bless�
            monstre->estBlesse=vrai;

        }
        else{
            //il loupe le tir
            nbTexte=nbTirLoupe_TMonstre;
            AffichTexte(nbTexte,0,0,0,0,0);
        }
        getchar();
    }

    return vieMonstre;

}

void CheckCaseVoisine_Pisteur(int grillePerso[][LARGEUR_Map], int grilleTraces[][LARGEUR_Map], pisteur tabPisteur[], int nbPisteurs, monster *monstre,int chanceTir,state etatJeu, int nbDegats_Pisteur,char delimtMap){
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

        if(tabPisteur[i].estVivant==vrai){

            x=tabPisteur[i].coords.x;
            y=tabPisteur[i].coords.y;
            //on oublie pas que les tableaux commencent � 0 et non 1, du coup on retire 1
            x=x-1;
            y=y-1;
            nbCase=nbMonstre;
             Maj_AffichMap(grillePerso,delimtMap,etatJeu,tabPisteur,monstre);
            //on affiche le pisteur avec un !
            majElement_SurMap(x,y,tabPisteur[i].car_Verifie,16,tabPisteur[i].car_Verifie,tabPisteur[i].car_EnAttente);
            SDL_NettoieEcran();
            SDL_AffichMap(grillePerso,monstre);
            SDL_EnleveElement_Map(x,y,TAILLE_IMAGE,TAILLE_IMAGE,0,0,0);
            SDL_MajElement_Map(x,y,tabPisteur[i].car_Verifie,tabPisteur[i].car_Verifie,tabPisteur[i].car_EnAttente);



            if ((x>0) && (x<HAUTEUR_Map-1)){

                if ((y>0) && (y<LARGEUR_Map-1)){
                    //le monstre est � c�t� :
                    if((grillePerso[x-1][y]==nbMonstre)||(grillePerso[x+1][y]==nbMonstre) || (grillePerso[x][y-1]==nbMonstre) || (grillePerso[x][y+1]==nbMonstre)||(grillePerso[x-1][y-1]==nbMonstre)||(grillePerso[x-1][y+1]==nbMonstre)||(grillePerso[x+1][y+1]==nbMonstre)||(grillePerso[x+1][y-1]==nbMonstre)){

                        monstreEstLa=vrai;
                        nbTexte=nbMonstre_TCaseVoisine;
                        AffichTexte(nbTexte,tabPisteur,i);
                        vieMonstre=Tirer_SurMonstre(vieMonstre,chanceTir,nbDegats_Pisteur,monstre);
                        monstre->vieRestante=vieMonstre;
                    }
                }
                else if(y==0){
                    if((grillePerso[x-1][y]==nbMonstre)||(grillePerso[x+1][y]==nbMonstre)  || (grillePerso[x][y+1]==nbMonstre)||(grillePerso[x-1][y+1]==nbMonstre)||(grillePerso[x+1][y+1]==nbMonstre)){

                        monstreEstLa=vrai;
                        nbTexte=nbMonstre_TCaseVoisine;
                        AffichTexte(nbTexte,tabPisteur,i);
                        vieMonstre=Tirer_SurMonstre(vieMonstre,chanceTir,nbDegats_Pisteur,monstre);
                        monstre->vieRestante=vieMonstre;
                    }
                }
                else if (y==LARGEUR_Map-1){
                        if((grillePerso[x-1][y]==nbMonstre)||(grillePerso[x+1][y]==nbMonstre) || (grillePerso[x][y-1]==nbMonstre)||(grillePerso[x-1][y-1]==nbMonstre)||(grillePerso[x+1][y-1]==nbMonstre)){

                        monstreEstLa=vrai;
                        nbTexte=nbMonstre_TCaseVoisine;
                        AffichTexte(nbTexte,tabPisteur,i);
                        vieMonstre=Tirer_SurMonstre(vieMonstre,chanceTir,nbDegats_Pisteur,monstre);
                        monstre->vieRestante=vieMonstre;
                    }

                }
            }


            else if (x==0){

                if ((y>0) && (y<LARGEUR_Map-1)){
                    //le monstre est � c�t� :
                    if((grillePerso[x+1][y]==nbMonstre) || (grillePerso[x][y-1]==nbMonstre) || (grillePerso[x][y+1]==nbMonstre)||(grillePerso[x+1][y+1]==nbMonstre)||(grillePerso[x+1][y-1]==nbMonstre)){

                        monstreEstLa=vrai;
                        nbTexte=nbMonstre_TCaseVoisine;
                        AffichTexte(nbTexte,tabPisteur,i);
                        vieMonstre=Tirer_SurMonstre(vieMonstre,chanceTir,nbDegats_Pisteur,monstre);
                        monstre->vieRestante=vieMonstre;
                    }
                }
                else if(y==0){
                    if((grillePerso[x+1][y]==nbMonstre) || (grillePerso[x][y+1]==nbMonstre)||(grillePerso[x+1][y+1]==nbMonstre)){

                        monstreEstLa=vrai;
                        nbTexte=nbMonstre_TCaseVoisine;
                        AffichTexte(nbTexte,tabPisteur,i);
                        vieMonstre=Tirer_SurMonstre(vieMonstre,chanceTir,nbDegats_Pisteur,monstre);
                        monstre->vieRestante=vieMonstre;
                    }

                }
                else if (y==LARGEUR_Map-1){
                        if((grillePerso[x+1][y]==nbMonstre) || (grillePerso[x][y-1]==nbMonstre)||(grillePerso[x+1][y-1]==nbMonstre)){

                        monstreEstLa=vrai;
                        nbTexte=nbMonstre_TCaseVoisine;
                        AffichTexte(nbTexte,tabPisteur,i);
                        vieMonstre=Tirer_SurMonstre(vieMonstre,chanceTir,nbDegats_Pisteur,monstre);
                        monstre->vieRestante=vieMonstre;
                    }
                }
            }

            else if (x==HAUTEUR_Map-1){
                if ((y>0) && (y<LARGEUR_Map-1)){
                    //le monstre est � c�t� :
                    if((grillePerso[x-1][y]==nbMonstre) || (grillePerso[x][y-1]==nbMonstre) || (grillePerso[x][y+1]==nbMonstre)||(grillePerso[x-1][y-1]==nbMonstre)||(grillePerso[x-1][y+1]==nbMonstre)){

                        monstreEstLa=vrai;
                        nbTexte=nbMonstre_TCaseVoisine;
                        AffichTexte(nbTexte,tabPisteur,i);
                        vieMonstre=Tirer_SurMonstre(vieMonstre,chanceTir,nbDegats_Pisteur,monstre);
                        monstre->vieRestante=vieMonstre;
                    }
                }
                else if(y==0){
                    if((grillePerso[x-1][y]==nbMonstre) || (grillePerso[x][y+1]==nbMonstre)||(grillePerso[x-1][y+1]==nbMonstre)){

                        monstreEstLa=vrai;
                        nbTexte=nbMonstre_TCaseVoisine;
                        AffichTexte(nbTexte,tabPisteur,i);
                        vieMonstre=Tirer_SurMonstre(vieMonstre,chanceTir,nbDegats_Pisteur,monstre);
                        monstre->vieRestante=vieMonstre;
                    }

                }
                else if (y==LARGEUR_Map-1){
                        if((grillePerso[x-1][y]==nbMonstre) || (grillePerso[x][y-1]==nbMonstre)||(grillePerso[x-1][y-1]==nbMonstre)){

                        monstreEstLa=vrai;
                        nbTexte=nbMonstre_TCaseVoisine;
                        AffichTexte(nbTexte,tabPisteur,i);
                        vieMonstre=Tirer_SurMonstre(vieMonstre,chanceTir,nbDegats_Pisteur,monstre);
                        monstre->vieRestante=vieMonstre;
                        }
                }

            }





            //traces visibles :
             if(monstreEstLa==faux){

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

        }
    }
      SDL_NettoieEcran();
    SDL_AffichMap(grillePerso,monstre);

}

/*COde r�alis� par Elias Eckl�*/


    //D�placement d3e chaque pisteur
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
              fflush(stdin);
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
            fflush(stdin);
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


void Deplcmt_Pisteur(int grillePersos[][LARGEUR_Map], int grillesTraces_Pisteur[][LARGEUR_Map], state etatJeu, pisteur tabPisteur[],int nbPisteurs, int maxDistance, char carDelimt,monster monstre,int nbDegatsMonstre){
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

        if(tabPisteur[i].estVivant==vrai){

            //-1 pour coller � la plage du tableau : 0 �... et non 1 �...
            x=tabPisteur[i].coords.x-1;
            y=tabPisteur[i].coords.y-1;
            majElement_SurMap(x,y,tabPisteur[i].car_EnAttente,18,tabPisteur[i].car_Verifie,tabPisteur[i].car_EnAttente);
            SDL_EnleveElement_Map(x,y,TAILLE_IMAGE,TAILLE_IMAGE,0,0,0);
            SDL_MajElement_Map(x,y,tabPisteur[i].car_EnAttente,tabPisteur[i].car_Verifie,tabPisteur[i].car_EnAttente);

        //demander direction et distance
            //direction :
            nb_DirectionChoisie=ChoixDirection(grillePersos,tabPisteur,i,x,y);
            //distance :
            nb_DistanceChoisie=ChoixDistance(grillePersos,tabPisteur,i,x,y,maxDistance,nb_DirectionChoisie);
            //reinit
            majElement_SurMap(x,y,tabPisteur[i].car_EnAttente,18,tabPisteur[i].car_Verifie,tabPisteur[i].car_EnAttente);
            SDL_EnleveElement_Map(x,y,TAILLE_IMAGE,TAILLE_IMAGE,0,0,0);
            SDL_MajElement_Map(x,y,tabPisteur[i].car_EnAttente,tabPisteur[i].car_Verifie,tabPisteur[i].car_EnAttente);


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
            SDL_NettoieEcran();
            SDL_AffichMap(grillePersos,monstre);
            //on ajoute nouvelle trace du pisteur
            AjoutTrace_Pisteur(tabPisteur,i,grillesTraces_Pisteur);


        }
    }
    //on v�rifie si le d�placement fait n'est pas sur une case ou se trouve le monstre. Si oui pisteur est mang� par ce dernier
    PisteurEst_CaseMonstre(grillePersos,monstre,nbDegatsMonstre,tabPisteur,nbPisteurs);
    getchar();
}


void PisteursRestant_EnVie(pisteur tabPisteur[],int nbPisteursChoisi, booleanPerso *pisteursSontEnVie){
//BUT: on v�rifie s'il reste des pisteurs en vie. Si non alors o retourne false

    int i;
    int cptMort=0;

    for(i=0;i<nbPisteursChoisi;i++){
        if(tabPisteur[i].estVivant==faux){
            cptMort++;
        }
    }
    if(cptMort==nbPisteursChoisi){
        *pisteursSontEnVie=faux;
    }


}

