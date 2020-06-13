
#ifndef AG41_PROJET_ALGORITHM_H
#define AG41_PROJET_ALGORITHM_H
#include "Matrice.h"
#include "jeuEssai.h"

#define INDEX_DEBUT_FORMATION 4
#define INDEX_FIN_FORMATION 5

class Algorithm 
{
private : 

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

    long dureeFormation(int ligneFormation) {
        return formation[ligneFormation][INDEX_FIN_FORMATION] - formation[ligneFormation][INDEX_FIN_FORMATION];
    }

};

#endif //AG41_PROJET_ALGORITHM