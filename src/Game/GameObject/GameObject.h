//
// Created by Thomas Gueutal on 15/11/2021.
//

#ifndef DOODLEJUMP_GAMEOBJECT_H
#define DOODLEJUMP_GAMEOBJECT_H

#include <utility>
#include <memory>

// TODO  this needed here?
class World;

//! The base class for all movable objects and for all subcomponents of movable objects.
/*! The ::GameObject class functions as an abstract base class for all objects that require
 * some form of xy-position. It provides a move() method that allows a different movement
 * implementation for different types of movable objects.
 */
class GameObject {
    public:
        GameObject(double positionX, double positionY);

        explicit GameObject(std::pair<double, double>  position);

        virtual ~GameObject() = default;

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
         * setBehaviour() method.
         * \param destinationX The x-coordinate to move to.
         * \param destinationY The y-coordinate to move to.
         * \param doSetBehaviour Whether to invoke the setBehaviour() method.
         */
        void setPosition(double destinationX, double destinationY, bool doSetBehaviour = true);
        void setPosition(const std::pair<double, double>& destination, bool doSetBehaviour = true);

        //! Get the position of the ::GameObject.
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
         * \param moveX The x-coordinate of the movement vector by which the ::GameObject
         * has just been moved.
         * \param moveY The y-coordinate of the movement vector by which the ::GameObject
         * has just been moved.
         * \param prevX The x-coordinate the ::GameObject was just moved from.
         * \param prevY The y-coordinate the ::GameObject was just moved from.
         */
        virtual void setBehaviour(double moveX, double moveY, double prevX, double prevY);

    private:
        std::pair<double, double> _position;

};


#endif //DOODLEJUMP_GAMEOBJECT_H
