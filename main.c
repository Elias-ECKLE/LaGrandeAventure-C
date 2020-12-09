
/*FEATURES :

    //INIT :
- afficher map aves ses délimitations : 29x14cases=406 cases entourées de "*"
- demander au joueur combien de pisteurs il veut : préférable d'en prendre 3 ou 4->on peut choisir entre 1 et 10
- demander au joueur une valeur en x et en y pour chaque pisteur. Puis à chaque fois faire apparaitre un "P" sur la case choisie
- positioner au hasard le monstre sur une case(apposer nb 16), et le cacher. Si case tirée est voisine à un pisteur, alors refaire le tirage



    //PARTIE :


- -1 sur les nb des traces
- chaque pisteur va dire ce qu'il voit autour de lui (sur les 8 cases) à tour de rôle.(Il est affiché sur la map d'un "!")
    3 possibilités :
        a. il n'y a rien autour de lui et affiche "RIEN en 1,,2,3,4,5,6,7,8"
        b. certaines cases ont des traces du monstre : il affiche "traces en 'nbCaseVoisine' de valeur 'nbTraces'" pour chaque case concernée l'une aprè l'autre
        c. Le monstre est dans l'une des cases voisine : le pisteur annonce juste "je le vois". on peut tirer ou soit ne rien faire
    -->40% de chances de le toucher à savoir qu'il a 4 points de vie et on l'indique à l'écran

- Sur la map affiché avec "?". On déplace ensuite les pisteurs à tour de rôle : d'abord distance de déplacement demandées : de 1 à 4 puis direction de déplacement : quatre directions possibles : 1 pour haut, 2pour droite, 3pour bas et 4 pour gauche



- le monstre se déplace d'une case à chaque tour et marque sur la case auquel il se trouve le nb 16. Il se déplace en l'une des 4 cases différentes, H B G D  aléatoirement(ou flaire les traces des pisteurs)
    et s'il tombe sur même case que pisteur alors il le mange et l'indique à l'écran
- A noter qu'il check les 4 cases autour de lui pour savoir s'il y a un pisteur et si oui, il va sur cette case en question pour le manger
    Si touché par coup de tir alors pendant quatre tours un point apparaît au dernier endroit séjourné avt déplacement et perd 1 pv


    //CONDITION de victoire : les pv du monstres ont atteints 0
    //CONDITION de défaite  : tous les pisteurs sont morts
    //du coup on boucle les 3 phases de la partie autant de fois jusqu'à qu'il arrive une de ces condtions



    //FIN DE PARTIE :
- on affiche si le monstre a mangé tous les pisteurs
- ou si les pisteurs ont tués le monstre

*/


#include "define.h"



int main()
{



  //INIT variables :____________________________________________________________
  state etatJeu=debut;


























    return 0;



























}
