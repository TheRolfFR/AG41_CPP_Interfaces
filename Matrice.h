//
// Created by TheRolf on 13/06/2020.
//

#ifndef AG41_PROJET_MATRICE_H
#define AG41_PROJET_MATRICE_H

#include <iostream>
#include <cstring>
#include <iomanip>
#include "jeuEssai.h"
#include "CMatrix.h"

class Matrice : public CMatrix<double> {
public:
    Matrice(int rows, int cols) : CMatrix(rows, cols) {
    }

    Matrice(Matrice *m) : CMatrix(m->row, m->col) {
        for(unsigned int i = 0; i < row; ++i) {
            for(unsigned int j = 0; j < col; ++j) {
                this->data[i][j] = m->operator()(i, j);
            }
        }
    }

    friend std::ostream &operator<<(std::ostream &os, const Matrice &matrice) {
        return os;
    }
};


#endif //AG41_PROJET_MATRICE_H