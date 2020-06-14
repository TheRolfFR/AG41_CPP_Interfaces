//
// Created by TheRolf on 14/06/2020.
//

#ifndef AG41_PROJET_POSITIONINTERFACES_H
#define AG41_PROJET_POSITIONINTERFACES_H

#include "jeuEssai.h"
#include "Position.h"

class PositionInterfaces : public Informations {
private:
    Position _positions[NBR_INTERFACES];
public:
    void nouvelleJournee() {
        for(int i = 0; i < NBR_INTERFACES; ++i) {
            _positions[i].first = 0.0;
            _positions[i].second = 0.0;
        }
    }

    Position operator[](int x) {
        return _positions[x];
    }
};


#endif //AG41_PROJET_POSITIONINTERFACES_H
