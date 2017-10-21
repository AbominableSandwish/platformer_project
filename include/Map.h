#ifndef MAP_H
#define MAP_H
#include "Shapes.h"
#include "Character.h"


class Map : public Rectangle
{
public:
	Map(double _pos_x, double _pos_y, double _width, double _height);
	~Map();


	//attributs
	sf::RectangleShape shape_map;
	bool CheckCollind(Character);
};
#endif