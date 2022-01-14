//
// Created by Thomas Gueutal on 12/01/2022.
//

#ifndef DOODLEJUMP_SCOREBOARD_H
#define DOODLEJUMP_SCOREBOARD_H

#include "../../Utility/Utility.h"

class Entity;
class Camera;


class Scoreboard {
    public:
        Scoreboard();

        //! Update the current score by adding to it.
        void update(int score);

        //! Get the current score.
        int getScore() const;

        //! Reset the score to zero.
        void resetScore();

    private:
        int _score;
};


#endif //DOODLEJUMP_SCOREBOARD_H
