#include <SFML/Graphics.hpp>
#include <image_sfml.h>
#include <iostream>
#include "Map.h"
#include "Character.h"
#include <Box2D/Box2D.h>
#include <string>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGTH 600
const int PPM = 30;

struct body
{
	b2BodyDef DEF;
	b2PolygonShape SHAPE;
	b2FixtureDef FIX;
	b2Body * BOD;
	sf::RectangleShape RECT;
};

float32 timeStep = 1 / 30.0f;      //the length of time passed to simulate (seconds)
int32 velocityIterations = 8;   //how strongly to correct velocity
int32 positionIterations = 3;   //how strongly to correct position

bool isJumping = false;

int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGTH,64), "SFML works!");
	window.setFramerateLimit(60.f);

	b2Vec2 gravity(0.0f, 10.f);
	b2World* world = new b2World(gravity);

	Map shape_earth(0, WINDOW_HEIGTH - 50, 250, 50);
	Character shape_charact(0, 0, 50, 50);
	shape_charact.SetWorld(*world);


	body ground;
	ground.RECT = sf::RectangleShape(sf::Vector2f(300, 25));//100-50? is size?
	ground.RECT.setOrigin(0, -WINDOW_HEIGTH+25);
	ground.RECT.setFillColor(sf::Color(200, 75, 20, 255));

	ground.DEF.position.Set(0, WINDOW_HEIGTH-25);
	ground.DEF.type = b2_staticBody;

	ground.SHAPE.SetAsBox(280.0f, 25.f);
	
	ground.FIX.shape = &ground.SHAPE;
	ground.FIX.density = .7f;
	ground.FIX.friction = 1.f;

	ground.BOD = (*world).CreateBody(&ground.DEF);
	ground.BOD->CreateFixture(&ground.SHAPE, 1.0f);

	body ground2;
	ground2.RECT = sf::RectangleShape(sf::Vector2f(300, 25));//100-50? is size?
	ground2.RECT.setOrigin(-500, -WINDOW_HEIGTH + 25);
	ground2.RECT.setFillColor(sf::Color(200, 75, 20, 255));

	ground2.DEF.position.Set(700, WINDOW_HEIGTH - 25);
	ground2.DEF.type = b2_staticBody;

	ground2.SHAPE.SetAsBox(200.0f, 25.f);

	ground2.FIX.shape = &ground2.SHAPE;
	ground2.FIX.density = .7f;
	ground2.FIX.friction = 1.f;

	ground2.BOD = (*world).CreateBody(&ground2.DEF);
	ground2.BOD->CreateFixture(&ground2.SHAPE, 1.0f);
	
	//Image image(std::string("data/image.png"));
	while (window.isOpen())
	{
		world->Step(timeStep, velocityIterations, positionIterations);
		shape_charact.update();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				
				if (shape_charact.getBody()->GetPosition().y + 50 >574.985)
				{
					isJumping = false;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
						shape_charact.jump(90, &isJumping);
					}
				

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
					shape_charact.Move(50);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
					shape_charact.Move(-50);
				}
			}
			
		}
		window.clear();
		//image.draw(window);
		
		std::cout << ground.DEF.position.y<< " ";
		std::cout << shape_charact.getBody()->GetPosition().y+50<< "\n ";
		if(ground.DEF.position.y == shape_charact.pos_x){}
		
		window.draw(ground.RECT);
		window.draw(ground2.RECT);
	
		//window.draw(shape_earth.shape_map);
		window.draw(shape_charact.GetShape());
		window.display();
	}
	delete world;
	system("pause");
	return 0;
}