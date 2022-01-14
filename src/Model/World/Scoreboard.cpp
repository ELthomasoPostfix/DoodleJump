//
// Created by Thomas Gueutal on 12/01/2022.
//

#include "Scoreboard.h"

Scoreboard::Scoreboard() {
    _score = 0;

}

void Scoreboard::update(int score) {
    _score += score;
}

int Scoreboard::getScore() const {
    return _score;
}

void Scoreboard::resetScore() {
    _score = 0;
}

