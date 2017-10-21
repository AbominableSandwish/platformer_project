#ifndef SHAPES_H
#define SHAPES_H
#include <iostream>
#include <SFML/Graphics.hpp>

#define HEIGHT_WINDOW 500
#define WIDTH_WINDOW 500

class Circle;

class Shapes
{
public:
	Shapes(double _pos_x, double _pos_y);
	~Shapes();

	virtual bool isColliding(Shapes*) = 0;

	//attributs
	double pos_x, pos_y;

};

class Rectangle : public Shapes
{
public:
	Rectangle(double _pos_x, double _pos_y, double _width, double _height);

	bool isColliding(Shapes*);
	bool isColliding(Circle*);
	bool isColliding(Rectangle*);

	//attributs
	sf::RectangleShape sh_rectangle;
	double width, height;
};

class Circle : public Shapes
{
public:
	Circle(double _pos_x, double _pos_y, double _r, sf::CircleShape _sh_circle);

	bool isColliding(Shapes*);
	bool isColliding(Circle*);
	bool isColliding(Rectangle*);
	void setPosition(double _pos_x, double _pos_y);
	//attributs
	double r;
	sf::CircleShape sh_circle;
};
#endif