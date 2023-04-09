#pragma once
#include "SFML/Graphics.hpp"
#include "player.h"
#include "enemy.h"
#include <vector>
#include "Bullet.h"

class Game
{
public:
	static sf::Vector2f viewSize;
	static sf::VideoMode vm;
	static sf::RenderWindow window;
	static void init();
	static void add_bullet();

private:
	static sf::Sprite background;
	static sf::Texture bg_texture;

	static Player player;
	static std::vector<Enemy*> enemies;
	static std::vector<Bullet*> bullets;

	static void start_screen();
	static void end_screen();
	static sf::Text message_text;

	static void main_loop();
	static void event_handler();
	static void update(float dt);
	static void draw();

	static void add_enemy();
	static void remove_enemy(Enemy* e);
	static void remove_bullet(Bullet* b);

	static sf::Clock bullet_timer;
	static sf::Font font;
	static sf::Text score_text;
	static int score;
};

