
#ifndef AG41_PROJET_ALGORITHM_H
#define AG41_PROJET_ALGORITHM_H

#include <map>
#include <cmath>
#include <vector>
#include "Matrice.h"
#include "jeuEssai.h"
#include "Informations.h"

class Algorithm : public Informations
{
private :
    double meilleureVarianceKm = 0;
    double meilleureVarianceHeures = 0;
    std::vector<std::pair<int, int>> meilleureSolution;

    long best_eval = -1;
    std::vector<std::pair<int, int>> _choix; ///< indice de la formation, indice de l'interface affectée

    void mettreAJourSolution(int iteration, int indiceInterface, int interface) {
        _choix[iteration].first = indiceInterface;
        _choix[iteration].second = interface;
    }

    long heuresDuJour(int interface, int jour) {
        long somme = 0;

        // pour chaque choix dans _choix fait
        int indiceFormation;
        int interfaceAffectee;
        int jourDeLaTache;
        for(std::vector<std::pair<int, int>>::iterator c = _choix.begin(); c != _choix.end(); c++) {
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
        long somme = 0;

        for(int i = 0; i < JOURS_DANS_LA_SEMAINE; ++i) {
            somme += heuresDuJour(interface, i+1);
        }

        return somme;
    };

    std::pair<double, long> totalInterface(int interface) {
        std::pair<double, long> resultat;
        resultat.first = 0;
        resultat.second = 0;

        int indiceMaisonInterface = maisonInterface(interface);
        int distanceMaisonSessad = distanceEntre(indiceMaisonInterface, INDICE_CENTRE_SESSAD);

        int jour = SAMEDI;
        int maisonDepart = indiceMaisonInterface;
        bool nouvelleJournee = false;
        int indiceFormation;
        int indiceInterface;
        for(std::vector<std::pair<int, int>>::iterator c = _choix.begin(); c != _choix.end(); c++) {
            indiceInterface = c->second;

            if(indiceInterface == interface) { // si c'est la bonne interface
                indiceFormation = c->first;

                if(jour != jourFormation(indiceFormation)) { // si c'est un jour différent, on part du sessad
                    jour = jourFormation(indiceFormation);

                    // on ajoute le retour chez soi
                    if(nouvelleJournee) {
                        resultat.first += distanceMaisonSessad;
                    }

                    // on part de chez soi
                    resultat.first += distanceMaisonSessad;

                    maisonDepart = INDICE_CENTRE_SESSAD;
                }

                // on se rend chez l'apprenant
                resultat.first += distanceEntre(maisonDepart, maisonApprenti(indiceFormation));

                // on se rend a la formation
                resultat.first += distanceEntre(maisonApprenti(indiceFormation), maisonFormation(indiceFormation));

                // on ajoute le temps de travail
                resultat.second += dureeFormation(indiceFormation);

                // on retour chez l'apprenant
                resultat.first += distanceEntre(maisonFormation(indiceFormation), maisonApprenti(indiceFormation));
            }
            nouvelleJournee = true;
        }

        return resultat;
    }

    void construireSolution(Matrice *m) {
        // initialisation
        std::map<int, double> totalKm;
        std::map<int, long> totalHeures;

        // on somme et on min
        double sommeKm = 0;
        long sommeHeures = 0;
        for(unsigned int i = 0; i < NBR_INTERFACES; ++i) {
            std::pair<double, long> res = totalInterface(i);

            totalKm[i] = res.first;
            totalHeures[i] = res.second;

            sommeKm += totalKm[i];
            sommeHeures += totalHeures[i];
        }

        // on prend la moyenne
        double moyenneKm = sommeKm/NBR_INTERFACES;
        double moyenneHeures = sommeHeures/NBR_INTERFACES;

        sommeKm = 0;
        sommeHeures = 0;
        for(unsigned int i = 0; i < NBR_INTERFACES; ++i) {
            sommeKm += pow(totalKm[i] - moyenneKm, 2);
            sommeHeures += pow(totalHeures[i] - moyenneHeures, 2);
        }

        double varianceKm = sommeKm/NBR_INTERFACES;
        double varianceHeures = sommeHeures/NBR_INTERFACES;

        /*
         * La meilleure solution se base sur le gain en poucentage de variablité de la variance sommé entre heures et distances)
         */

        double diffVarianceKm = meilleureVarianceKm - varianceKm;
        double diffVarianceHeures = meilleureVarianceHeures - varianceHeures;

        // pas encore de meilleure solution
        if(meilleureVarianceKm == 0 || meilleureVarianceHeures == 0) {
            meilleureVarianceKm = varianceKm;
            meilleureVarianceHeures = varianceHeures;
            meilleureSolution = _choix;

            return;
        }

        // sinon si fait le rapport de diff
        double rapportKm = diffVarianceKm/meilleureVarianceKm;
        double rapportHeures = diffVarianceHeures/meilleureVarianceHeures;

        double gainVariance = rapportKm + rapportHeures;


        if(gainVariance < 0) {
            meilleureVarianceKm = varianceKm;
            meilleureVarianceHeures = varianceHeures;
            meilleureSolution = _choix;
        }

        return;
    }
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
                        throw "Sans formation.";
                    else
                    {
                        if(formation[j][2] != specialite_interfaces[i]) // ça correspond à quoi ça, ça compile pas d'ailleurs
                        {
                            M2[i][j] = -1;
                        }
                    }

                }
                catch (String const& chaine)
                {
                    //do nothing
                }
                if (competences_interfaces[i] != formation[j][2]) // je ne sais pas
                {
                    M2[i][j] = -1;
                }
            }
        }
        return M2;
    };

    void solve_algorithm(Matrice* M0, int iteration, long eval_node_parent)
    {
        if (iteration == NBR_FORMATION)
        {
            construireSolution(M0);
            return;
        }

        int i, j ;
    /* Do the modification on a copy of the distance matrix */

    Matrice M(M0);

    int i, j ;

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
            if(M[i][j]>=0 && (min_row[i]<0||min_row[i]>M[i][j]))
            {
                min_row[i] = M[i][j];
            }
        }
        for(j=0;j<NBR_FORMATION;++j)
        {
            if(M[i][j]>=0)
            {
                M[i][j] -= min_row[i];
            }
        }
    }

        long min_column[NBR_FORMATION];

    for(i=0;i<NBR_INTERFACES;++i)
    {
        min_column[i] = -1.0;
        for(j=0;j<NBR_FORMATION;++j)
        {
            if(M[j][i]>=0 && (min_column[i]<0||min_column[i]>M[j][i]))
            {
                min_column[i] = M[j][i];
            }
        }
        for(j=0;j<NBR_FORMATION;++j)
        {
            if(M[j][i]>=0)
            {
                M[j][i] -= min_column[i];
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
    long max_zero = -3;

    for(i=0;i<NBR_INTERFACES;++i)
    {
        for(j=0;j<NBR_FORMATION;++j)
        {
            if(M[i][j] == 0.0)
            {
                double min_row_zero = -1;
                double min_column_zero = -1;
                for(int y1=0;y1<NBR_FORMATION;++y1)
                {
                    if((M[i][y1]>=0 && (min_row_zero<0||min_row_zero>d[i][y1])) && (y1!=j))
                    {
                        min_row_zero = M[i][y1];
                    }
                }
                for(int y2=0; y2<NBR_INTERFACES; y2++)
                {
                    if((M[y][j]>=0 && (min_column_zero<0||min_column_zero>M[y][j])) && (y!=i))
                    {
                        min_column_zero = M[y][j];
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

    mettreAJourSolution(iteration, izero, jzero);

    /* Do the modification on a copy of the distance matrix */
    Matrice M2(M);

    /**
     *  Modify the matrix d2 according to the choice of the zero with the max penalty
     */

    for(int y=0;y<NBR_FORMATION;++y)
    {
        if(M2[izero][y] != -1)
        {
            //ajout de la distance effectuée
        }
    }
    for(y=0;y<NBR_INTERFACES;++y)
    {
        M2[y][jzero] = -1;
    }
    M2[jzero][izero] = -1;

    /* Explore left child node according to given choice */
    solve_algorithm(M2, iteration + 1, eval_node_child);

    /* Do the modification on a copy of the distance matrix */
    Matrice M3(M);

    /**
     *  Modify the dist matrix to explore the other possibility : the non-choice
     *  of the zero with the max penalty
     */

    M3[izero][jzero] = -1;

        /* Explore right child node according to non-choice */
        solve_algorithm(&M2, iteration, eval_node_child);
    };

    void update_hach();
    void update_matrice();
    void create_matrice();
    void eval();
}

#endif //AG41_PROJET_ALGORITHM