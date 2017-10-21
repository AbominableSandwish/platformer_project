#include "Map.h"



Map::Map(double _pos_x, double _pos_y, double _width, double _height) : Rectangle(_pos_x, _pos_y, _width, _height)
{
	this->shape_map.setPosition(sf::Vector2f((float)this->pos_x, (float)this->pos_y));

	this->shape_map.setSize(sf::Vector2f((float)this->width, (float)this->height));

	this->shape_map.setFillColor(sf::Color::Red);
}

bool Map::CheckCollind(Character _shape_charact) {
	return this->isColliding(&_shape_charact);
}


Map::~Map()
{
}
