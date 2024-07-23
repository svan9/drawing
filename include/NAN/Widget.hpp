#ifndef NAN_WIDGET_HPP
#define NAN_WIDGET_HPP

#include <SFML/Graphics.hpp>
#include <NAN/Context.hpp>
#include <NAN/tools/Mouse.hpp>

namespace Nan {

class Widget {
// private:
public:
	virtual void start() = 0;
	virtual void update() = 0;
	virtual void draw(Nan::Context& ctx) = 0;
	virtual void event(sf::Event& ev, sf::RenderWindow& ptw) = 0;
};


}
#endif