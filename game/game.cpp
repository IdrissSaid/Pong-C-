#include "game.h"

void Game::initVariable()
{
	this->window = nullptr;
	player.setPosition(0, (WIN_HEIGHT / 2) - (player.getSize().y / 2));
	player2.setPosition(WIN_WITDH - player2.getSize().x, (WIN_HEIGHT / 2) - (player2.getSize().y / 2));
	ball.setPosition((WIN_WITDH / 2) - (ball.getRadius() / 2), (WIN_HEIGHT / 2) - (ball.getRadius() / 2));
	res[0] = 0;
	res[1] = 0;
	text.update("0 | 0", Vector2f((WIN_WITDH / 2.f) - (text.getSize() + 6), 0));
}

void Game::initWindow()
{
	this->videoMode.width = WIN_WITDH;
	this->videoMode.height = WIN_HEIGHT;
	this->window = new RenderWindow(this->videoMode, "Pong SFML C++");
	this->window->setVerticalSyncEnabled(true);
}

Game::Game()
{
	this->initVariable();
	this->initWindow();
}

Game::~Game()
{
	delete this->window;
}

bool Game::isRunning() const
{
	return this->window->isOpen();
}

void Game::update()
{
	while (window->pollEvent(event))
		input.InputHandler(event, *window, &statement);
	if (!statement) {
		menu.update(this->window, &statement);
		return;
	}
	int tmp[2];
	tmp[0] = res[0];
	tmp[1] = res[1];
	string str;

	player.update(this->window, input.GetButton(), 1);
	player2.update(this->window, input.GetButton(), 2);
	ball.update(this->window, &player, &player2, res);
	if (tmp[0] != res[0] || tmp[1] != res[1]) {
		str = to_string(res[0]) + " | " + to_string(res[1]);
		text.update(str, Vector2f((WIN_WITDH / 2.f) - text.getSize(), 0));
	}
}

void Game::render()
{
	window->clear();
	if (!statement) {
		menu.render(window);
	} else if (statement == 1) {
		player.render(window);
		player2.render(window);
		ball.render(window);
		text.render(window);
	}
	window->display();
}