//
// Created by Thomas Gueutal on 05/01/2022.
//

#include "View.h"


/*
 *      PUBLIC methods
 */

void View::move(const std::pair<double, double> &moveVector) {
    _viewArea->move(moveVector);
}

void View::setPosition(const std::pair<double, double> &destination) {
    _viewArea->setPosition(destination);
}

const std::unique_ptr<CollisionObject> &View::getViewArea() {
    return _viewArea;
}

