//
// Created by Thomas Gueutal on 13/11/2021.
//

#ifndef DOODLEJUMP_BONUS_H
#define DOODLEJUMP_BONUS_H

#include "../Entity.h"
#include "../Player/Player.h"


class Bonus : public Entity {
    public:
        explicit Bonus(Rect& rect);

        ~Bonus() override = default;

        void process(double delta) = 0;

        // TODO  do exception handling for locking the observable in implementations
        //! Attempt to activate the bonus. If this succeeds, true is returned.
        virtual bool update(bool callerIsSupported) = 0;

        void setObservable(const std::weak_ptr<Player>& observable);

    protected:
        std::weak_ptr<Player> _observable;
        bool _active;
};


#endif //DOODLEJUMP_BONUS_H
