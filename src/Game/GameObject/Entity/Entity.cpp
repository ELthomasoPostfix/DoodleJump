//
// Created by Thomas Gueutal on 13/11/2021.
//

#include "Entity.h"


Entity::Entity(double positionX, double positionY) :
    GameObject(positionX, positionY) {}

View &Entity::getView() {
    return _view;
}

void Entity::process(double delta) {}


