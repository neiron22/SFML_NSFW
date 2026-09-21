//Constructor.cpp
#include "Constructor.hpp"

Constructor::Constructor() :

	shape_Counter({ 10, 10 }),
	pointer_hsape({10,40}),
	poligon_Counter({ 220, 15 }, 22),

	vertex_button(ButtonType::add_vertex_Triangles),
	deleted_button(ButtonType::deleted_shape),
	color_indocator(sf::Vector2f{ 530.f,10.f }),
	slider_1({500.f,170.f}),
	silder_counter({600.f , 140.f}),

	buttonPoligonplus({260.f , 80.f} , Type_pressed::Oane_clikc),
	buttonPoligonminus({ 200.f , 80.f }, Type_pressed::Oane_clikc)
	{

	sf::Vector2f point_pos{ 340, 45 };
	float distance = 90.f;

	poligon = 3;

	buttons.push_back(&vertex_button);
	buttons.push_back(&deleted_button);


	for (auto& it : buttons) {
		it->init(point_pos);
		point_pos.x += distance;
	}
}

void Constructor::update(sf::Vector2f mouse_pos, float dt){

	int angle = int(360.f * slider_1.getSilverLevel());

	bool LKM = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	bool PKM = sf::Mouse::isButtonPressed(sf::Mouse::Right);
	
	for (auto& it : buttons) {
		it->update(mouse_pos, LKM , dt);
	}

	model.update(buttons , mouse_pos , LKM , poligon , float(angle));
	
	color_indocator.update(mouse_pos, LKM);

	shape_Counter.updateint(model.get_shape_count());
	poligon_Counter.updatesize_t(poligon);

	
	pointer_hsape.updateint(model.get_zahvat_index());

	buttonPoligonplus.update(mouse_pos, LKM, dt);
	buttonPoligonminus.update(mouse_pos, LKM, dt);

	if (buttonPoligonplus.getClick()) { poligon++; }
	if (buttonPoligonminus.getClick() && poligon > 3) { poligon--; }

	if (model.get_zahvat_index() >= 0) {
		slider_1.update(mouse_pos, LKM, model.get_zahvat_index(), model.get_angle_zahvat_index());
	}
	silder_counter.updateint(angle);
}


void  Constructor::draw(sf::RenderWindow& window) {
	for (auto& it : buttons) {
		it->draw(window);
	}
	model.draw(window);

	shape_Counter.draw(window);
	poligon_Counter.draw(window);

	pointer_hsape.draw(window);


	color_indocator.draw(window);

	buttonPoligonplus.draw(window);
	buttonPoligonminus.draw(window);

	slider_1.draw(window);
	silder_counter.draw(window);
}