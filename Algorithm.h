
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

Matrice attribute(Matrice M)
{
    Matrice M2(M);
    for(int i=0;i<NBR_APPRENANTS;++i)
    {
        for(int j=0;j<NBR_FORMATION;++j)
        {
            try
            {
                if(formation[j][1] == -1)
                    throw string("Sans formation.");
                else
                {
                    if(formation[j][2] != specialite_interfaces[i])
                    {
                        M2[i][j] = -1;
                    }
                }
                 
            }
           catch (string const& chaine)
            {
                //do nothing
            }
            if (competences_interfaces[i] != formation[j][2])
            {
                M2[i][j] = -1;
            }
        }
    }
    return M2;
};

void solve_algorithm(Matrice M0, int iteration, double eval_node_parent)
{
    if (iteration == )
    {
        build_solution ();
        return;
    }

    /* Do the modification on a copy of the distance matrix */
    

    int i, j ;

    double eval_node_child = eval_node_parent;

    /**
     * substract the min of the rows and the min of the columns
     * and update the evaluation of the current node
     */

    double min_row[NBR_INTERFACES];
    for(i=0;i<NBR_INTERFACES;++i)
    {
        min_row[i] = -1;
        for(j=0;j<NBR_FORMATION;++j)
        {
            if(d[i][j]>=0 && (min_row[i]<0||min_row[i]>d[i][j]))
            {
                min_row[i] = d[i][j];
            }
        }
        for(j=0;j<NBR_FORMATION;++j)
        {
            if(d[i][j]>=0)
            {
                d[i][j] -= min_row[i];
            }
        }
    }

    double min_column[NBR_FORMATION];

    for(i=0;i<NBR_INTERFACES;++i)
    {
        min_column[i] = -1.0;
        for(j=0;j<NBR_FORMATION;++j)
        {
            if(d[j][i]>=0 && (min_column[i]<0||min_column[i]>d[j][i]))
            {
                min_column[i] = d[j][i];
            }
        }
        for(j=0;j<NBR_FORMATION;++j)
        {
            if(d[j][i]>=0)
            {
                d[j][i] -= min_column[i];
            }
        }

    }

    for(i=0;i<NBR_INTERFACES;++i)
    {
        eval_node_child += min_row[i]+min_column[i];
    }

    /* Cut : stop the exploration of this node */
    if (best_eval>=0 && eval_node_child >= best_eval)
        return;


    /**
     *  Compute the penalities to identify the zero with max penalty
     *  If no zero in the matrix, then return, solution infeasible
     */

    /* row and column of the zero with the max penalty */
    int izero=-1, jzero=-1 ;
    double max_zero = -3;

    for(i=0;i<NBR_INTERFACES;++i)
    {
        for(j=0;j<NBR_FORMATION;++j)
        {
            if(d[i][j] == 0.0)
            {
                double min_row_zero = -1;
                double min_column_zero = -1;
                for(int y=0;y<NBR_TOWNS;++y)
                {
                    if((d[i][y]>=0 && (min_row_zero<0||min_row_zero>d[i][y])) && (y!=j))
                    {
                        min_row_zero = d[i][y];
                    }
                    if((d[y][j]>=0 && (min_column_zero<0||min_column_zero>d[y][j])) && (y!=i))
                    {
                        min_column_zero = d[y][j];
                    }
                }
                double this_zero = min_row_zero + min_column_zero;
                if(this_zero>max_zero)
                {
                    max_zero = this_zero;
                    izero = i;
                    jzero = j;
                }
            }
        }
    }
    if(max_zero == -3)
    {
        /*printf("Solution Infesable\n");*/
        return;
    }


    /**
     *  Store the row and column of the zero with max penalty in
     *  starting_town and ending_town
     */

    starting_town[iteration]=izero;
    ending_town[iteration]=jzero;

    /* Do the modification on a copy of the distance matrix */
    double d2[NBR_TOWNS][NBR_TOWNS] ;
    memcpy (d2, d, NBR_TOWNS*NBR_TOWNS*sizeof(double)) ;

    /**
     *  Modify the matrix d2 according to the choice of the zero with the max penalty
     */

    for(int y=0;y<NBR_TOWNS;++y)
    {
        d2[izero][y] = -1;
        d2[y][jzero] = -1;
    }
    d2[jzero][izero] = -1;

    /* Explore left child node according to given choice */
    solve_algorithm(M2, iteration + 1, eval_node_child);

    /* Do the modification on a copy of the distance matrix */
    memcpy (d2, d, NBR_TOWNS*NBR_TOWNS*sizeof(double)) ;

    /**
     *  Modify the dist matrix to explore the other possibility : the non-choice
     *  of the zero with the max penalty
     */

    d2[izero][jzero] = -1;

    /* Explore right child node according to non-choice */
    solve_algorithm(M2, iteration, eval_node_child);
};

void update_hach();
void update_matrice();
void create_matrice();
void eval();

long dureeFormation(int indiceFomation) {
    return formation[indiceFomation][INDICE_FIN_FORMATION] - formation[indiceFomation][INDICE_DEBUT_FORMATION];
};

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
};

long heuresDeLaSemaine(int interface) {
    long somme;

    for(int i = 0; i < JOURS_DANS_LA_SEMAINE; ++i) {
        somme += heuresDuJour(interface, i+1);
    }

    return somme;
    };

#endif //AG41_PROJET_ALGORITHM