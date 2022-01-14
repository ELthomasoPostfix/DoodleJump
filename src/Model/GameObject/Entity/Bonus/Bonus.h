//
// Created by Thomas Gueutal on 13/11/2021.
//

#ifndef DOODLEJUMP_BONUS_H
#define DOODLEJUMP_BONUS_H

#include "../Entity.h"
#include "../Player/Player.h"

//! The base class for all bonuses. A bonus may register as an observer to the player.
/*!
 * As an observer, a bonus gets notified of a collision with the player.
 * It can then influence the player based on the context of this collision.
 */
class Bonus : public Entity {
    public:
        explicit Bonus(Rect& rect);

        ~Bonus() override = default;

        //! Check collision circumstances and possibly activate the bonus.
        void notifyCollision(Player &collidedWith, bool playerIsSupported) override = 0;

    protected:
        bool _active;
};


#endif //DOODLEJUMP_BONUS_H
