#pragma once
#include "SFML/Graphics.hpp"

class Bullet
{
	static sf::Texture texture;

public:
	Bullet(sf::Sprite player_sprite);
	~Bullet();
	sf::Sprite get_sprite();
	void update(float dt, sf::RenderWindow& w);
	static void load_bullet_texture(std::string texture_name);
	bool should_remove = false;

private:
	sf::Sprite sprite;
	sf::Vector2f position;
	sf::Vector2f speed;
	static const float max_speed;
};

