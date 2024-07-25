#ifndef NAN_CONTEXTCONFIG_HPP
#define NAN_CONTEXTCONFIG_HPP

#include <SFML/Graphics.hpp>
#include <NAN/Window.hpp>

namespace Nan {

class ContextConfig {
public:
	struct Background {
		sf::Color color = sf::Color::White;
	};
private:
	
	Background _background;
public:
	ContextConfig() {}

	void background(sf::Color color) {
		_background.color = color;
	}

	Background background() {
		return _background;
	} 
};

}
#endif