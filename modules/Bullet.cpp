#include "Bullet.h"
#include <iostream>
#define PI 3.14159

sf::Texture Bullet::texture;
const float Bullet::max_speed = 500.f;

void Bullet::load_bullet_texture(std::string texture_name)
{
	if (!texture.loadFromFile(texture_name.c_str()))
	{
		std::cout << "[ERROR] Couldn't load bullet texture!\n";
	}
}

Bullet::Bullet(sf::Sprite player_sprite)
{
	position = player_sprite.getPosition();
	float rot = (player_sprite.getRotation()*PI)/180.f;
	speed.x = sin(rot) * max_speed;
	speed.y = -cos(rot) * max_speed;
	sprite.setTexture(Bullet::texture);
	sprite.setOrigin(Bullet::texture.getSize().x / 2, Bullet::texture.getSize().y / 2);
	sprite.setPosition(this->position);
}

Bullet::~Bullet()
{

}

sf::Sprite Bullet::get_sprite() { return this->sprite; }

void Bullet::update(float dt, sf::RenderWindow& w)
{
	position.x += speed.x * dt;
    position.y += speed.y * dt;
	sprite.setPosition(position);
	sf::FloatRect r;
	r.height = w.getSize().y;
	r.left = 0.f;
	r.width = w.getSize().x;
	r.top = 0.f;
	if (!r.contains(sprite.getPosition()))
	{
		should_remove = true;
	}
}