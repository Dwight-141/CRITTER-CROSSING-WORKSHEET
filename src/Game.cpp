
#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
	: window(game_window)
{
	srand(time(NULL));
}

Game::~Game()
{
	delete[] animals;
	delete[] passports;
	delete character;
	delete passport;

}

bool Game::init()
{
	backgroundInit();
	menuInit();
	textureInit();

	character = new sf::Sprite;
	passport = new sf::Sprite;
	stamp = new sf::Sprite;
	return true;
}

void Game::update(float dt)
{
	dragSprite(dragged);
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
		window.draw(*character);
		window.draw(*passport);
		window.draw(accept);
		window.draw(reject);
		window.draw(*stamp);
		break;
	}




}

void Game::mouseClicked(sf::Event event)
{
	//get the click position
	sf::Vector2i click = sf::Mouse::getPosition(window);


}

void Game::mouseButtonPressed(sf::Event event)
{
	if (event.mouseButton.button == sf::Mouse::Left)
	{
		sf::Vector2i click = sf::Mouse::getPosition(window);
		sf::Vector2f clickf = static_cast<sf::Vector2f>(click);

		if (accept.getGlobalBounds().contains(clickf))
		{
			passport_accepted = true;
			std::cout << "accept" << std::endl;
			stamp->setTexture(stamp_texture[0], true);
			stamp->setPosition(passport->getPosition().x, passport->getPosition().y);
		}
		else if (reject.getGlobalBounds().contains(clickf))
		{
			passport_rejected = true;
			std::cout << "reject" << std::endl;
			stamp->setTexture(stamp_texture[1], true);
			stamp->setPosition(passport->getPosition().x, passport->getPosition().y);
		}
		else if (passport->getGlobalBounds().contains(clickf))
		{
			dragged = passport;
		}
		accept.setPosition(0, -200);
		reject.setPosition(0, -200);
	}

	if (event.mouseButton.button == sf::Mouse::Right)
	{
		sf::Vector2i click = sf::Mouse::getPosition(window);
		sf::Vector2f clickf = static_cast<sf::Vector2f>(click);

		if (passport->getGlobalBounds().contains(clickf))
		{
			accept.setPosition(clickf);
			reject.setPosition(clickf.x, clickf.y + 110);
		}
	}
}

void Game::mouseButtonReleased(sf::Event event)
{
	if (event.mouseButton.button == sf::Mouse::Left)
	{
		dragged = nullptr;
	}
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
			newAnimal();
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
	if (!passports[0].loadFromFile("../Data/Images/Critter Crossing Customs/penguin passport.png"))
	{
		std::cout << "font did not load \n";
	}
	if (!animals[1].loadFromFile("../Data/Images/Critter Crossing Customs/elephant.png"))
	{
		std::cout << "font did not load \n";
	}
	if (!passports[1].loadFromFile("../Data/Images/Critter Crossing Customs/elephant passport.png"))
	{
		std::cout << "font did not load \n";
	}
	if (!animals[2].loadFromFile("../Data/Images/Critter Crossing Customs/moose.png"))
	{
		std::cout << "font did not load \n";
	}
	if (!passports[2].loadFromFile("../Data/Images/Critter Crossing Customs/moose passport.png"))
	{
		std::cout << "font did not load \n";
	}
	if (!accept_texture.loadFromFile("../Data/Images/Critter Crossing Customs/accept button.png"))
	{
		std::cout << "font did not load \n";
	}
	if (!reject_texture.loadFromFile("../Data/Images/Critter Crossing Customs/reject button.png"))
	{
		std::cout << "font did not load \n";
	}
	if (!stamp_texture[0].loadFromFile("../Data/Images/Critter Crossing Customs/accept.png"))
	{
		std::cout << "font did not load \n";
	}
	if (!stamp_texture[1].loadFromFile("../Data/Images/Critter Crossing Customs/reject.png"))
	{
		std::cout << "font did not load \n";
	}

	accept.setTexture(accept_texture);
	reject.setTexture(reject_texture);
	accept.setPosition(0, -200);
	reject.setPosition(0, -200);
}

void Game::newAnimal()
{
	passport_accepted = false;
	passport_rejected = false;

	int animal_index = rand() % 3;
	int passport_index = rand() % 3;

	if (animal_index == passport_index)
	{
		should_accept = true;
	}
	else
	{
		should_accept = false;
	}

	character->setTexture(animals[animal_index], true);
	character->setScale(1.8, 1.8);
	character->setPosition(window.getSize().x / 12, window.getSize().y / 12);

	passport->setTexture(passports[passport_index], true);
	passport->setScale(0.6, 0.6);
	passport->setPosition(window.getSize().x / 2, window.getSize().y / 3);

}

void Game::dragSprite(sf::Sprite* sprite)
{
	if (sprite != nullptr)
	{
		sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
		sf::Vector2f mouse_positionf = static_cast<sf::Vector2f>(mouse_position);

		sf::Vector2f drag_position = mouse_positionf - drag_offset;
		sprite->setPosition(drag_position.x, drag_position.y);
		//std::cout << "dragging" << std::endl;
		if (passport_accepted)
		{
			stamp->setTexture(stamp_texture[0], true);
			stamp->setPosition(sprite->getPosition().x, sprite->getPosition().y);
		}
		else if (passport_rejected)
		{
			stamp->setTexture(stamp_texture[1], true);
			stamp->setPosition(sprite->getPosition().x, sprite->getPosition().y);
		}
	}
}


