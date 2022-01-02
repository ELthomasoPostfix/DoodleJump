//
// Created by Thomas Gueutal on 15/11/2021.
//

#ifndef DOODLEJUMP_GAMEOBJECT_H
#define DOODLEJUMP_GAMEOBJECT_H

#include <utility>
#include <memory>

//! The base class for all movable objects and for all subcomponents of movable objects.
/*! The ::GameObject class functions as an abstract base class for all objects that require
 * some form of xy-position. It provides a move() method that allows a different movement
 * implementation for different types of movable objects.
 */
class GameObject {
public:
    GameObject(double positionX, double positionY);

    //! Move the GameObject to the specified location.
    virtual void move(double destinationX, double destinationY) = 0;

    std::pair<double, double> getPosition() const;

protected:
    // TODO  make setPosition() public, but delete it in subclasses the may only access move()
    //  ==> good idea?
    void setPosition(double destinationX, double destinationY);

private:
    std::pair<double, double> _position;

};


#endif //DOODLEJUMP_GAMEOBJECT_H
