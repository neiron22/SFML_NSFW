//button_shape.cpp
#include "button_shape.hpp"

button_shape::button_shape(sf::Vector2f pos, Type_pressed type) : pos(pos),type(type){
	activate_diactivate = false; flag = false;

	float size = 40.f , out_size = 5.f;
	
	rect.setSize({size,size});
	rect.setOrigin(sf::Vector2f{ size,size } * 0.5f);

	rect.setOutlineThickness(out_size);

	rect.setFillColor({0,0,0,0});
	rect.setOutlineColor({70,70,70});

	rect.setPosition(pos);
}

void button_shape::update(sf::Vector2f mouse_pos, bool LKM, float dt) {
	sf::Vector2f delta = pos - mouse_pos;
	sf::Vector2f distance = rect.getSize() * 0.5f;

	bool isHovered = (std::fabs(delta.x) < distance.x && std::fabs(delta.y) < distance.y);

	switch (type)
	{
	case Type_pressed::Oane_clikc:

		if (isHovered && LKM && !flag) {
			activate_diactivate = true;
			flag = LKM;
		}
		else { activate_diactivate = false; }
		if (!LKM) { flag = false; }

		break;
	case Type_pressed::On_off:

		if (isHovered && LKM && !flag) {
			activate_diactivate = !activate_diactivate;
			flag = LKM;
		}
		if (!LKM) { flag = false; }

		break;
	case Type_pressed::Prpessed:

		if (isHovered && LKM && !flag) {
			activate_diactivate = true;}
		else{ activate_diactivate = false; }
		break;
	default:
		break;
	}

	


	if (activate_diactivate) {
		rect.setFillColor(sf::Color::White);
	}
	else { rect.setFillColor({ 0,0,0,0 }); }
}


void button_shape::draw(sf::RenderWindow& window) {
	window.draw(rect);
}