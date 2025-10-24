
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
  void keyPressed(sf::Event event);
  void backgroundInit();
  void menuInit();
  void textureInit();
  
  enum MenuState { MAIN, GAME };

 private:
  sf::RenderWindow& window;
  sf::Sprite background;
  sf::Texture background_texture;

  sf::Font font;
  sf::Text menu_text;
  sf::Text play_option;
  sf::Text quit_option;
  MenuState currentState = MAIN;
  bool play_selected = false;

  sf::Sprite* character;
  sf::Sprite* passport;

  sf::Texture* animals = new sf::Texture[3];
  sf::Texture* passports = new sf::Texture[3];

};

#endif // PLATFORMER_GAME_H
