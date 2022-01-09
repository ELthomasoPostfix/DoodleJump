//
// Created by Thomas Gueutal on 05/01/2022.
//

#ifndef DOODLEJUMP_ENTITYVIEW_H
#define DOODLEJUMP_ENTITYVIEW_H

#include "../../Game/GameObject/Collision/CollisionObject.h"

class Game;


// TODO     The EntityView class will notify the Game class that it has changed.
//  ==> Give the AbstractEntityFactory a reference to Game, then it can attach this reference to the views
//  ==> View then calls a callback function of Game or just calls a Game method. This Game method then polls
//      the relevant view for changes
//              Game->notify(const EntityView& changedView) {
//                  window.draw(changedView);
//              }
class EntityView {
    public:
        explicit EntityView(Game& observer);

        virtual ~EntityView();

        // TODO  Add a override notify() implementation of the PlayerView to signal
        //  that the game is over because the player is dead???
        //  Why would we update() the Game that a view location has changed when stuff is drawn
        //  all the time? --> Instead, call a notify to add an entity to a list of ViewEntities inside of
        //  Game, or when some other state similar to player death changes???
        //! Notify all observers of the change in view state.
        void notify();

        //! Move the ::View by the moveVector.
        void move(const std::pair<double, double>& moveVector);

        //! Move the bottom left corner of the ::View to the destination.
        void setPosition(const std::pair<double, double>& destination);

        //! Get the bounding box in world space coordinates of the view.
        const std::unique_ptr<CollisionObject>& getViewArea();

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

    protected:
        void setTextureID(size_t textureID);

    protected:
        std::unique_ptr<CollisionObject> _viewArea;
        size_t _textureID;
        bool _hasTexture;
        std::array<uint8_t, 3> _rgbFillColor;

        Game& _observer;        // TODO  is Game a View observer? Should Camera be one instead?


};


#endif //DOODLEJUMP_ENTITYVIEW_H