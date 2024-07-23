#ifndef NAN_TOOLS_MOUSE_HPP 
#define NAN_TOOLS_MOUSE_HPP 

#include <SFML/Graphics.hpp>
#include <functional>
#include <type_traits>

namespace Nan {
namespace Tools {
	class MouseEvent {
		public:
			float x, y;
			sf::Mouse::Button button;
			float scroll = 0;
			
			MouseEvent(float x, float y, sf::Mouse::Button button) {
				this->x = x; this->y = y; this->button = button;
			}

			MouseEvent() {
				MouseEvent(0, 0, sf::Mouse::Button::ButtonCount);
			}
	};
	class Mouse {
	private:
		float x, y;
		bool is_pressed = false;
		sf::Clock clock;
		MouseEvent event_instances;
		int time_down = 0;
	public:
		
		void update_time() {
			time_down = clock.getElapsedTime().asMilliseconds();
			clock.restart();
		}

		virtual void on_mouse_down(Tools::MouseEvent& ev) = 0;
		virtual void on_mouse_up  (Tools::MouseEvent& ev) = 0;
		virtual void on_mouse_move(Tools::MouseEvent& ev) = 0;
		virtual void on_mouse_hold(Tools::MouseEvent& ev) = 0;
		virtual void on_wheel_scroll(Tools::MouseEvent& ev) = 0;


		void provide_mouse(sf::Event& ev, sf::RenderWindow& ptw) {			
			switch (ev.type) {
				case (sf::Event::MouseButtonPressed): {
					update_time();
					is_pressed = true;
					event_instances.x = x;
					event_instances.y = y;
					event_instances.button = ev.mouseButton.button;
					on_mouse_down(event_instances);
				} break;
				case (sf::Event::MouseButtonReleased): {
					is_pressed = false;
					event_instances.x = x;
					event_instances.y = y;
					event_instances.button = ev.mouseButton.button;
					on_mouse_up(event_instances);
				} break;

				case (sf::Event::MouseMoved): {
					sf::Vector2f v = ptw.mapPixelToCoords({ ev.mouseMove.x, ev.mouseMove.y });
					x = v.x; 
					y = v.y;
					event_instances.x = x;
					event_instances.y = y;
					if (is_pressed) { on_mouse_hold(event_instances); }
					on_mouse_move(event_instances);
				} break;

				case (sf::Event::MouseWheelScrolled): {
					event_instances.scroll = ev.mouseWheelScroll.delta;
					on_wheel_scroll(event_instances);
				} break;
				
				default: break;
			}
		}
	};
	
};
};

#endif