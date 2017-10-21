#include <SFML/Graphics.hpp>
#include <image_sfml.h>
#include <iostream>
#include "Map.h"
#include "Character.h"
#include <Box2D/Box2D.h>
#include <string>
#include "Box.h"

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

int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGTH,64), "SFML works!");
	window.setFramerateLimit(60.f);

	b2Vec2 gravity(0.0f, 9.8f);
	b2World* world = new b2World(gravity);

	Map shape_earth(0, WINDOW_HEIGTH - 50, 250, 50);
	Character shape_charact(0, 0, 50, 50);
	shape_charact.SetWorld(*world);

	body ground;
	ground.DEF.position.Set(400.0f / PPM, 6000.0f / PPM);
	ground.RECT = sf::RectangleShape(sf::Vector2f(8000, 25));//100-50? is size?
	ground.RECT.setOrigin(4000, 600);
	ground.RECT.setFillColor(sf::Color(200, 75, 20, 255));
	ground.SHAPE.SetAsBox(4000.0f / PPM, 25.0f / PPM);
	ground.BOD = (*world).CreateBody(&ground.DEF);
	ground.FIX.shape = &ground.SHAPE;
	ground.FIX.density = .7f;
	ground.FIX.friction = .9f;
	ground.BOD->CreateFixture(&ground.SHAPE, 1.0f);
	std::cout << 400.0f / PPM <<"  "<< 600.0f / PPM;
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
			}
		}
		window.clear();
		//image.draw(window);
		
		ground.RECT.setPosition(ground.BOD->GetPosition().x*PPM, ground.BOD->GetPosition().y*PPM);
		window.draw(ground.RECT);
	
		//window.draw(shape_earth.shape_map);
		window.draw(shape_charact.GetShape());
		window.display();
	}
	delete world;
	system("pause");
	return 0;
}