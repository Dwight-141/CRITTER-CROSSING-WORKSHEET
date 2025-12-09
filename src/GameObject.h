
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SFML/Graphics.hpp>

class GameObject
{
public:
	GameObject();
	~GameObject();
	bool initialiseSprite(sf::Texture& texture, std::string filename);
	sf::Sprite& getSprite();

private:
	std::unique_ptr<sf::Sprite> sprite;
};

#endif // GAMEOBJECT_H