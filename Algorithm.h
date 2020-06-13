
#ifndef AG41_PROJET_ALGORITHM_H
#define AG41_PROJET_ALGORITHM_H

#include <map>
#include "Matrice.h"
#include "jeuEssai.h"

#define INDICE_JOUR_FORMATION 3
#define INDICE_DEBUT_FORMATION 4
#define INDICE_FIN_FORMATION 5

#define JOURS_DANS_LA_SEMAINE 7

class Algorithm 
{
private : 
    std::map<int, int> _choix;
public : 
    void solve_algorithm(Matrice M, int iteration, double eval_parent)
    {
        Matrice M2(M);
        for(int i=0;i<NBR_APPRENANTS;++i)
        {
            for(j=0;j<NBR_FORMATION;++j)
            {
                if()
            }
        }
    };
    Matrice attribute(Matrice M)
    {
        voir
    };
    void update_hach();
    void update_matrice();
    void create_matrice();
    void eval();

    long dureeFormation(int indiceFomation) {
        return formation[indiceFomation][INDICE_FIN_FORMATION] - formation[indiceFomation][INDICE_DEBUT_FORMATION];
    }

    long heuresDuJour(int interface, int jour) {
        long somme = 0;

        // pour chaque choix dans _choix fait
        int indiceFormation;
        int interfaceAffectee;
        int jourDeLaTache;
        for(std::map<int, int>::iterator c = _choix.begin(); c != _choix.end(); c++) {
            indiceFormation = c->first;
            interfaceAffectee = c->second;

            jourDeLaTache = formation[indiceFormation][INDICE_JOUR_FORMATION];

            // si la tache est affectee l'interface choisie correspond (valeur) et que le jour correspond
            if(interfaceAffectee == interface && jourDeLaTache == jour) {
                // alors on ajoute la duree de l formation
                somme += dureeFormation(indiceFormation);
            }
        }

        return somme;
    }

    long heuresDeLaSemaine(int interface) {
        long somme;

        for(int i = 0; i < JOURS_DANS_LA_SEMAINE; ++i) {
            somme += heuresDuJour(interface, i+1);
        }

        return somme;
    }
};

#endif //AG41_PROJET_ALGORITHM