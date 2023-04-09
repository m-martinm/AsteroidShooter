#include "player.h"
#include <iostream>
#include <cmath>
#include "Bullet.h"
#include "game.h"

Player::Player() {}
Player::~Player() {}

void Player::init(std::string texture_name, sf::Vector2f position)
{
	this->position = position;
	speed = sf::Vector2f(0, 0);

	if (!texture.loadFromFile(texture_name.c_str()))
	{
		std::cout << "[ERROR] Couldn't load player's texture!\n";
	}

	sprite.setTexture(texture);
	sprite.setPosition(this->position);
	sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);

}

void Player::update(float dt, sf::RenderWindow& w)
{
	if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
		sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			speed.y -= max_speed;
			if (speed.y <= -max_speed) speed.y = -max_speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			speed.y += max_speed;
			if (speed.y >= max_speed) speed.y = max_speed;
		}
	}
	if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
		sf::Keyboard::isKeyPressed(sf::Keyboard::Right)))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			speed.x += max_speed;
			if (speed.x >= max_speed) speed.x = max_speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			speed.x -= max_speed;
			if (speed.x <= -max_speed) speed.x = -max_speed;
		}
	}if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
		sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			sprite.rotate(rot_speed * dt);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			sprite.rotate(-rot_speed * dt);
		}
	}
	if (std::fabs(speed.x - break_force) >= break_force)
	{
		if (speed.x > 0) speed.x -= break_force;
		else speed.x += break_force;
	}
	else {
		speed.x = 0.f;
	}
	if (std::fabs(speed.y - break_force) >= break_force)
	{
		if (speed.y > 0) speed.y -= break_force;
		else speed.y += break_force;
	}
	else
	{
		speed.y = 0.f;
	}
	position.x += speed.x * dt;
	position.y += speed.y * dt;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		Game::add_bullet();
	}

	// collision
	sf::FloatRect r = sprite.getGlobalBounds();
	float offset = 10.f;
	if (r.left + r.width + offset >= w.getSize().x)
	{
		position.x = w.getSize().x - r.width;
		speed.x = -speed.x;
	}
	if (r.left - offset <= 0)
	{
		position.x = r.width;
		speed.x = -speed.x;
	}
	if (r.top + r.height + offset >= w.getSize().y)
	{
		position.y = w.getSize().y - r.height;
		speed.y = -speed.y;
	}
	if (r.top - offset <= 0)
	{
		position.y = r.height;
		speed.y = -speed.y;
	}
	sprite.setPosition(position);
}

sf::Sprite Player::get_sprite()
{
	return sprite;
}

void Player::reset()
{
	position.x = Game::window.getSize().x / 2;
	position.y = Game::window.getSize().y / 2;
	sprite.setRotation(0.f);
	speed.x = 0;
	speed.y = 0;
	sprite.setPosition(position);
}
