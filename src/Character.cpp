#include "Character.h"

const int PPM = 30;


Character::Character(double _pos_x, double _pos_y, double _width, double _height) : Rectangle(_pos_x, _pos_y, _width, _height)
{
	sh_character = sf::RectangleShape(sf::Vector2f((float)this->width, (float)this->height));//(0,0,10,10,sf::Color(255,255,255));
	sh_character.setOrigin(0, 0);
	sh_character.setFillColor(sf::Color::Blue);

	m_bodyDef.position.Set(0,0);
	m_bodyDef.type = b2_dynamicBody;

	m_bodyShape.SetAsBox(25.0f, 25.0f);

	m_bodyFix.shape = &m_bodyShape;
	m_bodyFix.density = 0.1f;
	m_bodyFix.friction = 0.1f;
}

void Character::update() {
	sh_character.setRotation(m_body->GetAngle());
	sh_character.setPosition(m_body->GetPosition().x, m_body->GetPosition().y);
}


void Character::SetWorld(b2World & world) {
	m_body = world.CreateBody(&m_bodyDef);
	m_body->CreateFixture(&m_bodyFix);
}

sf::Shape & Character::GetShape() {
	return sh_character;
}

void Character::ResetPosition(b2World & world) {
	//destroy stuff (memory management, otherwise they build up)
	m_body->DestroyFixture(m_body->GetFixtureList());
	world.DestroyBody(m_body);
	//m_shape.SetOrigin(5,5);
	m_bodyDef.position.Set(10.0f, 10.0f);
	m_bodyDef.angularVelocity = 0;
	//m_bodyDef.angle = 270;
	m_bodyDef.linearVelocity.Set(0, 60);
	//reset fixture and body
	SetWorld(world);
	//reset shape
	update();
}

Character::~Character()
{
}

void Character::setPosition(double _pos_x, double _pos_y)
{
	this->pos_x = _pos_x;
	this->pos_y = _pos_y;
	this->sh_character.setPosition(sf::Vector2f((float)this->pos_x, (float)this->pos_y));
}
