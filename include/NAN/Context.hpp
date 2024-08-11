#ifndef NAN_CONTEXT_HPP
#define NAN_CONTEXT_HPP

#include <SFML/Graphics.hpp>
#include <NAN/Window.hpp>
#include <NAN/ContextConfig.hpp>
#include <NAN/tools/Bounds.hpp>
#include <glm/glm.hpp>
#include <functional>

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
	sf::Cursor cursor;
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
		base_window->setMouseCursor(cursor);
		base_window->setMouseCursorVisible(is_cursor);
	}
	void set_cursor(sf::Cursor::Type _cursor) {
		this->cursor.loadFromSystem(_cursor);
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

	void print_text(std::string& text, Tools::Boundu rect) {
		sf::Text __text;
		__text.setString(text);
		float __char_size = text.size()/rect.w;
		__text.setCharacterSize(__char_size);
		sf::Vector2f pos({(float)rect.x, (float)rect.y});
		__text.setPosition(pos);
		base_window->draw(__text);
	}

	void draw(const sf::Drawable &drawable, const sf::RenderStates &states = sf::RenderStates::Default) {
		base_window->draw(drawable, states);
	}

	template<typename T>
	void set(const char* name, T value) {
		// shader.setParameter(name, value);
		shader.setUniform(name, value);
	}

	void drawing() {
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

	void draw_line(float x1, float y1, float x2, float y2, sf::Color color = sf::Color::Black) {
		sf::Vertex line[] =
		{
			sf::Vertex(sf::Vector2f(x1, y1), color),
			sf::Vertex(sf::Vector2f(x2, y2), color)
		};
		base_window->draw(line, 2, sf::Lines);
	}
	void draw_line_x(float x, float y, float width, float weight, sf::Color color = sf::Color::Black) {
		sf::RectangleShape cnv;
		cnv.setPosition(sf::Vector2f(x, y));
		cnv.setSize(sf::Vector2f(width, 1));
		cnv.setFillColor(color);
		cnv.setOutlineColor(color);
		cnv.setOutlineThickness(weight);
		base_window->draw(cnv);
	}
	void draw_rect(float x, float y, float width, float height, float weight=1.0f, sf::Color color = sf::Color::Black) {
		sf::RectangleShape cnv;
		cnv.setPosition(sf::Vector2f(x, y));
		cnv.setSize(sf::Vector2f(width, height));
		cnv.setFillColor(color);
		cnv.setOutlineColor(color);
		cnv.setOutlineThickness(weight);
		base_window->draw(cnv);
	}
	static void draw_rect(sf::RenderTexture& rt, float x, float y, float width, float height, float weight=1.0f, sf::Color color = sf::Color::Black) {
		sf::RectangleShape cnv;
		cnv.setPosition(sf::Vector2f(x, y));
		cnv.setSize(sf::Vector2f(width, height));
		cnv.setFillColor(color);
		cnv.setOutlineColor(color);
		cnv.setOutlineThickness(weight);
		rt.draw(cnv);
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

	// void draw_rect(size_t x, size_t y, size_t w, size_t h) {
	// 	sf::ConvexShape cnv;
	// 	cnv.setPoint(0, sf::Vector2f(x, y));
	// 	cnv.setPoint(1, sf::Vector2f(x+w, y));
	// 	cnv.setPoint(2, sf::Vector2f(x+w, y+h));
	// 	cnv.setPoint(3, sf::Vector2f(x, y+h));
	// 	base_window->draw(cnv);
	// }

	static void draw_rect_line(sf::RenderTexture& rt,
		size_t x, size_t y, 
		size_t dx, size_t dy,
		float ot = 2,
		sf::Color color = sf::Color::Black
	) {
		for (int f = 0; f < ot; f++) {
			x+=f; y+=f; dx-=f; dy-=f;
			sf::Vertex line[] =
			{
				sf::Vertex(sf::Vector2f(x, y), color),
				sf::Vertex(sf::Vector2f(dx, y), color),

				sf::Vertex(sf::Vector2f(dx, y), color),
				sf::Vertex(sf::Vector2f(dx, dy), color),

				sf::Vertex(sf::Vector2f(dx, dy), color),
				sf::Vertex(sf::Vector2f(x, dy), color),
				
				sf::Vertex(sf::Vector2f(x, dy), color),
				sf::Vertex(sf::Vector2f(x, y), color)
			};
			rt.draw(line, 8, sf::Lines);
		}
	}

	static void rotate_r4(
		size_t& x, size_t& y, 
		size_t& dx, size_t& dy,
		size_t& x_2, size_t& y_2, 
		size_t& dx_2, size_t& dy_2
	) {
		size_t _x = x;
		x = dx;
		dx = dx_2;
		dx_2 = x_2;
		x_2 = _x;

		size_t _y = y;
		y = dy;
		dy = dy_2;
		dy_2 = y_2;
		y_2 = _y;
	}

	static bool is_normal_r4(
		size_t& x, size_t& y, 
		size_t& dx, size_t& dy,
		size_t& x_2, size_t& y_2, 
		size_t& dx_2, size_t& dy_2
	) {
		if (
			std::min({x, dx, x_2, dx_2}) == x &&
			std::max({x, dx, x_2, dx_2}) == dx_2 &&
			std::min({y, dy, y_2, dy_2}) == y &&
			std::min({x, dx, x_2, dx_2}) == x
		) {
			return true;
		}

		return false;
	}

	template<typename T>
	static T find_more(T value, std::initializer_list<sf::Uint32> il) {
		for (T& val_: il) { if (val_ > value) { return val_; } }
		return 0;
	}

	template<typename T>
	static T find_less(T value, std::initializer_list<sf::Uint32> il) {
		for (T& val_: il) { if (val_ < value) { return val_; } }
		return 0;
	}
	
	template<typename T>
	static T find_if(bool(*func)(T&), std::initializer_list<sf::Uint32> il) {
		for (T& val_: il) { if (func(val_)) { return val_; } }
		return 0;
	}
	
	template<typename T>
	static T find_if(const std::function<bool(T&)>& func, std::initializer_list<sf::Uint32> il) {
		for (T& val_: il) { if (func(val_)) { return val_; } }
		return 0;
	}

	template<typename T>
	static size_t find_if_index(std::function<bool(T&)>& func, std::vector<T> il) {
		int i = 0;
		for (T& val_: il) { 
			if (func(val_)) { 
				return i;
			} 
			i++;
		}
		return 0;
	}

	// static void normal_r4(
	// 	size_t& x, size_t& y, 
	// 	size_t& dx, size_t& dy,
	// 	size_t& x_2, size_t& y_2, 
	// 	size_t& dx_2, size_t& dy_2
	// ) {
	// 	auto ffx = {x, dx, x_2, dx_2};
	// 	auto ffy = {y, dy, y_2, dy_2};
	// 	std::vector<sf::Vector2u> ff = {{x, y}, {dx, dy}, {x_2, y_2}, {dx_2, dy_2}};

	// 	x = std::min(ffx);
	// 	y = std::min(ffy);
	// 	dx_2 = std::max(ffx);
	// 	dy_2 = std::max(ffy);

	// 	std::function<bool(sf::Vector2u&)> fndx;
	// 	fndx = [x, dy_2](sf::Vector2u& d) -> bool {
	// 		return d.x > x && d.y < dy_2;
	// 	};

	// 	size_t _di = find_if_index(fndx, ff);
	// 	dx = *(ffx.begin()+_di);
	// 	dy = *(ffy.begin()+_di);

	// 	std::function<bool(sf::Vector2u&)> fnx_2;
	// 	fnx_2 = [y, dx_2](sf::Vector2u& d) -> bool {
	// 		return d.x > dx_2 && d.y < y;
	// 	};

	// 	_di = find_if_index(fnx_2, ff);
		
	// 	x_2 = *(ffx.begin()+_di);
	// 	y_2 = *(ffy.begin()+_di);

	// }
	
	static void draw_rect_line(sf::RenderTexture& rt,
		size_t x, size_t y, 
		size_t dx, size_t dy,
		size_t x_2, size_t y_2, 
		size_t dx_2, size_t dy_2,
		float ot = 2,
		sf::Color color = sf::Color::Black
	) {
		for (int f = 0; f < ot; f++) {
			x-=f; y-=f; dx+=f; dy-=f;
			x_2-=f; y_2+=f; dx_2+=f; dy_2+=f;
			sf::Vertex line[] = {
				sf::Vertex(sf::Vector2f(x, y), color),
				sf::Vertex(sf::Vector2f(dx, dy), color),

				sf::Vertex(sf::Vector2f(dx, dy), color),
				sf::Vertex(sf::Vector2f(dx_2, dy_2), color),

				sf::Vertex(sf::Vector2f(dx_2, dy_2), color),
				sf::Vertex(sf::Vector2f(x_2, y_2), color),

				sf::Vertex(sf::Vector2f(x_2, y_2), color),
				sf::Vertex(sf::Vector2f(x, y), color),
			};
			rt.draw(line, 8, sf::Lines);
		}
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