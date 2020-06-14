//
// Created by TheRolf on 13/06/2020.
//

#ifndef AG41_PROJET_INFORMATIONS_H
#define AG41_PROJET_INFORMATIONS_H

#define INDICE_CENTRE_SESSAD -1

#define INDICE_APPRENANT_FORMATION 0
#define INDICE_SPECIALITE_FORMATION 1
#define INDICE_COMPETENCE_INTERFACE_FORMATION 2
#define INDICE_JOUR_FORMATION 3
#define INDICE_DEBUT_FORMATION 4
#define INDICE_FIN_FORMATION 5

#define INDICE_DEBUT_INTERFACES NBR_CENTRES_FORMATION
#define INDICE_DEBUT_APPRENANTS (INDICE_DEBUT_INTERFACES + NBR_INTERFACES)

#define JOURS_DANS_LA_SEMAINE 7

#include "jeuEssai.h"

class Informations {
protected:

    static double distanceEntre(int source, int destination) {
        if(source == INDICE_CENTRE_SESSAD && destination == INDICE_CENTRE_SESSAD)
            return 0;

        if(source == INDICE_CENTRE_SESSAD)
            return distanceEntre(std::pair<double, double> (0, 0), destination);

        return distanceEntre(std::pair<double, double> (coord[source][0], coord[source][1]), destination);
    }

    static double distanceEntre(std::pair<double, double> posSource, int destination) {
        if(destination == INDICE_CENTRE_SESSAD)
            return sqrt(pow(posSource.first, 2) + pow(posSource.second, 2));

        double diffX = pow(coord[destination][0] - posSource.first, 2);
        double diffY = pow(coord[destination][1] - posSource.second, 2);
        return sqrt(diffX + diffY);
    }

    static int jourFormation(int indiceFormation) {
        return formation[indiceFormation][INDICE_JOUR_FORMATION];
    }

    static int maisonApprenti(int indiceFormation) {
        int indiceApprenant = formation[indiceFormation][INDICE_APPRENANT_FORMATION];

        return INDICE_DEBUT_APPRENANTS + indiceApprenant;
    }

    static int maisonFormation(int indiceFormation) {
        return formation[indiceFormation][]
    }

    static int maisonInterface(int interface) {
        return INDICE_DEBUT_INTERFACES + interface;
    }

    static long dureeFormation(int indiceFomation) {
        return formation[indiceFomation][INDICE_FIN_FORMATION] - formation[indiceFomation][INDICE_DEBUT_FORMATION];
    };
};


#endif //AG41_PROJET_INFORMATIONS_H
