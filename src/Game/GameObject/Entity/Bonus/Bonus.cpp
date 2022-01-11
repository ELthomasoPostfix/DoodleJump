//
// Created by Thomas Gueutal on 13/11/2021.
//

#include "Bonus.h"

/*
 *      PUBLIC methods
 */

Bonus::Bonus(Rect &rect) : Entity(rect, true, false) {
    _active = false;
}

void Bonus::setObservable(const std::weak_ptr<Player> &observable) {
    _observable = observable;
}
