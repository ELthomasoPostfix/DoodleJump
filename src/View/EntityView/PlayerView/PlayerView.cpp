//
// Created by Thomas Gueutal on 08/01/2022.
//

#include "PlayerView.h"

PlayerView::PlayerView(Game &observer, double positionX, double positionY) : EntityView(observer),
                                                                             Player(positionX, positionY) {
    // TODO construct _viewArea
    //_textureID = PLAYER

}

void PlayerView::display() {

}
