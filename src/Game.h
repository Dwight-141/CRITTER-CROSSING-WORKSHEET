
#ifndef PLATFORMER_GAME_H
#define PLATFORMER_GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "GameObject.h"

class Game
{
public:
	Game(sf::RenderWindow& window);
	~Game();
	bool init();
	void update(float dt);
	void render();
	void mouseClicked(sf::Event event);
	void mouseButtonPressed(sf::Event event);
	void mouseButtonReleased(sf::Event event);
	void keyPressed(sf::Event event);
	void backgroundInit();
	void menuInit();
	void textureInit();
	void newAnimal();
	void dragSprite(GameObject* sprite);
	void returnPassport();

	enum MenuState { MAIN, GAME, LOSE};

private:
	// background
	sf::RenderWindow& window;
	GameObject background;
	sf::Texture background_texture;

	//menu
	sf::Font font;
	sf::Text menu_text;
	sf::Text play_option;
	sf::Text quit_option;
	sf::Text lose_text;
	MenuState currentState = MAIN;
	bool play_selected = false;

	//character
	GameObject character;
	GameObject passport;

	std::vector<sf::Texture> animals;
	std::vector<sf::Texture> passports;

	//stamps
	bool passport_accepted;
	bool passport_rejected;
	bool should_accept;
	bool stamped = false;
	
	GameObject accept;
	GameObject reject;
	GameObject stamp;

	sf::Texture accept_texture;
	sf::Texture reject_texture;
	std::vector<sf::Texture> stamp_texture;


	//dragging
	GameObject* dragged = nullptr;
	sf::Vector2f drag_offset;

	//score
	int score = 0;
	sf::Text score_text;

};

#endif // PLATFORMER_GAME_H
