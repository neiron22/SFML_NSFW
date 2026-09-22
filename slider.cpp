//Color_indikator.cpp
#include "slider.hpp"

//--------------


Color_indikator::Color_indikator(sf::Vector2f vec) :
	colorscale(vec) , color(sf::Color::White){ point = vec.x;
color_rect.setPosition(vec + sf::Vector2f{ 280.f,0.f });
float size = 50.f;
color_rect.setSize({size,size});
color_rect.setFillColor(sf::Color::Black);
pointer_shape = -1;
zahvat_rect = nullptr;
}



bool mouse_click(sf::Vector2f pos , sf::Vector2f mouse_pos , sf::Vector2f size , bool LKM) {
	sf::Vector2f delta = (pos - mouse_pos);
	if (std::fabs(delta.x) < size.x && std::fabs(delta.y) < size.y && LKM) { return true; }
	return false;}

void Color_indikator::update(sf::Vector2f mouse_pos, bool LKM, int pointer_shape, sf::Color color_shape) {
	sf::Vector2f r_pos = colorscale.r.getPosition();
	sf::Vector2f g_pos = colorscale.g.getPosition();
	sf::Vector2f b_pos = colorscale.b.getPosition();

		color = { static_cast<sf::Uint8>(r_pos.x - point) ,
					static_cast<sf::Uint8>(g_pos.x - point) ,
					static_cast<sf::Uint8>(b_pos.x - point) };

	color_rect.setFillColor(color);

	if (this->pointer_shape != pointer_shape) {
	colorscale.r.setPosition(sf::Vector2f{point+float(color_shape.r) , colorscale.r.getPosition().y }); 
	colorscale.g.setPosition(sf::Vector2f{ point + float(color_shape.g) , colorscale.g.getPosition().y });
	colorscale.b.setPosition(sf::Vector2f{ point + float(color_shape.b) , colorscale.b.getPosition().y });

	
	}

	this->pointer_shape = pointer_shape;

	if(zahvat_rect != nullptr && LKM){
		zahvat_rect->setPosition({ std::clamp(mouse_pos.x , point,point + 255) ,zahvat_rect->getPosition().y });
		return;
	}
	else {
		zahvat_rect = nullptr;
	}

	if (mouse_click(r_pos, mouse_pos, colorscale.r.getSize(), LKM)) {
		zahvat_rect = &colorscale.r;
	}
	if (mouse_click(g_pos, mouse_pos, colorscale.g.getSize(), LKM)) {
		zahvat_rect = &colorscale.g;
	}
	if (mouse_click(b_pos, mouse_pos, colorscale.b.getSize(), LKM)) {
		zahvat_rect = &colorscale.b;
	}
}

void Color_indikator::draw(sf::RenderWindow& window) {
	window.draw(colorscale.R);
	window.draw(colorscale.G);
	window.draw(colorscale.B);
	window.draw(colorscale.r);
	window.draw(colorscale.g);
	window.draw(colorscale.b);

	window.draw(color_rect);
	
}


One_slider::One_slider(sf::Vector2f pos):point_begin(pos.x), zahvat_rect(nullptr) , pointer_shape(0) {
	rect = get_smal_rect();
	RECT = get_big_rect(360.f);

	RECT.setPosition(pos);
	rect.setPosition(pos.x, pos.y + (RECT.getSize().y + RECT.getOutlineThickness()) * 0.5f);

	point_end = point_begin + RECT.getSize().x;
}


void One_slider::draw(sf::RenderWindow& window) {
	window.draw(RECT);
	window.draw(rect);}

float One_slider::getSilverLevel(){
	float pos = rect.getPosition().x;
	return (point_begin - pos)/(point_begin - point_end);
}

void One_slider::update(sf::Vector2f mouse_pos, bool LKM, int pointer_shape, float angle_shape) {
	sf::Vector2f rect_pos = rect.getPosition();
	sf::Vector2f rect_size = rect.getSize();

	if (this->pointer_shape != pointer_shape) { rect.setPosition({point_begin+angle_shape , rect_pos.y}); }
	this->pointer_shape = pointer_shape;

	if (zahvat_rect != nullptr && LKM) {
	zahvat_rect->setPosition({ std::clamp(mouse_pos.x , point_begin,point_end) ,rect.getPosition().y });
	}
	else { zahvat_rect = nullptr; }
	

	if (mouse_click(rect_pos, mouse_pos, rect_size, LKM)) {
		zahvat_rect = &rect;
	}

}