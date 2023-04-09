#pragma once
#include "SFML/Graphics.hpp"

class Enemy
{
	static sf::Texture texture;

public:
	Enemy(sf::RenderWindow& window);
	~Enemy();
	sf::Sprite get_sprite();
	void update(float dt, sf::RenderWindow& w);
	static void load_enemy_texture(std::string texture_name);
	bool should_remove = false;

private:
	sf::Sprite sprite;
	sf::Vector2f position;
	sf::Vector2f speed;
	bool onscreen = false;
};

