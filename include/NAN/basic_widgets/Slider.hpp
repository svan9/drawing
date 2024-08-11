#ifndef NAN_SLIDER_WIDGET_HPP
#define NAN_SLIDER_WIDGET_HPP

#include <SFML/Graphics.hpp>
#include <NAN/Window.hpp>
#include <NAN/Context.hpp>
#include <NAN/Widget.hpp>
#include <NAN/utils.hpp>
#include <NAN/tools/Bounds.hpp>
#include <NAN/tools/Mouse.hpp>
#include <NAN/basic_widgets/HSLColorPicker.hpp>
#include <NAN/tools/Keyboard.hpp>
#include <iostream>
#include <glm/glm.hpp>

#include <Windows.h>

namespace Nan {

class Slider:
	public Widget,
	public Tools::Mouse,
	public Tools::Keyboard {
private:
	float circle_radius = 10.0f;
	sf::Color basic_color = sf::Color(0xaaaaaaff); 
	sf::Color basic_color_circle = sf::Color::White; 
	float x = 1.0f;
	bool grabbed = false;
	const float margin = 5.0f;

	float line_x;
	float line_y;
	float line_x2;
	float line_y2;

	float xx = .0f;
	float yy = .0f;
public:
	Slider() {
		config();
	}

	Slider(Tools::Boundu __bounds) {
		bounds(__bounds);
		config();
	}

	void setConfig(sf::Color line_color, sf::Color circle_color) {
		basic_color = line_color;
		basic_color_circle = circle_color;
	}

	void config() {
		ratio_by_height();
	}

	float get() const noexcept { return x; }
	void set(float __x) { x=__x; }

	void start() { }
	
	void update() {	}

	void calc() { }

	void draw(Nan::Context& ctx) {
		ctx.draw_rect(bounds().x, bounds().y, bounds().w, bounds().h);
		ctx.draw_line_x(
			margin+bounds().x, bounds().y+(bounds().h/2.0f),
			bounds().w-margin*2,
			1.0f, basic_color);
		ctx.draw_circle((x*(bounds().w-margin*2))+bounds().x-(circle_radius/2.0f), bounds().y, circle_radius, basic_color_circle);
		if (!is_inside(&bounds())) { return; }
		ctx.set_cursor(sf::Cursor::Type::Hand);
	}

  void on_key_down(Tools::KeyboardEvent& ev) {
		// if (!is_inside(bounds())) { return; }
		// x = Nan::block(0.0f, (getMouse().x-bounds().x)/(bounds().w-margin*2), 1.0f);
	}

  void on_key_up(Tools::KeyboardEvent& ev) {
		if (!is_inside(&bounds())) { return; }
		if (sf::Keyboard::Key::Num1) { x = 0.1f; }
		else if (sf::Keyboard::Key::Num2) { x = 0.2f; }
		else if (sf::Keyboard::Key::Num3) { x = 0.3f; }
		else if (sf::Keyboard::Key::Num4) { x = 0.4f; }
		else if (sf::Keyboard::Key::Num5) { x = 0.5f; }
		else if (sf::Keyboard::Key::Num6) { x = 0.6f; }
		else if (sf::Keyboard::Key::Num7) { x = 0.7f; }
		else if (sf::Keyboard::Key::Num8) { x = 0.8f; }
		else if (sf::Keyboard::Key::Num9) { x = 0.9f; }
		else if (sf::Keyboard::Key::Num0) { x = 0.0f; }
		else if (ev.kw.shift && sf::Keyboard::Key::Num1) { x = 1.0f; }
	}
	
	void on_mouse_down(Tools::MouseEvent& ev) { }

	void on_mouse_up(Tools::MouseEvent& ev) {
		grabbed = false;
	}

	void on_mouse_move(Tools::MouseEvent& ev) { }

	void on_wheel_scroll(Tools::MouseEvent& ev) {
		if (!is_inside(&bounds())) { return; }
		if (is_key_pressed(sf::Keyboard::Key::F)) {
			x = Nan::block(0.0f, x+(ev.scroll/10.0f), 1.0f);
		}
	}

	void on_mouse_hold(Tools::MouseEvent& ev) {
		// +bounds().x+(circle_radius/2.0f),
		if (!is_inside(&bounds())) return;
		// if (grabbed) {
		x = Nan::block(0.0f, (ev.x-bounds().x)/(bounds().w-margin*2), 1.0f);
			// return;
		// }
		// if (is_inside(
		// 	(x*(bounds().w-margin*2))+bounds().x,
		// 	bounds().y+(circle_radius/2.0f),
		// 	circle_radius
		// )) {
		// 	grabbed = true;
		// }
	}

	void event(sf::Event& ev, sf::RenderWindow& ptw) {
		provide_key(ev, ptw);
		provide_mouse(ev, ptw);
	}
};

}
#endif