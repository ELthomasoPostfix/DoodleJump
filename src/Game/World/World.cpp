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
    auto it = _entities.begin();
    while (it != _entities.end()) {
        if (!_camera->isVisible((*it)->getClipObject()))
            (*it)->move(0, 600);
            //            it = _entities.erase(it);
        else
            ++it;
    }

    it = _bgEntities.begin();
    while (it != _bgEntities.end()) {
        if (!_camera->isVisible((*it)->getClipObject()))
            it = _bgEntities.erase(it);
        else
            ++it;
    }
}

void World::executeMurderBuffer() {
    for (auto & target : _murderBuffer) {
        auto entitiesIt = std::find_if(_entities.begin(), _entities.end(), [&](std::shared_ptr<Entity> const& p) {
            return &*p == &*(target); // assumes MyType has operator==
        });
        if (entitiesIt != _entities.end())
            _entities.erase(entitiesIt);

        auto bgEntitiesIt = std::find_if(_bgEntities.begin(), _bgEntities.end(), [&](std::shared_ptr<Entity> const& p) {
            return &*p == &*(target); // assumes MyType has operator==
        });
        if (entitiesIt != _entities.end())
            _entities.erase(entitiesIt);
    }

    _murderBuffer.clear();
}

void World::requestRemoval(const std::shared_ptr<Entity>& target) {
    _murderBuffer.emplace_back(target);
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
            const auto pushback = mbCollShape.determinePushback(moveDir, otherCollShape, 1.001);

            // Pushback is valid
            if (pushback.first != 0.0 || pushback.second != 0.0) {
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

std::pair<unsigned int, unsigned int> World::getCameraDimensions() const {
    return _camera->getDimensions();
}

const std::array<double, 4>& World::getCameraBoundingBox() const {
    return _camera->getBoundingBox();
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
    auto camDimensions = _camera->getDimensions();

    // TODO Also change the origin of the clipObject to the same as that of the collisionObject
    std::shared_ptr<StaticPlatform> platform = _entityFactory->createStaticPlatform();
    auto rcm = CollisionObject::determineRelativeCenterOfMass(platform->getCollisionObject().getCollisionShape());
    platform->getCollisionObject().setOrigin(platform->getCollisionObject().getBoundingWidth()/2.0,platform->getCollisionObject().getBoundingHeight());
    platform->getClipObject().setOrigin(platform->getClipObject().getBoundingWidth()/2.0, platform->getClipObject().getBoundingHeight());
    platform->setPosition(camDimensions.first/2.0, camDimensions.second/2.0);
    //platform->setPosition(camDimensions.first/2.0, -1);
    //addEntity(platform);
    // TODO spawn the platform just in sight and check if it gets clipped.
    //  If not, then move on !!

    std::shared_ptr<Player> player = _entityFactory->createPlayer();
    player->getCollisionObject().setOrigin(player->getCollisionObject().getBoundingWidth()/2.0, 0);
    player->getClipObject().setOrigin(player->getClipObject().getBoundingWidth()/2.0, 0);
    player->setPosition(camDimensions.first/2.0, camDimensions.second/2.0);
    addEntity(player);
}











