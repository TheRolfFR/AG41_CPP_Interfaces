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
    std::vector<long*> _matrice;

    void createMatrix() {
        for(int i = 0; i < _lignes; ++i) {
            _matrice[i] = new long[_colonnes];

            for(int j = 0; j < _colonnes; ++j) {
                _matrice[i][j] = 0;
            }
        }
    }
public:
    Matrice(int lignes, int colonnes) : _lignes(lignes), _colonnes(colonnes), _matrice(lignes, nullptr) {
        createMatrix();
    }

    Matrice(const Matrice& autre) : _lignes(autre._lignes), _colonnes(autre._colonnes), _matrice(autre._lignes, nullptr) {
        createMatrix();

        for(unsigned int i = 0; i < _lignes; ++i) {
            this->_matrice[i] = new long[_colonnes];
            for(unsigned int j = 0; j < _colonnes; ++j) {
                this->_matrice[i][j] = autre._matrice[i][j];
            }
        }
    }

    Matrice(Matrice* autre) : _lignes(autre->_lignes), _colonnes(autre->_colonnes), _matrice(autre->_lignes, nullptr)  {

        createMatrix();

        for(unsigned int i = 0; i < _lignes; ++i) {
            this->_matrice[i] = new long[_colonnes];
            for(unsigned int j = 0; j < _colonnes; ++j) {
                this->_matrice[i][j] = autre->_matrice[i][j];
            }
        }
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
};


#endif //AG41_PROJET_MATRICE_H