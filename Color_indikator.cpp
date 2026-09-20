//Color_indikator.cpp
#include "Color_indikator.hpp"

Color_indikator::Color_indikator(sf::Vector2f vec) :
	colorscale(vec) { point = vec.x;
color_rect.setPosition(vec + sf::Vector2f{ 280.f,0.f });
float size = 50.f;
color_rect.setSize({size,size});
color_rect.setFillColor(sf::Color::Black);

zahvat_rect = nullptr;
}

bool mouse_click(sf::Vector2f pos , sf::Vector2f mouse_pos , sf::Vector2f size , bool LKM) {
	sf::Vector2f delta = (pos - mouse_pos);
	if (std::fabs(delta.x) < size.x && std::fabs(delta.y) < size.y && LKM) { return true; }
	return false;}

void Color_indikator::update(sf::Vector2f mouse_pos, bool LKM){
	sf::Vector2f r_pos = colorscale.r.getPosition();
	sf::Vector2f g_pos = colorscale.g.getPosition();
	sf::Vector2f b_pos = colorscale.b.getPosition();

	sf::Color color = { static_cast<sf::Uint8>(r_pos.x - point) ,
						static_cast<sf::Uint8>(g_pos.x - point) ,
						static_cast<sf::Uint8>(b_pos.x - point) };

	color_rect.setFillColor(color);

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