//
// Created by Thomas Gueutal on 05/01/2022.
//

#ifndef DOODLEJUMP_ENTITYVIEW_H
#define DOODLEJUMP_ENTITYVIEW_H

#include "../resources.h"
#include "../../Game/World/Event.h"
#include "../../Game/GameObject/Collision/CollisionObject.h"

class Game;


class EntityView {
    public:
        explicit EntityView(Game& observer, Rect& viewArea);

        virtual ~EntityView();

        // TODO  Add a override notify() implementation of the PlayerView to signal
        //  that the game is over because the player is dead???
        //  Why would we update() the Game that a view location has changed when stuff is drawn
        //  all the time? --> Instead, call a notify to add an entity to a list of ViewEntities inside of
        //  Game, or when some other state similar to player death changes???
        //! Notify all observers that the view is ready to be drawn.
        void notify();

        //! Move the view by the moveVector.
        void move(const std::pair<double, double>& moveVector);

        //! Move the bottom left corner of the view to the destination.
        void setPosition(const std::pair<double, double>& destination);

        //! Get the bounding box in world space coordinates of the view.
        CollisionObject& getViewArea();

        //! Get the id of the texture used by this view. A view may not use a texture.
        /*!
         * If the view was assigned a texture, then a valid texture id
         * will be returned for use in the texture manager of ::Window/
         * If no texture was assigned, it is not guaranteed that a
         * valid texture id will be returned. There is no default
         * id value to indicate a texture-less view. Instead, utilize
         * the ::EntityView::hasTexture() method to verify.
         */
        size_t getTextureID() const;

        //! Check whether the view was assigned a texture.
        bool hasTexture() const;

        //! In case the view has not texture, then it will be assigned a fill color.
        /*!
         * The fill color can be used to represent the view as a rectangle of
         * the specified color. Even without a texture, the view may still
         * be simply represented. The color is represented by RGB values.
         */
        const std::array<uint8_t, 3>& getRGBFillColor() const;

        //! Set the id of the texture to use when displaying the entity.
        void setTextureID(size_t textureID);

        //! Set the color of the rectangle representation when displaying the entity.
        void setFillColor(unsigned int red, unsigned int green, unsigned int blue);

    protected:
        //! Make a copy of the to display view information, to pass to the observer.
        EntityView getViewCopy() const;

    protected:
        CollisionObject _viewArea;
        size_t _textureID;
        bool _hasTexture;
        std::array<uint8_t, 3> _rgbFillColor;

        Game& _observer;        // TODO  is Game a View observer? Should Camera be one instead?


};


#endif //DOODLEJUMP_ENTITYVIEW_H
