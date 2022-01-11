//
// Created by Thomas Gueutal on 08/01/2022.
//

#include "PlayerView.h"

PlayerView::PlayerView(Game &observer, Rect& collShape, Rect& viewArea)
    : Player(collShape), EntityView(observer, viewArea) {}

void PlayerView::display() {
    notify();
}

CollisionObject &PlayerView::getClipObject() {
    return _viewArea;
}

void PlayerView::moveBehaviour(double moveX, double moveY) {
    getCollisionObject().move(moveX, moveY);
    _viewArea.move(moveX, moveY);
}

void PlayerView::setBehaviour(double moveX, double moveY, double prevX, double prevY) {
    getCollisionObject().move(moveX, moveY);
    _viewArea.move(moveX, moveY);
}


