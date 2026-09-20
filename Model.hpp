//Model.hpp
#pragma once

#include<SFML/Graphics.hpp>
#include<vector>

#include"Type.hpp"

class Button;

struct Shape_in_VertexArray{
	size_t begin, end;
	float radius;
	Shape_in_VertexArray(size_t begin, size_t end ,float radius) noexcept: begin(begin), end(end) , radius(radius){}
};

class Model{
	sf::VertexArray model;
	std::vector<Shape_in_VertexArray> shapes;
	size_t count_vertex;
	int inex_zahvat_shape;
	sf::Vector2f mouse_delta_pos;
public:
	
	Model() noexcept {
		model.setPrimitiveType(sf::Triangles); count_vertex = 0;
		inex_zahvat_shape = -1; mouse_delta_pos = { 0.f,0.f }; };

	void draw(sf::RenderWindow& window);

	void Add(sf::Vector2f point , float size_shape = 60.f, int facets = 3, float angle = 0.f);

	void Delete(size_t index);

	void Delete();

	void move_1_shape(Shape_in_VertexArray& zahvat_shape, sf::Vector2f vec);

	bool pointInPolygon(sf::Vector2f point, rsize_t index);

	void update(std::vector<Button*> buttons, sf::Vector2f mouse_pos, bool lkm, int poligon = 6);

	int get_shape_count() { return int(shapes.size()); }

	void set_shape_color(size_t index, sf::Color color);

	void set_point_color(size_t index_point, sf::Color color);
};

