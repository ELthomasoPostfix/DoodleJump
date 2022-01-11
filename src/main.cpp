#include <iostream>

#include "Game.h"

// TODO  to modify difficulty, modify standard deviation of the normal distribution of Random???
//  ==> If we normalize the result of random to the rang [0, 1], and we multiply default
//  platform distance by the random result, then the platform will be located to the
//  middle end of the distribution more often if the stddev is low. If the stddev is
//  higher, then there is more chance for the platform to be spawned at a further distance instead

// TODO  use  https://homepage.divms.uiowa.edu/~mbognar/applets/normal.html to
//  determine good stddev for random
//      Random(seed, .5, .15)       ??


void windowTest()
{

        // TODO set window VSync to true
        //  cap framerate at 60
        unsigned int wWidth = 600;
        unsigned int wWidthH = wWidth/2;
        unsigned int wHeight = 800;
        unsigned int wHeightH = wHeight/2;
        sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "SFML works!");
        window.setFramerateLimit(60);

        sf::CircleShape shape(100.f);
        // shape.setOrigin(50.f, 50.f);
        // shape.setPosition(300 - 50.f, 400 - 50.f);
        shape.setPosition(300, 400);
        shape.setFillColor(sf::Color::Green);

        sf::ConvexShape quadI;
        quadI.setPointCount(4);
        quadI.setPoint(0, sf::Vector2f(0, 0));
        quadI.setPoint(1, sf::Vector2f(300, 0));
        quadI.setPoint(2, sf::Vector2f(300, 400));
        quadI.setPoint(3, sf::Vector2f(0, 400));
        quadI.setFillColor(sf::Color::Blue);
        sf::ConvexShape quadII;
        quadII.setPointCount(4);
        quadII.setPoint(0, sf::Vector2f(300, 0));
        quadII.setPoint(1, sf::Vector2f(600, 0));
        quadII.setPoint(2, sf::Vector2f(600, 400));
        quadII.setPoint(3, sf::Vector2f(300, 400));
        quadII.setFillColor(sf::Color::Cyan);
        sf::ConvexShape quadIII;
        quadIII.setPointCount(4);
        quadIII.setPoint(0, sf::Vector2f(300, 400));
        quadIII.setPoint(1, sf::Vector2f(600, 400));
        quadIII.setPoint(2, sf::Vector2f(600, 800));
        quadIII.setPoint(3, sf::Vector2f(300, 800));
        quadIII.setFillColor(sf::Color::Magenta);
        sf::ConvexShape quadIV;
        quadIV.setPointCount(4);
        quadIV.setPoint(0, sf::Vector2f(0, 400));
        quadIV.setPoint(1, sf::Vector2f(300, 400));
        quadIV.setPoint(2, sf::Vector2f(300, 800));
        quadIV.setPoint(3, sf::Vector2f(0, 800));
        quadIV.setFillColor(sf::Color::Yellow);

        std::unique_ptr<World>& world(World::getInstance());
        std::unique_ptr<Game> game = std::make_unique<Game>(600, 800);

        double margin = 20;

        Rect pViewShape{{{wWidthH+margin, wHeightH+margin}, {wWidthH + 100-margin, wHeightH+margin},
                         {wWidthH+100-margin, wHeightH+100-margin}, {wWidthH+margin, wHeightH+100-margin}}};
        Rect pCollShape{{{wWidthH, wHeightH}, {wWidthH + 100, wHeightH},
                         {wWidthH+100, wHeightH+100}, {wWidthH, wHeightH+100}}};
        Player* playerView = new PlayerView(*game, pCollShape, pViewShape);

        Player* player = new Player(pCollShape);
        player->process(2);
        player->process(2);

        sf::Texture texture;
        texture.loadFromFile(PLAYER_TEXTURE_PATH);
        // Create a sprite
        sf::Sprite sprite;
        sprite.setTexture(texture);
        sprite.setScale(.4, 1);
        sprite.setPosition(300, 400);
        sprite.setOrigin(texture.getSize().x/2, texture.getSize().y/2);


        sf::Font font;
        font.loadFromFile("../Resources/Fonts/Qikki-Reg/Qarmic_sans_Abridged.ttf");
        // Create text
        sf::Text text;
        text.setFont(font);
        text.setString("Hello");
        text.setPosition(250, 100);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::Black);




        Rect r1 = {{{100.0, 100.0}, {200.0, 100.0}, {200.0, 200.0}, {100.0, 200.0}}};
        std::pair<double, double> c1 = CollisionObject::determineAbsoluteCenterOfMass(r1);
        CollisionObject* cObj1 = new CollisionObject(r1, true, false);
        cObj1->setOrigin(cObj1->getBoundingWidth()/2, cObj1->getBoundingHeight()/2);

        Rect r2 = {{{150.0, 150.0}, {250.0, 150.0}, {250.0, 250.0}, {150.0, 250.0}}};
        std::pair<double, double> c2 = CollisionObject::determineAbsoluteCenterOfMass(r2);
        CollisionObject* cObj2 = new CollisionObject(r2, true, false);
        //cObj2->setOrigin(cObj2->getBoundingWidth()/2, cObj2->getBoundingHeight()/2);
        //cObj2->move(-150, -150);
        cObj2->setPosition(wWidthH, wHeightH);

        CollisionObject cObj2Stored = *cObj2;

        Rect cameraArea{{{0, 0}, {wWidthH, 0}, {wWidthH, wHeightH}, {0, wHeightH}}};
        Camera* camera = new Camera(wWidthH, wHeightH, cameraArea);

        uint32_t ctr = 0;
        int moveAmount = 5;
        std::pair<double, double> moveDir{0, 0};
        bool requireCollision = true;

        while (window.isOpen()) {
                sf::Event event{};
                while (window.pollEvent(event)) {
                        if (event.type == sf::Event::Closed)
                                window.close();
                        if (event.type == sf::Event::KeyPressed) {
                                double dirX = 0.0;
                                double dirY = 0.0;
                                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
                                    sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                                        dirX += -moveAmount;
                                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
                                    sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                                        dirX += moveAmount;
                                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
                                    sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                                        dirY += -moveAmount;
                                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
                                    sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
                                        dirY += moveAmount;
                                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                                        auto pushback =
                                            cObj2->determinePushback(moveDir, *cObj1, 1.001, requireCollision);

                                        cObj2->move(pushback);
                                        std::cout << "(" << cObj2->getPosition().first << ", "
                                                  << cObj2->getPosition().second << ")" << std::endl;
                                } else {
                                        cObj2->move(dirX, dirY);
                                        playerView->move(dirX, dirY);
                                        moveDir.first += dirX != 0 && dirX != moveDir.first ? dirX : 0;
                                        moveDir.second += dirY != 0 && dirY != moveDir.second ? dirY : 0;
                                }
                                if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
                                        requireCollision = !requireCollision;
                                // Key 'R' stands for resize world coordinates to independent coordinates.
                                if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
                                    camera->project(*cObj2);
                                }                               // Key 'T' stands for transpose from independent coordinates to SFMLcoordinates
                                if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
                                    const double centerY = (wHeight / 2.0) / 2.0;
                                    const double topDistance = centerY - cObj2->getBoundingBox().at(3);
                                    const double bottomDistance = centerY - cObj2->getBoundingBox().at(1);
                                    cObj2->move(0, topDistance + bottomDistance);
                                }
                                // Copy the movable object.
                                if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
                                    cObj2Stored = *cObj2;
                                // Restore the movable object to the previous stored state
                                if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
                                    *cObj2 = cObj2Stored;
                                // Swap the two player objects
                                if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
                                    auto* temp = playerView;
                                    playerView = player;
                                    player = temp;
                                }
                        }
                }

                window.clear();

                sf::ConvexShape rect1;
                rect1.setPointCount(4);
                Rect s1 = cObj1->getCollisionShape();
                for (unsigned int i = 0; i < 4; ++i)
                        rect1.setPoint(i, sf::Vector2f(s1.at(i).first, s1.at(i).second));
                rect1.setFillColor(sf::Color(150, 50, 250));

                sf::CircleShape circle1(20);
                // TODO    the origin is the center of mass of the shape???
                circle1.setOrigin(circle1.getRadius(), circle1.getRadius());
                circle1.setPosition(cObj1->getPosition().first, cObj1->getPosition().second);
                circle1.setFillColor(sf::Color(255, 0, 0));

                sf::ConvexShape rect2;
                rect2.setPointCount(4);
                Rect s2 = cObj2->getCollisionShape();
                for (unsigned int i = 0; i < 4; ++i)
                        rect2.setPoint(i, sf::Vector2f(s2.at(i).first, s2.at(i).second));
                rect2.setFillColor(sf::Color(150, 100, 150));

                sf::CircleShape circle2(20);
                circle2.setOrigin(circle2.getRadius(), circle2.getRadius());
                circle2.setPosition(cObj2->getPosition().first, cObj2->getPosition().second);
                circle2.setFillColor(sf::Color(255, 0, 0));

                sf::CircleShape circle3(20);
                circle3.setOrigin(circle3.getRadius(), circle3.getRadius());
                circle3.setPosition(300.0, 400.0);
                circle3.setFillColor(sf::Color(255, 0, 0));

                // TODO  draw a line with length moveDir and some thickness
                auto lineStart = CollisionObject::determineAbsoluteCenterOfMass(s2);
                sf::Vertex line[] = {sf::Vertex(sf::Vector2f(lineStart.first, lineStart.second)),
                                     sf::Vertex(sf::Vector2f(lineStart.first + moveDir.first * 8.0,
                                                             lineStart.second + moveDir.second * 8.0))};
                sf::CircleShape arrowHead(5);
                arrowHead.setOrigin(arrowHead.getRadius(), arrowHead.getRadius());
                arrowHead.setPosition(lineStart.first + moveDir.first * 8.0, lineStart.second + moveDir.second * 8.0);

                if (cObj1->checkCollision(*cObj2)) {
                        rect1.setOutlineThickness(10);
                        rect1.setOutlineColor(sf::Color(250, 150, 100));
                }


                sf::ConvexShape pvCollRect;
                pvCollRect.setPointCount(4);
                Rect s3 = playerView->getCollisionObject().getCollisionShape();
                for (unsigned int i = 0; i < 4; ++i)
                    pvCollRect.setPoint(i, sf::Vector2f(s3.at(i).first, s3.at(i).second));
                pvCollRect.setFillColor(sf::Color(150, 0, 0));


                sf::ConvexShape pvViewRect;
                pvViewRect.setPointCount(4);
                Rect s4 = playerView->getClipObject().getCollisionShape();
                for (unsigned int i = 0; i < 4; ++i)
                    pvViewRect.setPoint(i, sf::Vector2f(s4.at(i).first, s4.at(i).second));
                pvViewRect.setFillColor(sf::Color(0, 0, 150));


                if (camera->isVisible(playerView->getClipObject())) {
                        pvCollRect.setOutlineThickness(5);
                        pvCollRect.setOutlineColor(sf::Color(0, 150, 0));
                }

                // TODO  add a rotate function to CollisionObject
                // TODO  test the collision tests by moving and rotating the collision shapes.
                //  The coloring of the border is already handled to show the collision

                window.draw(quadI);
                window.draw(quadII);
                window.draw(quadIII);
                window.draw(quadIV);

                shape.rotate(1);
                window.draw(shape);

                window.draw(rect1);
                window.draw(circle1);

                window.draw(rect2);
                window.draw(circle2);

                window.draw(line, 2, sf::Lines);
                window.draw(arrowHead);

                window.draw(circle3);


                window.draw(pvCollRect);
                window.draw(pvViewRect);

                window.draw(sprite);

                window.draw(text);


                window.display();
        }
}

int main()
{
        const std::unique_ptr<Game>& game = std::make_unique<Game>(600, 800);
        game->setFrameRateLimit(60);
        game->start();

        // TODO
        // TODO
        //windowTest();
        // TODO
        // TODO

        return 0;
}
