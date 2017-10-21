#include <SFML/Graphics.hpp>
#include "Shapes.h"
#include <cmath>


//Shapes
Shapes::Shapes(double _pos_x, double _pos_y) : pos_x(_pos_x), pos_y(_pos_y) {}

Shapes::~Shapes() {}

//Rectangle
Rectangle::Rectangle(double _pos_x, double _pos_y, double _width, double _height) : Shapes(_pos_x, _pos_y), width(_width), height(_height) {
	this->sh_rectangle.setPosition((float)this->pos_x, (float)this->pos_y);
	this->sh_rectangle.setSize(sf::Vector2f((float)this->width, (float)this->height));
	this->sh_rectangle.setFillColor(sf::Color::Blue);
}

bool Rectangle::isColliding(Shapes* _shape) {
	if (dynamic_cast<Rectangle*>(_shape)) {
		return Rectangle::isColliding(dynamic_cast<Rectangle*>(_shape));
	}
	else {
		if (dynamic_cast<Circle*>(_shape)) {
			return Rectangle::isColliding(dynamic_cast<Circle*>(_shape));
		}
		else
		{
			return false;
		}
	}
}

bool Rectangle::isColliding(Rectangle* _rectangle) {
	if (this->pos_x < _rectangle->pos_x + _rectangle->width &&
		this->pos_x + this->width > _rectangle->pos_x &&
		this->pos_y < _rectangle->pos_y + _rectangle->height &&
		this->height + this->pos_y > _rectangle->pos_x) {
		// collision détectée !
		return true;
	}
	return false;
}

bool Rectangle::isColliding(Circle* _circle) {
	double rectCenterX = this->pos_x + 50;
	double rectCenterY = this->pos_y + 50;

	double rectX = rectCenterX - this->width / 2;
	double rectY = rectCenterY - this->height / 2;

	double rectReferenceX = rectX;
	double rectReferenceY = rectY;

	// Rotate circle's center point back
	double unrotatedCircleX = cos(this->sh_rectangle.getRotation()) * ((_circle->pos_x + 50) - rectCenterX) - sin(this->sh_rectangle.getRotation()) * ((_circle->pos_y + 50) - (this->pos_y + 50)) + (this->pos_x + 50);
	double unrotatedCircleY = sin(this->sh_rectangle.getRotation()) * ((_circle->pos_x + 50) - rectCenterX) + cos(this->sh_rectangle.getRotation()) * ((_circle->pos_y + 50) - (this->pos_y + 50)) + (this->pos_y + 50);

	// Closest point in the rectangle to the center of circle rotated backwards(unrotated)
	double closestX, closestY;

	// Find the unrotated closest x point from center of unrotated circle
	if (unrotatedCircleX < rectReferenceX) {
		closestX = rectReferenceX;
	}
	else if (unrotatedCircleX > rectReferenceX + this->width) {
		closestX = rectReferenceX + this->width;
	}
	else {
		closestX = unrotatedCircleX;
	}

	// Find the unrotated closest y point from center of unrotated circle
	if (unrotatedCircleY < rectReferenceY) {
		closestY = rectReferenceY;
	}
	else if (unrotatedCircleY > rectReferenceY + this->height) {
		closestY = rectReferenceY + this->height;
	}
	else {
		closestY = unrotatedCircleY;
	}

	// Determine collision
	bool collision = false;
	double dX = abs(unrotatedCircleX - closestX);
	double dY = abs(unrotatedCircleY - closestY);

	double distance = (sqrt((dX * dX) + (dY * dY)) - 50);

	if (distance < _circle->r) {
		collision = true;
	}
	else {
		collision = false;
	}

	return collision;
}


//Circle
Circle::Circle(double _pos_x, double _pos_y, double _r, sf::CircleShape _sh_circle) :Shapes(_pos_x, _pos_y), r(_r) {
	_sh_circle.setPosition((float)this->pos_x, (float)this->pos_y);
	// change la couleur de la forme pour du vert
	_sh_circle.setFillColor(sf::Color(100, 250, 50));
	this->sh_circle = _sh_circle;
}

void Circle::setPosition(double _pos_x, double _pos_y) {
	this->pos_x = _pos_x;
	this->pos_y = _pos_y;
	this->sh_circle.setPosition((float)this->pos_x, (float)this->pos_y);
}

bool Circle::isColliding(Shapes* _shape) {
	if (dynamic_cast<Rectangle*>(_shape)) {
		return Circle::isColliding(dynamic_cast<Rectangle*>(_shape));
	}
	else {
		if (dynamic_cast<Circle*>(_shape)) {
			return Circle::isColliding(dynamic_cast<Circle*>(_shape));
		}
		else {
			return false;
		}
	}

}

bool Circle::isColliding(Circle* _circle) {
	double dx = this->pos_x - _circle->pos_x;
	double dy = this->pos_y - _circle->pos_y;
	double distance = std::sqrt(dx * dx + dy * dy);

	if (distance < this->r + _circle->r) {
		return true;
	}
	else {
		return false;
	}
}

bool Circle::isColliding(Rectangle* _rectangle) {
	double distX = std::abs(this->pos_x - _rectangle->pos_x - _rectangle->width / 2);
	double distY = std::abs(this->pos_y - _rectangle->pos_y - _rectangle->height / 2);

	if (distX > (_rectangle->width / 2 + this->r)) { return false; }
	if (distY > (_rectangle->height / 2 + this->r)) { return false; }

	if (distX <= (_rectangle->width / 2)) { return true; }
	if (distY <= (_rectangle->height / 2)) { return true; }
}

