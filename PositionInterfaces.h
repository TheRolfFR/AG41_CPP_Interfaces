//
// Created by TheRolf on 14/06/2020.
//

#ifndef AG41_PROJET_POSITIONINTERFACES_H
#define AG41_PROJET_POSITIONINTERFACES_H

#include "jeuEssai.h"

class PositionInterfaces {
private:
    std::pair<float, float> _positions[NBR_INTERFACES];
public:
    PositionInterfaces();
    void nouvelleJournee();
    std::pair<float, float> operator[](int x);
};


#endif //AG41_PROJET_POSITIONINTERFACES_H
