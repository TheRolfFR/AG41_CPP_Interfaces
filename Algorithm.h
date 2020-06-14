
#pragma clang diagnostic push
#pragma ide diagnostic ignored "NotImplementedFunctions"
#pragma ide diagnostic ignored "UnusedStructInspection"
#pragma ide diagnostic ignored "UnusedGlobalDeclarationInspection"
#ifndef AG41_PROJET_ALGORITHM_H
#define AG41_PROJET_ALGORITHM_H

#include <map>
#include <cmath>
#include <vector>
#include "Matrice.h"
#include "jeuEssai.h"
#include "Informations.h"
#include "PositionInterfaces.h"

#define VALEUR_DEFAUT_MEILLEURE_VARIANCE -1

class Algorithm : public Informations
{
private :
    double meilleureVarianceKm;
    double meilleureVarianceHeures;
    std::vector<std::pair<int, int>> meilleureSolution;
    PositionInterfaces position;

    long sommeDureeFormations = 0;

    std::vector<std::pair<int, int>> _choix; ///< indice de la formation, indice de l'interface affectée

    bool premiereJournee = true;

    void calculSommeDureeFormations() {
        for(int z=0;z<NBR_FORMATION;z++)
        {
            sommeDureeFormations += dureeFormation(z);
        }
    }

    void mettreAJourSolution(int iteration, int indiceInterface, int indiceFormation) {
        _choix[iteration-1].first = indiceFormation;
        _choix[iteration-1].second = indiceInterface;
    }

    double distancePourFormation(int indiceInterface, int indiceFormation) {
        double resultat = 0;
        // si c'est le début de journée, on revient chez soi et le lendemain
        // on va de chez soi à la SESSAD puis de la SESSAD à la maison de l'apprenant
        if(position[indiceInterface].first == 0.0 && position[indiceInterface].second == 0.0) {
            if(!premiereJournee) {
                // on ajoute le trajet de la veille
                resultat += 0;
            }

            // on ajoute le trajet du domicile au SESSAD
            resultat += distanceEntre(maisonInterface(indiceInterface), INDICE_CENTRE_SESSAD);

            premiereJournee = false;
        }

        int mNouvelApprenti = maisonApprenti(indiceFormation);
        int mFormation = maisonFormation(indiceFormation);

        // puis de la ou j'étais au domicile du nouvel apprenant
        resultat += distanceEntre(INDICE_CENTRE_SESSAD, mNouvelApprenti);

        // puis du nouvel apprenant au centre de formation
        // puis du centre de formation a la maison de l'apprenti
        resultat += 2* distanceEntre(mNouvelApprenti, mFormation);

        return resultat;
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

    std::pair<double, long> totalInterface(int interface, int iteration) {
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

            if(indiceInterface == interface && interface < iteration) { // si c'est la bonne interface
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

    std::pair<double, double> calculVariances() {
        return calculVariances(NBR_FORMATION-1);
    }

    std::pair<double, double> calculVariances(int iteration) {
        // initialisation
        std::map<int, double> totalKm;
        std::map<int, long> totalHeures;

        // on somme et on min
        double sommeKm = 0;
        long sommeHeures = 0;
        for(unsigned int i = 0; i < NBR_INTERFACES; ++i) {
            std::pair<double, long> res = totalInterface(i, iteration);

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

        return std::pair<double, double> (sommeKm/NBR_INTERFACES, sommeHeures/NBR_INTERFACES);
    }

    void affectationMeilleureSolution(double varianceKm, double varianceHeures) {
        meilleureVarianceKm = varianceKm;
        meilleureVarianceHeures = varianceHeures;
        meilleureSolution = _choix;

        std::cout << "Variance de km    : " << varianceKm << std::endl;
        std::cout << "Variance d'heures : " << varianceHeures << std::endl;

        std::cout << "Solution : " << std::endl;

        for(std::vector<std::pair<int, int>>::iterator c = meilleureSolution.begin(); c != meilleureSolution.end(); ++c) {
            std::cout << c->first << " : " << c->second << std::endl;
        }
    }

    void construireSolution() {
        std::pair <double, double> var = calculVariances();

        double varianceKm = var.first/NBR_INTERFACES;
        double varianceHeures = var.second/NBR_INTERFACES;
        /*
         * La meilleure solution se base sur le gain en poucentage de variablité de la variance sommé entre heures et distances)
         */

        double diffVarianceKm = meilleureVarianceKm - varianceKm;
        double diffVarianceHeures = meilleureVarianceHeures - varianceHeures;

        // pas encore de meilleure solution
        if(meilleureVarianceKm == VALEUR_DEFAUT_MEILLEURE_VARIANCE || meilleureVarianceHeures == VALEUR_DEFAUT_MEILLEURE_VARIANCE) {
            affectationMeilleureSolution(varianceKm, varianceHeures);
            return;
        }

        // sinon si fait le rapport de diff
        double rapportKm = diffVarianceKm/meilleureVarianceKm;
        double rapportHeures = diffVarianceHeures/meilleureVarianceHeures;

        double gainVariance = rapportKm + rapportHeures;


        if(gainVariance > 0) {
            affectationMeilleureSolution(varianceKm, varianceHeures);
            meilleureSolution = _choix;
        }

        return;
    }
    //initialisation de M
    //Si l'interface i est compétente pour une tâche y, M[i][y]=0 sinon M[i][y]=-1
    void init(Matrice &M)
    {
        for(int i=0;i<NBR_APPRENANTS;++i)
        {
            for(int j=0;j<NBR_FORMATION;++j)
            {
                /* try
                 {
                     if(formation[j][1] == -1)
                         throw "Sans formation.";
                     else
                     {
                         if(formation[j][1] != specialite_interfaces[i]) // vérification des spécialités des interfaces
                         {
                             M2(i, j) = -1;
                         }
                     }

                 }
                 catch (String const& chaine)
                 {
                     //do nothing
                 }*/
                if (competences_interfaces[i][formation[j][INDICE_COMPETENCE_INTERFACE_FORMATION]] == 0) // vérification des compétences des interfaces
                    M(i, j) = -1;
            }
        }
        return;
    };

    void resoudreAlgorithme(Matrice *M0, int iteration, double mfKm, double mfH)
    {
        if (iteration == NBR_FORMATION+1)
        {
            construireSolution();
            return;
        }

        /* Fais les modifications sur une copie de la matrice */

        Matrice M(M0);

        int i, j ;

        /**
         * soustrait le min de chaque line et le min de chaque colonne
         * et met à jour l'évaluation du noeud actuel
         */
        bool estZero = true;
        i = 0;
        while (estZero && i<NBR_INTERFACES)
        {
            for(j=0;j<NBR_FORMATION;++j)
            {
                if (M(i, j) == 0)
                {
                    estZero = false;
                }
            }
            i++;
        }

        if (!estZero)
        {
            long min_column[NBR_FORMATION];

            for(i=0;i<NBR_FORMATION;++i)//parcours de chaque colonne
            {
                min_column[i] = -1.0;
                for(j=0;j<NBR_INTERFACES;++j)// parcours de chaque ligne
                {
                    if(M(j, i)>=0 && (min_column[i]<0||min_column[i]>M(j, i)))//on trouve le min de la colonne
                    {
                        min_column[i] = M(j, i);
                    }
                }
                for(j=0;j<NBR_INTERFACES;++j)//on soutrait le min à chaque coef de la colonne
                {
                    if(M(j, i)>=0)
                    {
                        M(j, i) -= min_column[i];
                    }
                }

            }

            double min_row[NBR_INTERFACES];
            for(i=0;i<NBR_INTERFACES;++i)
            {
                min_row[i] = -1;
                for(j=0;j<NBR_FORMATION;++j)
                {
                    if(M(i, j)>=0 && (min_row[i]<0||min_row[i]>M(i, j)))
                    {
                        min_row[i] = M(i, j);
                    }
                }
                for(j=0;j<NBR_FORMATION;++j)
                {
                    if(M(i, j)>=0)
                    {
                        M(i, j) -= min_row[i];
                    }
                }
            }
        }

        // std::cout << iteration << std::endl << M << std::endl;

        /* Coupe: arrêt de l'exploration de ce noeud */
        if (meilleureVarianceHeures != VALEUR_DEFAUT_MEILLEURE_VARIANCE && meilleureVarianceKm != VALEUR_DEFAUT_MEILLEURE_VARIANCE)
        {
            std::pair<double, double > variances = calculVariances(iteration-1);

            double diffVarKm = meilleureVarianceKm - variances.first;
            double diffVarHeures = meilleureVarianceHeures - variances.second;

            if (diffVarKm > mfKm || diffVarHeures > mfH) {
                // std::cout << "Jme tire à l'itération " << iteration << std::endl;
                return;
            }
        }
        /**
         *  Additionne les pénalités pour trouver le zéro avec max pénalités
         *  S'il n'y a pas de zéro dans la matrice retourne "matrice infesable"
         */

        /* ligne et column du zéro avec le max pénalité */
        int izero=-1, jzero=-1 ;
        long max_zero = -3;

        for(i=0;i<NBR_INTERFACES;++i)
        {
            for(j=0;j<NBR_FORMATION;++j)
            {
                if(M(i, j) == 0.0)
                {
                    double min_row_zero = -1;
                    double min_column_zero = -1;
                    //recherche du min de la ligne
                    for(int y1=0;y1<NBR_FORMATION;++y1)
                    {
                        if((M(i, y1)>=0 && (min_row_zero<0||min_row_zero>M(i, y1))) && (y1!=j))
                        {
                            min_row_zero = M(i, y1);
                        }
                    }
                    //recherche du min de la colonne
                    for(int y2=0; y2<NBR_INTERFACES; y2++)
                    {
                        if((M(y2, j)>=0 && (min_column_zero<0||min_column_zero>M(y2, j))) && (y2!=i))
                        {
                            min_column_zero = M(y2, j);
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
            // std::cout << "Solution Infaisable" << std::endl;
            return;
        }


        /**
         *  Met à jour l'évaluation de la solution
         */

        mettreAJourSolution(iteration, izero, jzero);

        /* Fais les modifications sur une copie de la matrice */
        Matrice M2(&M);

        /**
         *  Modifie la matrice M2 en fonction du choix du zero de pénalité max
         */
        // ajout de la distance pour la tache à tout les éléments de la ligne du zero
        for(int y=0;y<NBR_FORMATION;++y)
        {
            if(M2(izero, y) != -1)
            {
                //(duree*distance)/duree_totale
                M2(izero, y)= (dureeFormation(jzero)*distancePourFormation(izero,jzero))/ (double) sommeDureeFormations;
            }
        }
        // met à -1 tout les éléments de la colonne du zero
        for(int y=0;y<NBR_INTERFACES;++y)
        {
            M2(y, jzero) = -1;
        }
        M2(jzero, izero) = -1;

        // std::cout << iteration << std::endl << M << std::endl;

        /* Explore le noeud enfant gauche conformément au choix donné */
        resoudreAlgorithme(&M2, iteration + 1, mfKm, mfH);

        /* fait les modification sur une copie de la matrice */
        Matrice M3(&M);

        /**
         *  Modifie la matrice pour explorer l'autre possibilité, le nom choix
         *  du zero avec pénalité max
         */

        M3(izero, jzero) = -1;

        /* explore le noeud enfant droit conformément au non-choix */
        resoudreAlgorithme(&M3, iteration, mfKm, mfH);
    };
public:

    Algorithm() :
        meilleureVarianceKm(VALEUR_DEFAUT_MEILLEURE_VARIANCE),
        meilleureVarianceHeures(VALEUR_DEFAUT_MEILLEURE_VARIANCE),
        meilleureSolution(NBR_FORMATION, std::pair<int, int>(-1,-1)),
        position(),
        _choix(NBR_FORMATION, std::pair<int, int>(-1,-1)) {

        calculSommeDureeFormations();

    }

    void lancer(double mfKm, double mfH) {
        Matrice m(NBR_INTERFACES, NBR_FORMATION);
        init(m);
        this->resoudreAlgorithme(&m, 1, mfKm, mfH);
    }
};

#endif //AG41_PROJET_ALGORITHM