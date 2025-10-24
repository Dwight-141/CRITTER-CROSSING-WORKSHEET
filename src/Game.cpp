
#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
	: window(game_window)
{
	srand(time(NULL));
}

Game::~Game()
{
	delete [] animals;
	delete [] passports;
	delete character;
	delete passport;

}

bool Game::init()
{
	backgroundInit();
	menuInit();

	character = new sf::Sprite;
	passport = new sf::Sprite;

	//sf::Texture* animals = new sf::Texture[3];
	//sf::Texture* passports = new sf::Texture[3];
	return true;
}

void Game::update(float dt)
{

}

void Game::render()
{
	window.draw(background);
	switch (currentState)
	{
	case MAIN:
		window.draw(menu_text);
		window.draw(play_option);
		window.draw(quit_option);

		break;
	case GAME:
		break;
	}




}

void Game::mouseClicked(sf::Event event)
{
	//get the click position
	sf::Vector2i click = sf::Mouse::getPosition(window);


}

void Game::keyPressed(sf::Event event)
{
	if ((event.key.code == sf::Keyboard::Left) || (event.key.code == sf::Keyboard::Right))
	{
		play_selected = !play_selected;
		if (play_selected)
		{
			play_option.setString("> Play <");
			quit_option.setString("Quit");
		}
		else
		{
			play_option.setString("Play");
			quit_option.setString("> Quit <");
		}
	}
	else if (event.key.code == sf::Keyboard::Enter)
	{
		if (play_selected)
		{
			currentState = GAME;
		}
		else
		{
			window.close();
		}
	}
}

void Game::backgroundInit()
{
	if (!background_texture.loadFromFile("../Data/WhackaMole Worksheet/background.png"))
	{
		std::cout << "background texture didnt load \n";
	}

	background.setTexture(background_texture);
}

void Game::menuInit()
{
	if (!font.loadFromFile("../Data/Fonts/OpenSans-Bold.ttf"))
	{
		std::cout << "font did not load \n";
	}

	menu_text.setString("       Critter Crossing\nPlease Select An Option");
	menu_text.setFont(font);
	menu_text.setCharacterSize(50);
	menu_text.setFillColor(sf::Color(0, 0, 0, 255));
	menu_text.setPosition(
		window.getSize().x / 2 - menu_text.getGlobalBounds().width / 2, 0);

	play_option.setString("Play");
	play_option.setFont(font);
	play_option.setCharacterSize(50);
	play_option.setFillColor(sf::Color(0, 0, 0, 255));
	play_option.setPosition(100, 300);

	quit_option.setString("Quit");
	quit_option.setFont(font);
	quit_option.setCharacterSize(50);
	quit_option.setFillColor(sf::Color(0, 0, 0, 255));
	quit_option.setPosition(800, 300);
}

void Game::textureInit()
{
	if (!animals[0].loadFromFile("../Data/Images/Critter Crossing Customs/penguin.png"))
	{
		std::cout << "font did not load \n";
	}
	if (!animals[0].loadFromFile("../Data/Images/Critter Crossing Customs/penguin passport.png"))
	{
		std::cout << "font did not load \n";
	}
	if (!animals[1].loadFromFile("../Data/Images/Critter Crossing Customs/elephant.png"))
	{
		std::cout << "font did not load \n";
	}
	if (!animals[1].loadFromFile("../Data/Images/Critter Crossing Customs/elephant passport.png"))
	{
		std::cout << "font did not load \n";
	}
	if (!animals[2].loadFromFile("../Data/Images/Critter Crossing Customs/moose.png"))
	{
		std::cout << "font did not load \n";
	}
	if (!animals[2].loadFromFile("../Data/Images/Critter Crossing Customs/moose passport.png"))
	{
		std::cout << "font did not load \n";
	}

}


