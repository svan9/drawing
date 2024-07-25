#ifndef NAN_CONTEXT_HPP
#define NAN_CONTEXT_HPP

#include <SFML/Graphics.hpp>
#include <NAN/Window.hpp>
#include <NAN/ContextConfig.hpp>

namespace Nan {

class Context {
public:
	enum ShaderKind {
		Vertex, Fragment
	};
private:
	sf::RenderWindow* base_window;
	sf::Shader shader;
	sf::RectangleShape main_frame;
	ContextConfig style_config;
	bool is_cursor = true;
public:
	Context() { }
	~Context() { }
	
	Context(sf::RenderWindow* base_window) {
		this->base_window = base_window; 
	}

	void hide_cursor() {
		is_cursor = false;
	}
	void show_cursor() {
		is_cursor = true;
	}
	void update_cursor() {
		base_window->setMouseCursorVisible(is_cursor);
	}

	void resize(sf::Vector2u size) {
		main_frame.setSize(sf::Vector2f(size.x, size.y));
	}
	void resize(size_t w, size_t h) {
		main_frame.setSize(sf::Vector2f(w, h));
	}

	void create(sf::RenderWindow* base_window) {
		this->base_window = base_window; 
	}

	ContextConfig& config() {
		return style_config;
	}

	void load_shader(const char* path_to_vertex, const char* path_to_fragment) {
		if (!shader.loadFromFile(path_to_vertex, path_to_fragment)) {
			throw std::runtime_error("cannot load shaders");
		}
	}

	void load_shader(const char* path) {
	  load_shader(path, Nan::Context::ShaderKind::Fragment);
	}
	void load_shader(const char* path, Nan::Context::ShaderKind sh_kind) {
		if (sh_kind == ShaderKind::Fragment) {
			if (!shader.loadFromFile(path, sf::Shader::Fragment)) {
				throw std::runtime_error("cannot load shader");
			}
		}
		else if (sh_kind == ShaderKind::Vertex) {
			if (!shader.loadFromFile(path, sf::Shader::Vertex)) {
				throw std::runtime_error("cannot load shader");
			}
		}
	}

	template<typename T>
	void set(const char* name, T value) {
		// shader.setParameter(name, value);
		shader.setUniform(name, value);
	}

	void draw() {
		update_cursor();
		// set("texture", sf::Shader::CurrentTexture);
		// base_window->draw(main_frame, &shader);
		// base_window->draw(main_frame);
	}

	void draw_circle(uint32_t x, uint32_t y, float weight, sf::Color color = sf::Color::Black) {
		sf::CircleShape crc;
		crc.setFillColor(color);
		crc.setRadius(weight);
		crc.setPosition(x, y);
		base_window->draw(crc);
	}

	void draw_circle_empty(uint32_t x, uint32_t y, float weight, float border_weight, sf::Color color = sf::Color::Black) {
		sf::CircleShape crc;
		crc.setFillColor(sf::Color::Transparent);
		crc.setOutlineColor(color);
		crc.setOutlineThickness(border_weight);
		crc.setRadius(weight);
		crc.setPosition(x-weight, y-weight);
		base_window->draw(crc);
	}

	static void draw_circle(sf::RenderTexture& rt, uint32_t x, uint32_t y, float weight, sf::Color color = sf::Color::Black) {
		sf::CircleShape crc;
		crc.setFillColor(color);
		crc.setRadius(weight);
		crc.setPosition(x, y);
		rt.draw(crc);
	}

	static void draw_circle_empty(sf::RenderTexture& rt, uint32_t x, uint32_t y, float radius, float border_weight=1.0f, sf::Color color = sf::Color::Black) {
		sf::CircleShape crc;
		crc.setFillColor(sf::Color::Transparent);
		crc.setOutlineColor(color);
		crc.setOutlineThickness(border_weight);
		crc.setRadius(radius);
		crc.setPosition(x-radius, y-radius);
		rt.draw(crc);
	}

	static void draw_line(sf::RenderTexture& rt, float x1, float y1, float x2, float y2, sf::Color color = sf::Color::Black) {
		sf::Vertex line[] =
		{
			sf::Vertex(sf::Vector2f(x1, y1), color),
			sf::Vertex(sf::Vector2f(x2, y2), color)
		};
		rt.draw(line, 2, sf::Lines);
	}

	void draw(sf::RenderTexture& rt, uint32_t x, uint32_t y) {
		rt.display();
		const auto& texture = rt.getTexture();
		sf::Sprite sprite(texture);
		sprite.setPosition(x, y);
		// sf::IntRect(
		// 			{static_cast<int>(x), static_cast<int>(y)},
		// 			{static_cast<int>(rt.getSize().x), static_cast<int>(rt.getSize().y)}
		// 		)
		base_window->draw(sprite);
	}

	void draw_rect(size_t x, size_t y, size_t w, size_t h) {
		sf::ConvexShape cnv;
		cnv.setPoint(0, sf::Vector2f(x, y));
		cnv.setPoint(1, sf::Vector2f(x+w, y));
		cnv.setPoint(2, sf::Vector2f(x+w, y+h));
		cnv.setPoint(3, sf::Vector2f(x, y+h));
		base_window->draw(cnv);
	}

	static void draw_rect_line(sf::RenderTexture& rt,
		size_t x, size_t y, 
		size_t dx, size_t dy, size_t w,
		sf::Color color = sf::Color::Black
	) {
		sf::ConvexShape cnv;
		cnv.setPoint(0, sf::Vector2f(x-w, y-w));
		cnv.setPoint(1, sf::Vector2f(dx-w, dy-w));
		cnv.setPoint(2, sf::Vector2f(dx+w, dy+w));
		cnv.setPoint(3, sf::Vector2f(x+w, y+w));
		cnv.setFillColor(color);
		rt.draw(cnv);
	}

	void draw_point(size_t x, size_t y) {
		sf::ConvexShape cnv;
		cnv.setPoint(0, sf::Vector2f(x, y));
		sf::CircleShape crc;
		base_window->draw(cnv);
	}

	// void draw() {
	// 	// base_window.draw()
	// }
};

}
#endif