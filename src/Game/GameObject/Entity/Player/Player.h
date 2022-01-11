//
// Created by Thomas Gueutal on 13/11/2021.
//

#ifndef DOODLEJUMP_PLAYER_H
#define DOODLEJUMP_PLAYER_H

#include "../Entity.h"

class Bonus;

class Player : public Entity {
    public:
        explicit Player(Rect& rect);

        ~Player() override;

        void process(double delta) final;

        //! Reset the downward pull to its original value.
        void resetDownwardPull();

        //! Reset the y-velocity of the player to its original (maximum) value.
        void resetYVelocity();

        //! Scale the downward pull by the specified amount until the player has traveled height in y-value.
        /*!
         * \param scale A scale with which the downward pull will be multiplied.
         * \param height How much the player must travel until the scale effect wears off.
         */
        void addDownwardPullScale(float scale, unsigned int height);

        //! Register a bonus that observes the player.
        void registerObserver(std::weak_ptr<Bonus>& observer);

        //! Get the default jump height of the player when they jump off of a solid object.
        double getJumpHeight() const;

    private:
        //! Move the player based on the delta time. Return whether the player ended up on top of a platform.
        bool handleMovement(double delta);

        //! Find the movement vector of the player based on delta time without accounting for collisions.
        std::pair<double, double> findMoveVector(double delta);

        //! Get the downward pull on the player.
        /*!
         * The downward pull on the player is subtracted from the velocity
         * of the player until they start falling instead of rising.
         */
        double getDownwardPull() const;

    private:
        double _downwardPull;
        std::vector<std::pair<float, unsigned int>> _pullScalers;
        std::pair<double, double> _velocity;
        double _terminalVelocity;
        double _jumpHeight;

        std::vector<std::weak_ptr<Entity>> _observers;       // TODO remove this ??? ==> No time for making jetpack follow user
};


#endif //DOODLEJUMP_PLAYER_H
