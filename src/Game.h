
#ifndef PLATFORMER_GAME_H
#define PLATFORMER_GAME_H

#include <SFML/Graphics.hpp>

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
	void dragSprite(sf::Sprite* sprite);

	enum MenuState { MAIN, GAME };

private:
	// background
	sf::RenderWindow& window;
	sf::Sprite background;
	sf::Texture background_texture;

	//menu
	sf::Font font;
	sf::Text menu_text;
	sf::Text play_option;
	sf::Text quit_option;
	MenuState currentState = MAIN;
	bool play_selected = false;

	//character
	sf::Sprite* character;
	sf::Sprite* passport;

	sf::Texture* animals = new sf::Texture[3];
	sf::Texture* passports = new sf::Texture[3];

	bool passport_accepted;
	bool passport_rejected;
	bool should_accept;

	//functionality
	sf::Sprite* dragged = nullptr;
	sf::Vector2f drag_offset;

};

#endif // PLATFORMER_GAME_H
