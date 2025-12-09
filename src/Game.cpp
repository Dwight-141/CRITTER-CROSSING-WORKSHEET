
#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
	: window(game_window)
{
	srand(time(NULL));
	animals.resize(3);
	passports.resize(3);
	stamp_texture.resize(2);
}

Game::~Game()
{

}

bool Game::init()
{
	backgroundInit();
	menuInit();
	textureInit();
	newAnimal();

	return true;
}

void Game::update(float dt)
{
	if (currentState == GAME)
	{
		dragSprite(dragged);
		returnPassport();
	}

}

void Game::render()
{
	window.draw(background.getSprite());
	switch (currentState)
	{
	case MAIN:
		window.draw(menu_text);
		window.draw(play_option);
		window.draw(quit_option);

		break;
	case GAME:
		window.draw(character.getSprite());
		window.draw(passport.getSprite());
		window.draw(accept.getSprite());
		window.draw(reject.getSprite());
		window.draw(stamp.getSprite());
		window.draw(score_text);
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

		if (accept.getSprite().getGlobalBounds().contains(clickf))
		{
			passport_accepted = true;
			std::cout << "accept" << std::endl;
			stamp.initialiseSprite(stamp_texture[0], "../Data/Images/Critter Crossing Customs/accept.png");
			stamp.getSprite().setPosition(passport.getSprite().getPosition().x, passport.getSprite().getPosition().y);
			stamped = true;
		}
		else if (reject.getSprite().getGlobalBounds().contains(clickf))
		{
			passport_rejected = true;
			std::cout << "reject" << std::endl;
			stamp.initialiseSprite(stamp_texture[1], "../Data/Images/Critter Crossing Customs/reject.png");
			stamp.getSprite().setPosition(passport.getSprite().getPosition().x, passport.getSprite().getPosition().y);
			stamped = true;
		}
		else if (passport.getSprite().getGlobalBounds().contains(clickf))
		{
			dragged = &passport;
		}
		accept.getSprite().setPosition(0, -200);
		reject.getSprite().setPosition(0, -200);
	}

	if (event.mouseButton.button == sf::Mouse::Right)
	{
		sf::Vector2i click = sf::Mouse::getPosition(window);
		sf::Vector2f clickf = static_cast<sf::Vector2f>(click);

		if (passport.getSprite().getGlobalBounds().contains(clickf))
		{
			accept.getSprite().setPosition(clickf);
			reject.getSprite().setPosition(clickf.x, clickf.y + 110);
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
	background.initialiseSprite(background_texture, "../Data/WhackaMole Worksheet/background.png");
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

	score_text.setString(std::to_string(score));
	score_text.setFont(font);
	score_text.setCharacterSize(50);
	score_text.setFillColor(sf::Color(0, 0, 0, 255));
	score_text.setPosition(window.getSize().x - score_text.getGlobalBounds().width, 0);

}

void Game::textureInit()
{
	accept.initialiseSprite(accept_texture, "../Data/Images/Critter Crossing Customs/accept button.png");
	reject.initialiseSprite(reject_texture, "../Data/Images/Critter Crossing Customs/reject button.png");


	accept.getSprite().setTexture(accept_texture);
	reject.getSprite().setTexture(reject_texture);
	accept.getSprite().setPosition(0, -200);
	reject.getSprite().setPosition(0, -200);
}

void Game::newAnimal()
{
	passport_accepted = false;
	passport_rejected = false;
	stamped = false;

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

	switch (animal_index)
	{
	case 0:
		character.initialiseSprite(animals[0], "../Data/Images/Critter Crossing Customs/penguin.png");
		break;
	case 1:
		character.initialiseSprite(animals[1], "../Data/Images/Critter Crossing Customs/elephant.png");
		break;
	case 2:
		character.initialiseSprite(animals[2], "../Data/Images/Critter Crossing Customs/moose.png");
		break;
	}

	switch (passport_index)
	{
	case 0:
		passport.initialiseSprite(passports[0], "../Data/Images/Critter Crossing Customs/penguin passport.png");
		break;
	case 1:
		passport.initialiseSprite(passports[1], "../Data/Images/Critter Crossing Customs/elephant passport.png");
		break;
	case 2:
		passport.initialiseSprite(passports[2], "../Data/Images/Critter Crossing Customs/moose passport.png");
		break;
	}

	character.getSprite().setScale(1.8, 1.8);
	character.getSprite().setPosition(window.getSize().x / 12, window.getSize().y / 12);

	passport.getSprite().setScale(0.6, 0.6);
	passport.getSprite().setPosition(window.getSize().x / 2, window.getSize().y / 3);

	stamp.getSprite().setPosition(0, -200);

}

void Game::dragSprite(GameObject* sprite)
{
	if (sprite != nullptr)
	{
		sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
		sf::Vector2f mouse_positionf = static_cast<sf::Vector2f>(mouse_position);

		sf::Vector2f drag_position = mouse_positionf - drag_offset;
		sprite->getSprite().setPosition(drag_position.x, drag_position.y);
		if (passport_accepted)
		{
			stamp.getSprite().setPosition(sprite->getSprite().getPosition().x, sprite->getSprite().getPosition().y);
		}
		else if (passport_rejected)
		{
			stamp.getSprite().setPosition(sprite->getSprite().getPosition().x, sprite->getSprite().getPosition().y);
		}
	}
}

void Game::returnPassport()
{
	if (dragged == nullptr && stamped)
	{
		if ((passport.getSprite().getPosition().x < window.getSize().x / 2) && (passport.getSprite().getPosition().y < window.getSize().y / 2))
		{
			if (should_accept == true && passport_accepted == true)
			{
				score++;
				score_text.setString(std::to_string(score));
				newAnimal();
			}
			else if (should_accept == false && passport_rejected == true)
			{
				score++;
				score_text.setString(std::to_string(score));
				newAnimal();
			}
			else
			{
				score--;
				score_text.setString(std::to_string(score));
				newAnimal();
			}
			score_text.setPosition(window.getSize().x - score_text.getGlobalBounds().width * 5, 0);
		}
	}
}


