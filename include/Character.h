#pragma once
#include "Shapes.h"
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

class Character : public Rectangle
{
private:
	b2Body * m_body;
	b2BodyDef m_bodyDef;
	b2PolygonShape m_bodyShape;
	b2FixtureDef m_bodyFix;
	sf::RectangleShape sh_character;
public:
	//Character(b2World & world);
	Character(double _pos_x, double _pos_y, double _width, double _height);
	void SetWorld(b2World & world);
	//b2Body* GetBody(); // Get Box2d body
	sf::Shape & GetShape();
	void update(); // Get SFML shape
	void ResetPosition(b2World & world); //this one is me too BHN resets shapes
	//void jump(float angle);
	//void setN(int newN) { n = newN; }  //reset n
	//int getN() { return n; }

	void setPosition(double _pos_x, double _pos_y);
	~Character();
};
