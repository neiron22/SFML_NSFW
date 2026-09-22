//Model.cpp
#include "Model.hpp"

#include"Button.hpp"

void Model::draw(sf::RenderWindow & window) {
	window.draw(model);
}

void Model::Add(sf::Vector2f point, float size_shape, size_t facets, float angle) {
	//if (size_shape == 0.f) { model.append(sf::Vertex{ point }); return; }
	angle *= to_radian;
	for (int i = 0; i < facets; i++) {
		float angle_1 = angle + (p_2 * i / facets);
		float angle_2 = angle + (p_2 * (i + 1) / facets); 

		sf::Vector2f pos_1 = point + sf::Vector2f{ sinf(angle_1) , cosf(angle_1) } *size_shape;
		sf::Vector2f pos_2 = point + sf::Vector2f{ sinf(angle_2) , cosf(angle_2) } *size_shape;

		model.append(sf::Vertex{ point });
		model.append(sf::Vertex{ pos_1 });
		model.append(sf::Vertex{ pos_2 });

	}
	facets *= 3;
	shapes.push_back({ count_vertex , count_vertex + facets ,size_shape,  point , angle });

	count_vertex += facets;
}

void Model::Delete(size_t index){
	if (count_vertex == 0) { return; }

	size_t begin = shapes[index].begin;
	size_t end = shapes[index].end;
	int delta = int(end - begin);

	if (end == count_vertex) { // этот случай выполняется ТОЛЬКО если элемет послeдний
		model.resize(count_vertex - delta);
		shapes.pop_back();
		count_vertex -= delta;
		return;
	}

	for (int i = int(end) , it = int(begin); i < count_vertex; i++ , it ++) {
		model[it] = model[i];
	}
	model.resize(count_vertex - delta);
	count_vertex -= delta;
	
	shapes.erase(shapes.begin() + index);

	for (size_t i = index; i < shapes.size(); i++) {
		shapes[i].begin -= delta;
		shapes[i].end -= delta;
	}

	return;
}
void Model::Delete() {
	if (count_vertex == 0) { return; }

	size_t begin = shapes.back().begin;
	size_t end = shapes.back().end;
	int delta = int(end - begin);


	model.resize(count_vertex - delta);
	shapes.pop_back();
	count_vertex -= delta;
	return;
	}


void Model::move_1_shape(Shape_in_VertexArray& zahvat_shape, sf::Vector2f vec) {
	for (size_t i = zahvat_shape.begin; i < zahvat_shape.end; i++) {
		model[i].position += vec;
	}
	zahvat_shape.pos += vec;
}

void Model::setRotation_shape(size_t index, float angle){
	if (index >= shapes.size()) return;

		auto& shape = shapes[index];
		sf::Vector2f center = shape.pos;

		sf::Transform transform;
		transform.translate(center);
		transform.rotate(angle - shape.angle);
		transform.translate(-center);

		shape.angle = angle;

		for (size_t i = shape.begin; i < shape.end; i++) {
			model[i].position = transform.transformPoint(model[i].position);
		}
}

bool Model::pointInPolygon(sf::Vector2f point, size_t index) {

	sf::Vector2f center = model[shapes[index].begin].position;
	float radius = shapes[index].radius;

	sf::Vector2f dlt_vec = point - center;
	float delta = (dlt_vec.x * dlt_vec.x) + (dlt_vec.y * dlt_vec.y);
	if (delta < radius * radius) { return true; }
	return false;
}

void Model::update(std::vector<Button*> buttons , sf::Vector2f mouse_pos,  bool lkm , size_t poligon , float angle, sf::Color color, bool flag){
	sf::Vector2f pos = { 450.f,350.f };

	setRotation_shape(pointer_index_shape, angle);
	set_shape_color(pointer_index_shape , color);

	for (auto& it : buttons) {
		if (it->getClick()){
			switch (it->getType()){
			case ButtonType::add_vertex_Triangles:
				Add(pos , 30.f , poligon , 0.f);
				break;
			case ButtonType::deleted_shape:
				Delete();
				break;
			}
		}
	}


	if (inex_zahvat_shape != -1 && lkm ) {
		move_1_shape(shapes[inex_zahvat_shape], mouse_pos - (model[shapes[inex_zahvat_shape].begin].position + mouse_delta_pos));

		return;
	}
	else
	{
		inex_zahvat_shape = -1;
	}

	for (int i = 0; i < int(shapes.size()); i++) {

		if ((pointInPolygon(mouse_pos, i) && lkm) && flag)
		{
			inex_zahvat_shape = i;
			pointer_index_shape = i;
			mouse_delta_pos = mouse_pos - model[shapes[inex_zahvat_shape].begin].position;
		}
	}
}

void Model::set_shape_color(size_t index, sf::Color color){
	if (index >= shapes.size()) { return; }
	size_t start = shapes[index].begin;
	size_t end = shapes[index].end;

	for (rsize_t it = start; it < end; it++) {
		model[it].color = color;
	}

	shapes[index].color = color;
}

void Model::set_point_color(size_t index_point, sf::Color color){
	model[index_point].color = color;
}


