#ifndef GROUND_H
#define GROUND_H

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

struct body
{
	b2BodyDef DEF;
	b2PolygonShape SHAPE;
	b2FixtureDef FIX;
	b2Body * BOD;
	sf::RectangleShape RECT;
};
class ground
{
public:
	ground();
	~ground();
};
#endif