//
// Created by TheRolf on 13/06/2020.
//

#ifndef AG41_PROJET_JEUESSAI_H
#define AG41_PROJET_JEUESSAI_H

#define NBR_INTERFACES        24
#define NBR_APPRENANTS        20
#define NBR_CENTRES_FORMATION 3
#define NBR_SPECIALITES       3
#define NBR_NODES 	      NBR_CENTRES_FORMATION+NBR_INTERFACES+NBR_APPRENANTS

/* code des compétence en langage des signes et en codage LPC */
#define COMPETENCE_SIGNES     0
#define COMPETENCE_CODAGE     1

/* competences des interfaces en SIGNES et CODAGE*/
int competences_interfaces[NBR_INTERFACES][2]={
        {1,0}, /* compétence en langages des SIGNES mais pas en CODAGE LPC */
        {0,1}, /* pas de compétence en langages des SIGNES mais compétence en CODAGE LPC */
        {1,0},
        {0,1},
        {0,1},
        {0,1},
        {1,0},
        {0,1},
        {0,1},
        {0,1},
        {0,1},
        {1,0},
        {1,0},
        {1,0},
        {0,1},
        {1,0},
        {1,0},
        {1,0},
        {0,1},
        {1,0},
        {0,1},
        {1,0},
        {1,0},
        {0,1}
};

/* spécialités des interfaces */
#define SPECIALITE_SANS       -1 /* Enseigné dans le centre le plus proche */
#define SPECIALITE_MENUISERIE  0
#define SPECIALITE_ELECTRICITE 1
#define SPECIALITE_MECANIQUE   2

/* specialite des interfaces */
int specialite_interfaces[NBR_INTERFACES][NBR_SPECIALITES]={
        {0,0,1},
        {0,0,1},
        {1,0,1},
        {0,0,0},
        {0,0,1},
        {0,0,0},
        {0,0,0},
        {1,0,0},
        {0,0,0},
        {0,0,0},
        {0,1,0},
        {0,0,0},
        {0,0,1},
        {0,1,0},
        {0,0,0},
        {0,0,0},
        {0,0,0},
        {0,1,0},
        {0,0,0},
        {0,0,0},
        {0,1,0},
        {0,0,0},
        {1,0,0},
        {1,0,0}
};

/* coordonnées des centres de formation, des interfaces et des apprenants */
float coord[NBR_NODES][2]={

        /* Centres de formation */
        {82,27}, /* centre formation SPECIALITE_MENUISERIE */
        {31,194}, /* centre formation SPECIALITE_ELECTRICITE */
        {100,60}, /* centre formation SPECIALITE_MECANIQUE */

        /* Les interfaces se rendent directement de leur domicile chez l'apprenant */
        {189,106}, /* interface 0 */
        {148,87}, /* interface 1 */
        {161,130}, /* interface 2 */
        {118,166}, /* interface 3 */
        {44,146}, /* interface 4 */
        {62,144}, /* interface 5 */
        {142,64}, /* interface 6 */
        {74,71}, /* interface 7 */
        {85,183}, /* interface 8 */
        {134,66}, /* interface 9 */
        {3,109}, /* interface 10 */
        {130,80}, /* interface 11 */
        {161,164}, /* interface 12 */
        {149,79}, /* interface 13 */
        {63,64}, /* interface 14 */
        {183,131}, /* interface 15 */
        {73,25}, /* interface 16 */
        {53,39}, /* interface 17 */
        {28,141}, /* interface 18 */
        {151,153}, /* interface 19 */
        {55,170}, /* interface 20 */
        {37,49}, /* interface 21 */
        {46,165}, /* interface 22 */
        {85,187}, /* interface 23 */

        /* Apprenants */
        {122,164}, /* apprenant 0 */
        {146,5}, /* apprenant 1 */
        {7,114}, /* apprenant 2 */
        {171,170}, /* apprenant 3 */
        {113,39}, /* apprenant 4 */
        {0,121}, /* apprenant 5 */
        {44,90}, /* apprenant 6 */
        {132,172}, /* apprenant 7 */
        {100,20}, /* apprenant 8 */
        {64,118}, /* apprenant 9 */
        {28,84}, /* apprenant 10 */
        {185,76}, /* apprenant 11 */
        {82,180}, /* apprenant 12 */
        {148,25}, /* apprenant 13 */
        {109,135}, /* apprenant 14 */
        {173,190}, /* apprenant 15 */
        {142,120}, /* apprenant 16 */
        {82,173}, /* apprenant 17 */
        {194,140}, /* apprenant 18 */
        {119,94}/* apprenant 19 */
};

#define NBR_FORMATION          80

#define LUNDI                  1
#define MARDI                  2
#define MERCREDI               3
#define JEUDI                  4
#define VENDREDI               5
#define SAMEDI                 6

/* formation : apprenant, specialite ou centre de formation, competence, horaire debut formation, horaire fin formation */
int formation[NBR_FORMATION][6]={
        {0,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,VENDREDI,15,19},
        {0,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,SAMEDI,13,19},
        {0,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,JEUDI,13,16},
        {0,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,MERCREDI,8,12},
        {1,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,VENDREDI,10,12},
        {1,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,LUNDI,10,12},
        {1,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,VENDREDI,9,12},
        {1,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,LUNDI,9,11},
        {2,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,SAMEDI,13,15},
        {2,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,MERCREDI,14,16},
        {2,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,SAMEDI,9,12},
        {2,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,SAMEDI,13,19},
        {3,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,VENDREDI,15,17},
        {3,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,LUNDI,13,17},
        {3,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,MARDI,9,11},
        {3,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,LUNDI,16,19},
        {4,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,JEUDI,10,12},
        {4,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,MERCREDI,10,12},
        {4,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,MARDI,9,12},
        {4,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,MERCREDI,13,17},
        {5,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,MERCREDI,13,19},
        {5,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,SAMEDI,8,12},
        {5,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,MERCREDI,10,12},
        {5,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,SAMEDI,16,19},
        {6,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,MERCREDI,16,18},
        {6,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,VENDREDI,10,12},
        {6,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,MERCREDI,10,12},
        {6,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,JEUDI,16,18},
        {7,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,JEUDI,8,12},
        {7,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,JEUDI,8,12},
        {7,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,MARDI,9,11},
        {7,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,JEUDI,10,12},
        {8,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,MARDI,14,18},
        {8,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,LUNDI,8,12},
        {8,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,LUNDI,16,18},
        {8,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,VENDREDI,13,15},
        {9,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,JEUDI,13,16},
        {9,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,MARDI,8,11},
        {9,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,VENDREDI,13,17},
        {9,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,VENDREDI,14,17},
        {10,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,JEUDI,10,12},
        {10,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,JEUDI,9,12},
        {10,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,SAMEDI,14,16},
        {10,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,MERCREDI,14,18},
        {11,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,LUNDI,8,12},
        {11,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,VENDREDI,8,12},
        {11,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,JEUDI,10,12},
        {11,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,MARDI,15,19},
        {12,SPECIALITE_MECANIQUE,COMPETENCE_SIGNES,LUNDI,10,12},
        {12,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,SAMEDI,15,17},
        {12,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,LUNDI,14,19},
        {12,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,SAMEDI,10,12},
        {13,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,VENDREDI,9,12},
        {13,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,LUNDI,10,12},
        {13,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,VENDREDI,13,16},
        {13,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,LUNDI,14,17},
        {14,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,LUNDI,16,18},
        {14,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,MERCREDI,14,18},
        {14,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,MERCREDI,10,12},
        {14,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,VENDREDI,10,12},
        {15,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,SAMEDI,10,12},
        {15,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,SAMEDI,8,12},
        {15,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,LUNDI,16,18},
        {15,SPECIALITE_ELECTRICITE,COMPETENCE_CODAGE,LUNDI,14,19},
        {16,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,VENDREDI,10,12},
        {16,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,MARDI,10,12},
        {16,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,JEUDI,8,10},
        {16,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,LUNDI,10,12},
        {17,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,MARDI,9,12},
        {17,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,LUNDI,16,19},
        {17,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,VENDREDI,16,18},
        {17,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,LUNDI,15,17},
        {18,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,JEUDI,9,12},
        {18,SPECIALITE_ELECTRICITE,COMPETENCE_SIGNES,MARDI,14,18},
        {18,SPECIALITE_MENUISERIE,COMPETENCE_SIGNES,LUNDI,16,19},
        {18,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,MERCREDI,16,19},
        {19,SPECIALITE_MECANIQUE,COMPETENCE_CODAGE,MERCREDI,16,18},
        {19,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,VENDREDI,14,17},
        {19,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,SAMEDI,10,12},
        {19,SPECIALITE_MENUISERIE,COMPETENCE_CODAGE,JEUDI,8,11}};

#endif //AG41_PROJET_JEUESSAI_H
