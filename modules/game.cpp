#include "Game.h"
#include "enemy.h"
#include <iostream>
#include <cstdlib>

sf::Vector2f Game::viewSize = sf::Vector2f(1024, 768);
sf::VideoMode Game::vm = sf::VideoMode(Game::viewSize.x, Game::viewSize.y);
sf::RenderWindow Game::window;
Player Game::player;
std::vector<Enemy*> Game::enemies;
std::vector<Bullet*> Game::bullets;
sf::Clock Game::bullet_timer;
sf::Font Game::font;
sf::Text Game::score_text;
int Game::score = 0;
sf::Text Game::message_text;
sf::Sprite Game::background;
sf::Texture Game::bg_texture;

void Game::init()
{
	Game::window.create(Game::vm, "AsteroidShooter", sf::Style::Titlebar | sf::Style::Close);
	window.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width / 2 - window.getSize().x/2, 0.f));
	window.setFramerateLimit(120);
	player.init("./assets/spaceship-2.png", sf::Vector2f(window.getSize().x/2.f, window.getSize().y/2.f));
	Enemy::load_enemy_texture("./assets/asteroid-1.png");
	Bullet::load_bullet_texture("./assets/bullet.png");
	if (!font.loadFromFile("./assets/game_over.ttf"))
	{
		std::cout << "[ERROR] Couldn't load font!\n";
	}
	Game::score_text.setFont(font);
	score_text.setPosition(40, 20);
	score_text.setCharacterSize(72);
	score_text.setFillColor(sf::Color::White);
	score_text.setString(std::to_string(score));

	if (!bg_texture.loadFromFile("./assets/bg.png"))
	{
		std::cout << "Couldn't load background!\n";
	}
	background.setTexture(bg_texture);
	Game::start_screen();
}

void Game::main_loop()
{
	sf::Clock clock;
	while (Game::window.isOpen())
	{
		Game::event_handler();
		sf::Time dt = clock.restart();
		Game::update(dt.asSeconds());
		Game::draw();
	}
}

void Game::event_handler()
{
	sf::Event event;


	while (window.pollEvent(event))
	{
		if (event.key.code == sf::Keyboard::Escape || event.type == sf::Event::Closed)
		{
			window.close();
			exit(0);
		}
	}
}

void Game::draw()
{
	Game::window.clear();
	Game::window.draw(background);
	Game::window.draw(player.get_sprite());
	for (Enemy *e : Game::enemies)
	{
		Game::window.draw(e->get_sprite());
	}
	for (Bullet* b : Game::bullets)
	{
		Game::window.draw(b->get_sprite());
	}
	Game::window.draw(score_text);
	Game::window.display();
}
void Game::update(float dt)
{
	// 1% chance every frame to spawn an enemy
	float random_num = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	if (random_num < 0.01) add_enemy();

	Game::player.update(dt, window);
	for (Enemy* e : Game::enemies)
	{
		e->update(dt, window);
		if (e->get_sprite().getGlobalBounds().intersects(Game::player.get_sprite().getGlobalBounds()))
		{
			end_screen();
		}
		if (e->should_remove)
		{
			remove_enemy(e);
		}
	}
	for (Bullet* b : Game::bullets)
	{
		b->update(dt, window);
		if (b->should_remove)
		{
			remove_bullet(b);
		}
		for (Enemy* e : Game::enemies)
		{
			if (e->get_sprite().getGlobalBounds().intersects(b->get_sprite().getGlobalBounds()))
			{
				remove_bullet(b);
				remove_enemy(e);
				score++;
				score_text.setString(std::to_string(score));
			}
		}
	}
}

void Game::add_enemy()
{
	enemies.push_back(new Enemy(Game::window));
}

void Game::remove_enemy(Enemy* e)
{
	std::erase(enemies, e);
}

void Game::add_bullet()
{
	if (bullet_timer.restart() >= sf::seconds(0.5f))
	{
		bullets.push_back(new Bullet(player.get_sprite()));
	}
}

void Game::remove_bullet(Bullet* b)
{
	std::erase(bullets, b);
}

void Game::start_screen()
{
	message_text.setFont(font);
	message_text.setCharacterSize(128);
	message_text.setFillColor(sf::Color::White);
	message_text.setString("Press [ENTER] to start!");
	sf::FloatRect textRect = message_text.getLocalBounds();
	message_text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	message_text.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f));
	while (Game::window.isOpen())
	{
		Game::event_handler();
		window.clear();
		window.draw(message_text);
		window.display();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			score = 0;
			main_loop();
		}
	}
}

void Game::end_screen()
{
	message_text.setFont(font);
	message_text.setCharacterSize(128);
	message_text.setFillColor(sf::Color::White);
	message_text.setString("Press [ENTER] to restart!");
	sf::FloatRect textRect = message_text.getLocalBounds();
	message_text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	message_text.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f));
	while (Game::window.isOpen())
	{
		Game::event_handler();
		window.clear();
		window.draw(message_text);
		window.draw(score_text);
		window.display();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			score = 0;
			score_text.setString(std::to_string(score));
			player.reset();
			enemies.clear();
			bullets.clear();
			main_loop();
		}
	}
}