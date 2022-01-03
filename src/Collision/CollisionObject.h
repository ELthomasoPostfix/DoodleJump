//
// Created by Thomas Gueutal on 13/11/2021.
//

#ifndef DOODLEJUMP_COLLISIONOBJECT_H
#define DOODLEJUMP_COLLISIONOBJECT_H

#include <utility>
#include <limits>
#include <functional>
#include "../Utility/Utility.h"
#include "../GameObject.h"

using Rect = std::array<std::pair<double, double>, 4>;

//! A class that provides collision functionality between ::CollisionObject s.
/*!
 *
 */
class CollisionObject : public GameObject {
    public:
        //! A constructor that assumes (\p positionX, \p positionY) to be the coordinates of the (center of the) collision shape.
            /*!
             * The constructor assumes that for a given shape, the shape contains
             * its points sorted in clockwise fashion.
             * \param positionX The x-coordinate of the collision shape's position.
             * \param positionY The y-coordinate of the collision shape's position.
             * \param shape The collision shape.
             * \param isPhysical Whether or not the ::CollisionObject participates in collision.
             */
            explicit CollisionObject(double positionX, double positionY, const Rect& shape, bool isPhysical);

            //! Check whether the caller's and \p other ::CollisionObject's collision shapes overlap.
            /*!
             * \note The use of lazy loading for the bounding box prevents the const qualification of the \p other
             * parameter.
             */
            bool checkCollision(CollisionObject& other);

            // TODO  clean this code up, it's too long and can probably be generalized
            //! Calculate the movement vector required for this ::CollisionObject to not collide with the container
            //! anymore.
            /*!
             * This function determines the vector with the opposite direction of the movement vector
             * required for undoing the collision of the caller ::CollisionObject with the container
             * ::CollisionObject. Once the push back vector is calculated, its magnitude can be additionally
             * manipulated using the scale factor parameter. This factor is interpreted as a percent, such that 1.0
             * corresponds to no adjustment, 1.1 corresponds to a 10% increase and .9 to a 10% decrease
             * in the magnitude of the push back vector.
             * It is possible to not require collision for the pushback calculation. In that case we extrapolate the
             * moveDir in the opposite direction. If the collision shape collides with the container collision
             * shape along this extrapolated "past" path, then this is handled as if such a "past" collision is
             * currently occurring. This way, it is possible to compensate for missed collisions due to
             * too large movements. In other words, this function does not predict missed collisions, that is up to
             * the caller.
             * \param moveDir The current movement direction of the collision object. It determines the direction
             * of the push back vector.
             * \param container The ::CollisionShape that supposedly collides with the caller.
             * \param scaleFactor The adjustment factor to the magnitude of the resulting push back vector.
             * \param requireCollision If true, it will surely return (0, 0) if the collision shape does
             * not currently collide with the container collision shape. Else return the push back vector
             * required to undo the collision. If false, extrapolate the moveDir into the opposite direction
             * and treat a possible past collision as if it is happening now.
             */
            std::pair<double, double> determinePushback(const std::pair<double, double>& moveDir,
                                                        CollisionObject& container, double scaleFactor = 1.0,
                                                        bool requireCollision = true);

            //! Set whether the ::CollisionObject participates in collision.
            void setIsPhysical(bool isPhysical);

            //! Check whether the ::CollisionObject participates in collision.
            bool isPhysical() const;

            //! get a copy of the collision shape.
            Rect getCollisionShape() const;

            //! The center of mass of the shape.
            /*! The center of mass of the collision object shape, calculated as
             * the average of the xy coordinates of all points part of the shape,
             * utilizing the actual point coordinates.
             *
             */
            static std::pair<double, double> determineAbsoluteCenterOfMass(const Rect& shape);

            //! The center of mass of the shape relative to the bottom left corner of the bounding box.
            /*! The center of mass of the collision object shape, calculated as
             * the average of the xy coordinates of all points part of the shape,
             * utilizing the point coordinates translated such that the bottom left
             * corner of its bounding box was translated to the origin, (0, 0).
             */
            static std::pair<double, double> determineRelativeCenterOfMass(const Rect& shape);

    protected:
            //! Move all points in the collision shape by the movement vector.
            /*!
             * \param moveX The x-coordinate of the movement vector.
             * \param moveY The y-coordinate of the movement vector.
             */
            void adjustCollisionShapePoints(double moveX, double moveY);

            //! Extend the ::GameObject::move(double, double) behaviour to also move the collision shape by the movement
            //! vector.
            /*!
             * \param moveX The x-coordinate of the movement vector.
             * \param moveY The y-coordinate of the movement vector.
             */
            void moveBehaviour(double moveX, double moveY) override;

            //! Move the ::CollisionObject, this includes its position and collision shape, to the specified location.
            /*!
             * Move the position member inherited from ::GameObject to the specified destination.
             * The points of the collision shape will be moved according to the same movement vector that
             * the position is moved along.
             * \param destinationX The x-coordinate to which the ::GameObject has just been moved.
             * \param destinationY The y-coordinate of the movement vector by which the ::GameObject
             * has just been moved.
             * \param prevX The x-coordinate the ::GameObject was just moved from.
             * \param prevY The y-coordinate the ::GameObject was just moved from.
             */
            void setBehaviour(double destinationX, double destinationY, double prevX, double prevY) override;

    private:

        //! Get the bounding box of the current collision shape.
        /*!
         * The bounding box of collision shape is the smallest rectangle that completely
         * contains the collision shape.
         */
        const std::array<double, 4>& getBoundingBox();

        //! Set the coordinates of a point in the collision shape.
        inline void setPoint(unsigned int index, double x, double y);

        //! Set the coordinates of a point in the collision shape.
        inline void adjustPoint(unsigned int index, double moveX, double moveY);

        inline const std::pair<double, double>& getPoint(unsigned int index);

        //! Check whether any point part of the contents, the ::CollisionObject's collision shape, are located within
        //! the bounding box of the container.
        static inline bool hasPointsInBounds(const std::array<double, 4> &bounds, const Rect& container);

        //! Check whether the point is located within the bounds.
        static inline bool pointIsInBounds(const std::array<double, 4> &bounds, const std::pair<double, double>& point);

        //! update the boundingBox of the ::CollisionObject.
        void updateBoundingBox();

    private:
        // TODO add a 'std::pair<double, double>& getPoint(index)' and give it graceful out of bounds index exception
        Rect _collisionShape;

        //! The bounding box contains the bottom left point followed by the top right point.
        std::array<double, 4> _boundingBox;
        bool _updated;

        bool _isPhysical;
};


#endif //DOODLEJUMP_COLLISIONOBJECT_H
