#ifndef NAN_FRAME_WIDGET_HPP
#define NAN_FRAME_WIDGET_HPP

#include <SFML/Graphics.hpp>
#include <NAN/Window.hpp>
#include <NAN/Context.hpp>
#include <NAN/Widget.hpp>
#include <NAN/tools/Bounds.hpp>
#include <NAN/tools/Mouse.hpp>

namespace Nan {

class Frame: public Widget {
private:
public:
	Frame() { }

	Frame(Tools::Boundu __bounds) {
		bounds(__bounds);
	}

	~Frame() = default;

	void start() { }
	
	void update() { }

	void draw(Nan::Context& ctx) {
		// ctx.draw_();
	}

	void on_mouse_click(size_t x, size_t y) {

	}
	
	void event(sf::Event& ev, sf::RenderWindow& ptw) {
		// switch (ev.type) {
		// case (sf::Event::MouseButtonReleased):
		// 	/* code */
		// 	break;
		
		// default:
		// 	break;
		// }
	}
};

}
#endif