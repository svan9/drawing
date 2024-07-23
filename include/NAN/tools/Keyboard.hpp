#ifndef NAN_TOOLS_KEYBOARD_HPP 
#define NAN_TOOLS_KEYBOARD_HPP 

#include <SFML/Graphics.hpp>
#include <functional>
#include <type_traits>

namespace Nan {
namespace Tools {
	class KeyboardEvent {
		public:
			sf::Event::KeyEvent kw;

			bool is_pressed(sf::Keyboard::Key key) {
				return sf::Keyboard::isKeyPressed(key);
			}
			
			KeyboardEvent(sf::Event::KeyEvent kw) {
				this->kw = kw;
			}

			KeyboardEvent() { }
	};
	class Keyboard {
	private:
		float x, y;
		bool is_pressed = false;
		sf::Clock clock;
		KeyboardEvent event_instances;
		int time_down = 0;
	public:
		
		void update_time() {
			time_down = clock.getElapsedTime().asMilliseconds();
			clock.restart();
		}

		bool is_key_pressed(sf::Keyboard::Key key) {
			return sf::Keyboard::isKeyPressed(key);
		}

		virtual void on_key_down(Tools::KeyboardEvent& ev) = 0;
		virtual void on_key_up  (Tools::KeyboardEvent& ev) = 0;
		// virtual void on_key_hold(Tools::KeyboardEvent& ev) = 0;

		void provide_key(sf::Event& ev, sf::RenderWindow& ptw) {			
			switch (ev.type) {
				case (sf::Event::KeyPressed): {
					event_instances.kw = ev.key;
					on_key_down(event_instances);
				} break;
				case (sf::Event::KeyReleased): {
					event_instances.kw = ev.key;
					on_key_up(event_instances);
				} break;
				
				default: break;
			}
		}
	};
	
};
};

#endif