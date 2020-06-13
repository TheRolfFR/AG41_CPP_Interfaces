//
// Created by TheRolf on 13/06/2020.
//

#ifndef GL41_PROJET_MATRICE_H
#define GL41_PROJET_MATRICE_H

class Matrice {
private:
    bool _matrice[][];
public:
    Matrice(int lignes, int colonnes) {
        _matrice = new bool[lignes*colonnes];
    } // Constructs an empty list
};


#endif //GL41_PROJET_MATRICE_H
