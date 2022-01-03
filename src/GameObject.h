//
// Created by Thomas Gueutal on 15/11/2021.
//

#ifndef DOODLEJUMP_GAMEOBJECT_H
#define DOODLEJUMP_GAMEOBJECT_H

#include <utility>
#include <memory>

// TODO  this needed here?
class Game;

//! The base class for all movable objects and for all subcomponents of movable objects.
/*! The ::GameObject class functions as an abstract base class for all objects that require
 * some form of xy-position. It provides a move() method that allows a different movement
 * implementation for different types of movable objects.
 */
class GameObject {
public:
        GameObject(double positionX, double positionY);

        // TODO  Implement ::Game as written in this detailed descr.
        //! The entry point for the ::Game class to let a ::GameObject influence the game state.
        /*!
         * If a derived class desires to influence the game world every frame, then these
         * interactions should be implemented through deriving the process() function.
         * The ::Game class will call the process function of all registered ::GameObject objects,
         * after it has performed its physics step on the ::RigidBody objects.
         * \param delta How many seconds have passed since the previous frame was ready.
         */
        virtual void process(double delta);

        //! Move the ::GameObject by the specified movement vector.
        /*!
         * \note If additional behavior intrinsic to a call of the move() method is required,
         * then the move behaviour can be extended through implementation of the
         * moveBehaviour(double, double) method.
         * \param moveX The x-coordinate of the movement vector.
         * \param moveY The y-coordinate of the movement vector.
         */
        void move(double moveX, double moveY);

        //! Move the ::GameObject by the specified movement vector.
        /*!
         * \param moveVector The vector by which to move the ::GameObject.
         */
        void move(const std::pair<double, double>& moveVector);

        //! Move the ::GameObject to the specified location.
        /*!
         * \note If additional behavior intrinsic to a call of the setPosition() method is required,
         * then the setter behaviour can be extended through implementation of the
         * setBehaviour(double, double) method.
         * \param destinationX The x-coordinate to move to.
         * \param destinationY The y-coordinate to move to.
         */
        void setPosition(double destinationX, double destinationY);

        std::pair<double, double> getPosition() const;

protected:
        //! Move the location of the ::GameObject by the movement vector.
        /*!
         * \note When a derived class wants to alter the ::GameObject's location,
         * this function is to be called. Calling this function is a requirement
         */
        inline void adjustPosition(double moveX, double moveY)
        {
                _position.first += moveX;
                _position.second += moveY;
        };

        //! Extends the move(double, double) and move(const std::pair<double, double>&) behaviour.
        /*!
         * After the location of the ::GameObject is altered by the default move() behaviour,
         * this method is called.
         * \param moveX The x-coordinate of the movement vector by which the ::GameObject
         * has just been moved.
         * \param moveY The y-coordinate of the movement vector by which the ::GameObject
         * has just been moved.
         */
        virtual void moveBehaviour(double moveX, double moveY);

        //! Extends the setPosition(double, double) behaviour.
        /*!
         * After the location of the ::GameObject is altered by the default setPosition() behaviour,
         * this method is called.
         * \param destinationX The x-coordinate to which the ::GameObject has just been moved.
         * \param destinationY The y-coordinate of the movement vector by which the ::GameObject
         * has just been moved.
         * \param prevX The x-coordinate the ::GameObject was just moved from.
         * \param prevY The y-coordinate the ::GameObject was just moved from.
         */
        virtual void setBehaviour(double destinationX, double destinationY, double prevX, double prevY);

private:
        std::pair<double, double> _position;
};


#endif //DOODLEJUMP_GAMEOBJECT_H
