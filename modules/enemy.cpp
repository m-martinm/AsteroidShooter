#include "enemy.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

sf::Texture Enemy::texture;

void Enemy::load_enemy_texture(std::string texture_name)
{
	srand(time(NULL));
	if (!texture.loadFromFile(texture_name.c_str()))
	{
		std::cout << "[ERROR] Couldn't load enemy texture!\n";
	}

}

Enemy::Enemy(sf::RenderWindow& window)
{
	float x, y;
	int side = rand() % 4;
    switch (side) {
    case 0:  // top
        x = rand() % window.getSize().x;
        y = -100.f;
        speed.x = rand() % 50;
        speed.y = 200.f;
        break;
    case 1:  // right
        x = window.getSize().x + 100.f;
        y = rand() % window.getSize().y;
        speed.x = -200.f;
        speed.y = rand() % 50;
        break;
    case 2:  // bottom
        x = rand() % window.getSize().x;
        y = window.getSize().y + 100.f;
        speed.x = rand() % 50;
        speed.y = -200.f;
        break;
    case 3:  // left
        x = -100.f;
        y = rand() % window.getSize().y;
        speed.x = 200.f;
        speed.y = rand() % 50;
        break;
    }
    position.x = x;
    position.y = y;
	sprite.setTexture(Enemy::texture);
	sprite.setPosition(this->position);
	sprite.setOrigin(Enemy::texture.getSize().x / 2, Enemy::texture.getSize().y / 2);
}
Enemy::~Enemy()
{

}
sf::Sprite Enemy::get_sprite()
{
    return this->sprite;
}
void Enemy::update(float dt, sf::RenderWindow& w)
{
    position.x += speed.x * dt;
    position.y += speed.y * dt;
    sprite.setPosition(position);
    sf::FloatRect r;
    r.height = w.getSize().y;
    r.left = 0.f;
    r.width = w.getSize().x;
    r.top = 0.f;
    if (r.contains(sprite.getPosition()))
    {
        onscreen = true;
    }
    else
    {
        if (onscreen)
        {
            should_remove = true;
        }
    }
}