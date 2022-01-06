//
// Created by Thomas Gueutal on 05/01/2022.
//

#ifndef DOODLEJUMP_VIEW_H
#define DOODLEJUMP_VIEW_H

#include "../Collision/CollisionObject.h"



class View {
    public:

        //! Move the ::View by the moveVector.
        void move(const std::pair<double, double>& moveVector);

        //! Move the bottom left corner of the ::View to the destination.
        void setPosition(const std::pair<double, double>& destination);

        const std::unique_ptr<CollisionObject>& getViewArea();

    private:
        std::unique_ptr<CollisionObject> _viewArea;


};


#endif //DOODLEJUMP_VIEW_H
