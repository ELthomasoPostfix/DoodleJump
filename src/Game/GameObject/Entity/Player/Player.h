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

        //! Scale the downward pull by the specified amount.
        /*!
         * \param scale A scale with which the downward pull will be multiplied.
         */
        void addDownwardPullScale(float scale);

        //! Remove one of the scaling factors applicable to the downward pull.
        /*!
         * \param scale The scale with which the downward pull was being multiplied to be removed.
         */
        void removeDownwardPullScale(float scale);

        //! Reset the y-velocity of the player to its original (maximum) value.
        void resetYVelocity();

        //! Register a bonus that observes the player.
        void registerObserver(std::weak_ptr<Bonus>& observer);

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
        std::vector<float> _pullScalers;
        std::pair<double, double> _velocity;
        double _terminalVelocity;

        std::vector<std::weak_ptr<Bonus>> _observers;
};


#endif //DOODLEJUMP_PLAYER_H
