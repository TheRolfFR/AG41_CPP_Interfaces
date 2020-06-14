//
// Created by TheRolf on 13/06/2020.
//

#ifndef AG41_PROJET_MATRICE_H
#define AG41_PROJET_MATRICE_H

#include <iostream>
#include <cstring>
#include <iomanip>
#include "jeuEssai.h"

class Matrice {
private:
    int _lignes;
    int _colonnes;
    long **_matrice;

    void createMatrix() {
        _matrice = new long *[_lignes];

        for(int i = 0; i < _lignes; ++i) {
            _matrice[i] = new long[_colonnes];

            for(int j = 0; j < _colonnes; ++j) {
                _matrice[i][j] = 0;
            }
        }
    }
public:
    Matrice(int lignes, int colonnes) : _lignes(lignes), _colonnes(colonnes) {
        createMatrix();
    }

    Matrice(const Matrice& autre) : _lignes(autre._lignes), _colonnes(autre._colonnes) {
        _matrice = new long*[_lignes];

        createMatrix();

        std::memcpy(_matrice, autre._matrice, sizeof(bool)*_lignes*_colonnes);
    }

    Matrice(Matrice* autre) : _lignes(autre->_lignes), _colonnes(autre->_colonnes) {
        _matrice = new long*[_lignes];

        createMatrix();

        std::memcpy(_matrice, autre->_matrice, sizeof(bool)*_lignes*_colonnes);
    }

    long* operator[](int x) {
        return _matrice[x];
    }

    friend std::ostream &operator<<(std::ostream &os, const Matrice &matrice) {
        os << "Matrice ["
        << matrice._lignes
        << ", "
        << matrice._colonnes
        << "]"
        << std::endl;

        for(int i = 0; i < matrice._lignes; ++i) {
            for(int j = 0; j < matrice._colonnes; ++j) {
                os << matrice._matrice[i][j] << std::setprecision(2) << " ";
            }
            os << std::endl;
        }

        return os;
    }

    virtual ~Matrice() {
        for(unsigned int i = 0; i < _lignes; ++i) {
            delete _matrice[i];
        }
        delete _matrice;
    }
};


#endif //AG41_PROJET_MATRICE_H