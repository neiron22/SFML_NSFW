//Button.hpp
#pragma once

#include<SFML\Graphics.hpp>

#include"Type.hpp"
class Button{
	ButtonType buttontype;
	std::unique_ptr<sf::Drawable> shape;
	sf::RectangleShape rect;
	sf::Vector2f pos;
	sf::Color color;

	bool clickedThisFrame, isPressed , wasPressedLastFrame;
	float time , timer;

public:

	Button(ButtonType type);

	void init(sf::Vector2f pos, sf::Color color = { 100,100,100 });

	void update(sf::Vector2f mouse_pos, bool LKM, float dt);

	void draw(sf::RenderWindow & window);

	bool getClick() { return clickedThisFrame; }
	ButtonType getType() { return buttontype; }
};

