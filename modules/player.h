#pragma once
#include <string>
#include "SFML/Graphics.hpp"
#include <iostream>

class Player
{
public:
	Player();
	~Player();

	void init(std::string texture_name, sf::Vector2f position);
	void update(float dt, sf::RenderWindow& w);
	sf::Sprite get_sprite();
	void reset();
private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f position;
	sf::Vector2f speed;
	const float break_force = 1.f;
	const float max_speed = 250.f;
	const float rot_speed = 200.f;
};

