#ifndef NAN_CANVAS_WIDGET_HPP
#define NAN_CANVAS_WIDGET_HPP

#include <SFML/Graphics.hpp>
#include <NAN/Window.hpp>
#include <NAN/Context.hpp>
#include <NAN/Widget.hpp>
#include <NAN/utils.hpp>
#include <NAN/tools/Bounds.hpp>
#include <NAN/tools/Mouse.hpp>
#include <NAN/tools/Keyboard.hpp>
#include <glm/glm.hpp>
#include <iostream>

namespace Nan {

class Canvas: public Widget, public Tools::Mouse, public Tools::Keyboard {
private:
	Tools::Boundu bounds;
	sf::RenderTexture rt;
	sf::Clock clock;
	float radius = 5.0f;
	sf::Color color = sf::Color::Black;
	sf::Color alt_color = sf::Color::White;
	sf::Vector2f circle;
	glm::vec2 last;
public:
	Canvas() {
		config();
	}

	Canvas(Tools::Boundu bounds) {
		this->bounds = bounds;
		config();
	}

	void setColor(sf::Color color) {
		this->color = color;
	}

	void setWeight(float radius) {
		this->radius = radius;
	}
 
	void config() {
		sf::ContextSettings settings;
		settings.antialiasingLevel = 8;
		circle.x = 0;
		circle.y = 0;
		last.x = 0;
		last.y = 0;
		rt.create(bounds.w, bounds.h);
		rt.setSmooth(true);
	}

	void start() { }
	
	void update() { }

	void draw(Nan::Context& ctx) {
		ctx.draw(rt, bounds.x, bounds.y);
		ctx.draw_circle_empty(circle.x, circle.y, radius, 2);
		ctx.hide_cursor();
	}

  void on_key_down(Tools::KeyboardEvent& ev) {
		
	}

  void on_key_up(Tools::KeyboardEvent& ev) {

	}

	void on_mouse_down(Tools::MouseEvent& ev) { }

	void on_mouse_up(Tools::MouseEvent& ev) {
		last.x = 0.0f;
		last.y = 0.0f;
	}

	void on_mouse_move(Tools::MouseEvent& ev) {
		circle.x = ev.x;
		circle.y = ev.y;
	}

	void drawing(glm::vec2 current) {
		sf::CircleShape crc;
		crc.setFillColor(color);
		crc.setPosition(current.x, current.y);
		crc.setRadius(radius-1);
		crc.setOutlineColor(sf::Color(color.r, color.g, color.b, 0xAA));
		crc.setOutlineThickness(1);
		rt.draw(crc);
		float dist = glm::sqrt(
			(current.x - last.x)*(current.x - last.x)+
			(current.y - last.y)*(current.y - last.y)
		);
		if (last.x == 0 && last.y == 0) { last = current; return; }
		float steps = dist/radius*2;
		glm::vec2 temp = current;
		for (int i = 0; i <= steps; ++i) {
			float t = static_cast<float>(i) / steps;
			float x = last.x * (1 - t) + current.x * t;
			float y = last.y * (1 - t) + current.y * t;
			crc.setPosition({x, y});
			rt.draw(crc);
		}
		last = current;
	}

	void erasing(glm::vec2 current) {
		sf::CircleShape crc;
		crc.setFillColor(alt_color);
		crc.setPosition(current.x, current.y);
		crc.setRadius(radius);
		rt.draw(crc);

		float dist = glm::sqrt(
			(current.x - last.x)*(current.x - last.x)+
			(current.y - last.y)*(current.y - last.y)
		);


		if (last.x == 0 && last.y == 0) {
			last = current;
			return;
		}
		
		float steps = dist/radius*2;

		for (int i = 0; i <= steps; ++i) {
			float t = static_cast<float>(i) / steps;
			float x = last.x * (1 - t) + current.x * t;
			float y = last.y * (1 - t) + current.y * t;
			crc.setPosition({x, y});
			rt.draw(crc);
		}

		last = current;
	}

	void on_wheel_scroll(Tools::MouseEvent& ev) {
		if ( is_key_pressed(sf::Keyboard::Key::F) ) {
			radius = Nan::block(2.0f, radius+ev.scroll, 50.0f);
		}
	}

	void on_mouse_hold(Tools::MouseEvent& ev) {
		glm::vec2 current(ev.x, ev.y);
		current -= radius;

		if (ev.button == sf::Mouse::Button::Left) {
			drawing(current);
		}
		else if (ev.button == sf::Mouse::Button::Right) {
			erasing(current);
		}
	}


	
	void event(sf::Event& ev, sf::RenderWindow& ptw) {
		provide_key(ev, ptw);
		provide_mouse(ev, ptw);
	}
};

}
#endif