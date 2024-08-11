#ifndef NAN_TEXT_WIDGET_HPP
#define NAN_TEXT_WIDGET_HPP

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
#include <string>
#include <glm/glm.hpp>

#include <Windows.h>

namespace Nan {

class Text:
	public Widget,
	public Tools::Mouse,
	public Tools::Keyboard {
private:
	std::string text;
public:
	Text() {
		config();
	}

	Text(Tools::Boundu __bounds) {
		bounds(__bounds);
		config();
	}

	Text(Tools::Boundu __bounds, std::string __text) {
		bounds(__bounds);
		setText(__text);
		config();
	}

	void setText(std::string __text) {
		text = __text;
	}

	void config() {
		ratio_by_height();
	}

	void start() { }
	
	void update() {	}

	void calc() { }

	void draw(Nan::Context& ctx) {
		ctx.print_text(text, bounds());
	}

  void on_key_down(Tools::KeyboardEvent& ev) {
	}

  void on_key_up(Tools::KeyboardEvent& ev) {
	}
	
	void on_mouse_down(Tools::MouseEvent& ev) { }

	void on_mouse_up(Tools::MouseEvent& ev) {
	}

	void on_mouse_move(Tools::MouseEvent& ev) { }

	void on_wheel_scroll(Tools::MouseEvent& ev) {
	}

	void on_mouse_hold(Tools::MouseEvent& ev) {
	}

	void event(sf::Event& ev, sf::RenderWindow& ptw) {
		provide_key(ev, ptw);
		provide_mouse(ev, ptw);
	}
};

}
#endif