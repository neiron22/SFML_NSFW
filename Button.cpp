//Button.cpp

#include "Button.hpp"
#include "button_shape.hpp"

Button::Button(ButtonType type)
    : buttontype(type), clickedThisFrame(false), isPressed(false),
    wasPressedLastFrame(false), time(0.04f), timer(time) {
    // НЕ создаём фигуры здесь!
}

void Button::init(sf::Vector2f pos, sf::Color color) {
    this->pos = pos;
    this->color = color;

    // Создаём фигуры ЗДЕСЬ, когда pos и color уже известны
    float size = 20.f;

    int point_count = 4;

    switch (buttontype) {
    case ButtonType::deleted_shape: {
        color = sf::Color::Red;
        auto vertexarray = std::make_unique<sf::VertexArray>(sf::Triangles);
        for (int i = 0; i < point_count; i++) {
            float angle = i * (2.f * 3.14159f) / point_count;
            float angle_1 = (i+0.2f) * (2.f * 3.14159f) / point_count;
            
            sf::Vector2f pos_0 = pos + sf::Vector2f{ std::cosf(angle) * size,std::sinf(angle) * size };
            sf::Vector2f pos_1 = pos + sf::Vector2f{ std::cosf(angle_1) * size,std::sinf(angle_1) * size };

            (*vertexarray).append(sf::Vertex{pos, color});
            (*vertexarray).append(sf::Vertex{ pos_0, color });
            (*vertexarray).append(sf::Vertex{ pos_1, color });
        }
        shape = std::move(vertexarray);
    break;}
    case ButtonType::add_vertex_Triangles: {
        auto vertexarray = std::make_unique<sf::VertexArray>(sf::Triangles);
        for (int i = 0; i < point_count; i++) {
            float angle = i * (2.f * 3.14159f) / point_count;
            float angle_1 = (i + 1) * (2.f * 3.14159f) / point_count;

            sf::Vector2f pos_0 = pos + sf::Vector2f{ std::cosf(angle) * size,std::sinf(angle) * size };
            sf::Vector2f pos_1 = pos + sf::Vector2f{ std::cosf(angle_1) * size,std::sinf(angle_1) * size };

            (*vertexarray).append(sf::Vertex{ pos, color });
            (*vertexarray).append(sf::Vertex{ pos_0, color });
            (*vertexarray).append(sf::Vertex{ pos_1, color });
        }
        shape = std::move(vertexarray);
    break;}
    
    }

    // Инициализация rect (фон кнопки)
    rect.setSize({ size * 2.7f, size * 2.7f });
    rect.setOutlineThickness(5.f);
    rect.setOrigin({ size * 1.35f, size * 1.35f });
    rect.setOutlineColor(color);
    rect.setFillColor({ 0, 0, 0, 0 });
    rect.setPosition(pos);
}


void Button::update(sf::Vector2f vec, bool LKM ,float dt){

	sf::Vector2f delta = pos - vec;
	sf::Vector2f distance = rect.getSize() * 0.5f;

	bool isHovered = (std::fabs(delta.x) < distance.x && std::fabs(delta.y) < distance.y);

	if (isHovered && LKM && !wasPressedLastFrame) {
	clickedThisFrame = true; }
	else {clickedThisFrame = false; }

	wasPressedLastFrame = LKM;


	isPressed = isHovered && LKM;

    if (clickedThisFrame) {  
        timer = time;
    }

    if (timer > 0) {
        timer -= dt;
        rect.setFillColor({ 140, 140, 140 }); }


    else {rect.setFillColor(isHovered ? sf::Color(20, 20, 20) : sf::Color(0, 0, 0));}
}

void Button::draw(sf::RenderWindow& window){
	window.draw(rect);
	window.draw(*shape);
}
