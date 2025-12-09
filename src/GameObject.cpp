#include "GameObject.h"
#include <iostream>

GameObject::GameObject()
{
	sprite = std::make_unique<sf::Sprite>();
}

GameObject::~GameObject()
{
}

bool GameObject::initialiseSprite(sf::Texture& texture, std::string filename)
{
	
	
	if (!texture.loadFromFile(filename))
	{
		std::cout << "texture didnt load \n";
		return false;
	}

	sprite->setTexture(texture);
	return true;
}

sf::Sprite& GameObject::getSprite()
{
	return *sprite;
}
