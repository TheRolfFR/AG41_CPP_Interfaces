#include <iostream>

#include "Algorithm.h"
#include <string>

int main(int argc, char* argv[]) {
    double fluctuationMaxKm;
    double fluctuationMaxHeures;

    if(argc < 3) {
        std::cout << "Le programme nécessite 2 arguments : <FLUCTUATION_MAX_KM> <FLUCTUATION_MAX_HEURES>" << std::endl;

        fluctuationMaxKm = 10;
        fluctuationMaxHeures = 10;

        std::cout << "Il sera lancé avec les valeurs par défaut : " << fluctuationMaxKm << " " << fluctuationMaxHeures << std::endl;
    } else {
        try {
            fluctuationMaxKm = std::stod(argv[1]);
            fluctuationMaxHeures = std::stod(argv[2]);
        } catch(const std::exception& e) {
            std::cerr << "Impossible de récupérer les paramètres : " << e.what() << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    Algorithm a;

    std::cout << "Lancement de l'algorithme : " << fluctuationMaxKm << ", " << fluctuationMaxHeures << std::endl;
    a.lancer(fluctuationMaxKm, fluctuationMaxHeures);
    std::cout << "Fin de l'algorithme" << std::endl;

    return 0;
}
