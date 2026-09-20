//FontManager.hpp
#pragma once
#include<SFML/Graphics.hpp>

class FontManager {
	static sf::Font font;
public:
	static sf::Font& get();
	static void init();
};

