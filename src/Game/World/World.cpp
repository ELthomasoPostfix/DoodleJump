//
// Created by Thomas Gueutal on 13/11/2021.
//

#include "World.h"
#include "../GameObject/Entity/Player/Player.h"
#include "../../View/AbstractEntityFactory/AbstractEntityFactory.h"


/*
 *      PUBLIC methods
 */

std::unique_ptr<World>& World::getInstance() {
    static std::unique_ptr<World> world(new World);
    return world;
}

void World::processEntities(const double delta) {

    for (const auto& processable : _entities) {
        processable->process(delta);
    }
}

void World::requestViews() {
    for (const auto& bgEntity : _bgEntities) {
        bgEntity->display();
    }

    for (auto fgEntity = _entities.rbegin(); fgEntity != _entities.rend(); ++fgEntity) {
        fgEntity->get()->display();
    }
}

void World::clipEntities() {
    for (auto& entity : _entities) {
        if (!_camera->isVisible(entity->getClipObject()))
            removeEntity(entity);
    }
}

bool World::addEntity(const std::shared_ptr<Entity>& entity) {
    return addEntity(entity, _entities);
}

bool World::removeEntity(const std::shared_ptr<Entity> &entity) {
    return removeEntity(entity, _entities);
}

bool World::addBGEntity(const std::shared_ptr<Entity> &entity) {
    return addEntity(entity, _bgEntities);
}

bool World::removeBGEntity(const std::shared_ptr<Entity> &entity) {
    return removeEntity(entity, _bgEntities);
}

std::vector<SolidCollisionInfo>
World::getSolidCollisions(Entity& movingBody, const std::pair<double, double> &moveDir) {

    std::vector<SolidCollisionInfo> collisions;
    auto mbCollShape = movingBody.getCollisionObject();

    for (const auto& staticBody : _entities) {
        CollisionObject& otherCollShape = staticBody->getCollisionObject();
        if (!otherCollShape.isSolid())
            continue;
        if (&mbCollShape != &otherCollShape && mbCollShape.checkCollision(otherCollShape)) {
            const auto pushback = mbCollShape.determinePushback(moveDir, otherCollShape);

            // Pushback is valid
            if (pushback.first != 0.0 && pushback.second != 0.0) {
                SolidCollisionInfo info;
                info.collidedWith = staticBody;
                info.pushback = pushback;
                info.topCollision = mbCollShape.isAbove(info.collidedWith->getCollisionObject(),
                                                        info.pushback.second);
                info.sideCollision = !info.topCollision;
                collisions.emplace_back(std::move(info));
            }
        }
    }

    return std::move(collisions);
}

std::vector<NonSolidCollisionInfo>
World::getNonSolidCollisions(Entity& movingBody) {

    std::vector<NonSolidCollisionInfo> collisions;
    auto mbCollShape = movingBody.getCollisionObject();

    for (const auto& staticBody : _entities) {
        CollisionObject& otherCollShape = staticBody->getCollisionObject();
        if (otherCollShape.isSolid())
            continue;
        if (&mbCollShape != &otherCollShape && mbCollShape.checkCollision(otherCollShape)) {
                NonSolidCollisionInfo info;
                info.collidedWith = staticBody;
                collisions.emplace_back(std::move(info));
        }
    }

    return std::move(collisions);
}

void World::signalRoundEnd() {
    _roundOver = true;
}

bool World::roundHasEnded() {
    return _roundOver;
}

void World::setIndependentDimensions(unsigned int wWidth, unsigned int wHeight) {
    _camera->setIndependentDimensions(wWidth, wHeight);
}

void World::assignEntityFactory(std::unique_ptr<AbstractEntityFactory>& abstractEntityFactory) {
    _entityFactory = std::move(abstractEntityFactory);
}

void World::setCameraArea(Rect &cameraArea) {
    _camera->replaceCameraArea(cameraArea);
}

void World::projectViewArea(CollisionObject &viewArea) const {
    _camera->project(viewArea);
}



/*
 *      PRIVATE methods
 */

bool World::addEntity(const std::shared_ptr<Entity> &entity, std::vector<std::shared_ptr<Entity>>& vec) {
    auto it = std::find(vec.begin(), vec.end(), entity);

    if (it != vec.end() && &(**it) == &(*entity))
        return false;

    vec.emplace_back(entity);
    return true;
}

bool World::removeEntity(const std::shared_ptr<Entity> &entity, std::vector<std::shared_ptr<Entity>>& vec) {
    auto it = std::find(vec.begin(), vec.end(), entity);

    if (it != vec.end() && &(**it) == &(*entity)) {
        vec.erase(it);
        return true;
    }

    // TODO  Scroll camera down, go to end screen??
    if (roundHasEnded())
        _endAnimationFinished = false;

    return false;
}

World::World() {
    Rect tempCameraArea{DEFAULT_CAMERA_AREA};
    _camera = std::make_unique<Camera>(DEFAULT_CAMERA_WIDTH,
                                       DEFAULT_CAMERA_HEIGHT,
                                       tempCameraArea);
    _roundOver = false;
    _endAnimationFinished = true;
}

void World::test() {
    std::shared_ptr<Platform> platform = _entityFactory->createStaticPlatform();
    addEntity(platform);

    std::shared_ptr<Player> player = _entityFactory->createPlayer();
    addEntity(player);
}











