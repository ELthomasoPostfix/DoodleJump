//
// Created by Thomas Gueutal on 29/12/2021.
//

#ifndef DOODLEJUMP_CAMERA_H
#define DOODLEJUMP_CAMERA_H

#include "Scoreboard.h"
#include "../GameObject/Collision/CollisionObject.h"

#define DEFAULT_CAMERA_WIDTH    600
#define DEFAULT_CAMERA_HEIGHT   800
#define DEFAULT_CAMERA_AREA     {{0.0, 0.0}, {1000.0, 0.0}, {1000.0, 1000.0}, {0.0, 1000.0}}



class Camera {
    public:
        //! Define the independent coordinate system and the absolute view area onto the world space. Also supply a scoreboard observer
        Camera(const std::shared_ptr<Scoreboard>& observer, double wWidth, double wHeight, Rect& viewArea);

        //! Get the dimensions, (width, height), of the rectangle onto which the ::Camera object will project the ::World.
        std::pair<unsigned int, unsigned int> getDimensions();

        //! Get the dimensions of the independent coordinate system the ::Camera object will projects the world coordinates onto.
        std::pair<double, double> getIndependentDimensions();

        //! Set the dimensions of the independent coordinate system the ::Camera object will projects the world coordinates onto.
        void setIndependentDimensions(double width, double height);

        //! Move the ::Camera by the moveVector.
        void move(double moveX, double moveY);
        void move(const std::pair<double, double>& moveVector);

        //! Move the ::Camera's position to the destination.
        void setPosition(const std::pair<double, double>& destination);

        //! Check whether the view is visible inside the ::Camera object's camera area.
        /*!
         * \note As the ::World object constitutes the Model component of the MVC design,
         * the ::EntityView component is not available here by design. Instead, the
         * ::Entity::getClipObject() method will ensure that any EntityView deriving
         */
        bool isVisible(CollisionObject& viewArea);

        //! Get the bounding box of the ::Camera.
        /*!
         * The bounding box of the camera describes which section of the ::World
         * object's world space the camera will keep and transform into the
         * needed independent coordinate system. The rest of the world space will be
         * clipped.
         */
        const std::array<double, 4>& getBoundingBox();

        //! Project the view area <b>in place</b> onto its relative position within the independent coordinate system.
        /*!
         * In more concrete terms, we first compress the x-axis by a factor cameraArea.x and then
         * stretch it by a factor of independentDimensions.x. We then work similarly for the y-axis
         * and the cameraArea.y and independentDimensions.x values.
         * After that, we translate the scaled coordinates so that the bottom left corner of the
         * scaled camera area coincides with the Origin (0, 0).
         */
        void project(CollisionObject& viewArea);

        //! Replace the camera area.
        void replaceCameraArea(Rect& newArea);

        //! Get the y-coordinate that the camera thinks should be exceeded before a move should happen.
        double getFocusY() const;

    private:
        //! Set the focus point y-value to where it should be based upon the camera view area.
        void recalibrateFocusY();

        //! Move the focus of the camera.
        /*!
         * \note If the focus is manually adjusted, the scoreboard
         * must also manually be alerted if the change in the focus.
         */
        void moveYFocus(double moveY);

        //! Print out a generic error message about moving the camera, plus the cause.
        static void printCameraError(const std::string& what);

    private:
        double _wWidth;
        double _wHeight;
        CollisionObject _cameraArea;
        double _focusY;

        std::shared_ptr<Scoreboard> _observer;
};


#endif //DOODLEJUMP_CAMERA_H
