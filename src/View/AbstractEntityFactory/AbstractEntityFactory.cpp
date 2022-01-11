//
// Created by Thomas Gueutal on 07/01/2022.
//

#include "AbstractEntityFactory.h"

/*
 *      PUBLIC methods
 */

AbstractEntityFactory::AbstractEntityFactory(Game &observer, const TexturesInfo& info)
    : observer(observer), info(info) {}

Rect AbstractEntityFactory::createRect(double width, double height) {
    return {{{0, 0}, {width, 0}, {width, height}, {0, height}}};
}
