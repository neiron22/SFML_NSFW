//button_shape.hpp
#pragma once
#include<SFML/Graphics.hpp>

enum class Type_pressed {Oane_clikc , On_off , Prpessed};


class button_shape{
	Type_pressed type;
	sf::RectangleShape rect;
	sf::Vector2f pos;
	bool activate_diactivate, flag;


public:

	button_shape(sf::Vector2f pos, Type_pressed type = Type_pressed::On_off);

	void update(sf::Vector2f mouse_pos, bool LKM, float dt);

	void draw(sf::RenderWindow& window);

	bool getClick() { return activate_diactivate; }
};

