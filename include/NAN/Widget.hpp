#ifndef NAN_WIDGET_HPP
#define NAN_WIDGET_HPP

#include <SFML/Graphics.hpp>
#include <NAN/Context.hpp>
#include <NAN/tools/Mouse.hpp>
#include <NAN/tools/Bounds.hpp>

namespace Nan {

class Widget {
private:
	Tools::Boundu __bounds;
	float ratio_w = 1.0f;
	float ratio_h = 1.0f;
public:

	void ratio_by_width() {
		if (__bounds.w > __bounds.h) {
			ratio_h = __bounds.w/__bounds.h;
		} else {
			ratio_h = __bounds.h/__bounds.w;
		}
	}

	void ratio_by_height() {
		if (__bounds.w > __bounds.h) {
			ratio_w = __bounds.w/__bounds.h;
		} else {
			ratio_w = __bounds.h/__bounds.w;
		}
	}

	void set_ratio(float w, float h) {
		ratio_w = w;
		ratio_h = h;
	}

	Tools::Boundu& bounds(Tools::Boundu bounds) {
		__bounds << bounds;
		__bounds.w *= ratio_w;
		__bounds.h *= ratio_h;
		return __bounds;
	}

	Tools::Boundu& bounds() {
		return __bounds; 
	}
	
	virtual void start() = 0;
	virtual void update() = 0;
	virtual void draw(Nan::Context& ctx) = 0;
	virtual void event(sf::Event& ev, sf::RenderWindow& ptw) = 0;
};


}
#endif