#ifndef NAN_WINDOW_HPP
#define NAN_WINDOW_HPP

#include <thread>
#include <SFML/Graphics.hpp>
#ifdef __linux__
#include <X11/Xlib.h>
#endif
#include <NAN/Widget.hpp>
#include <NAN/Widgets.hpp>
#include <NAN/Context.hpp>
#include <vector>
#include <memory>

#define NAN_WINDOW_FRAME_RATE 144

namespace Nan {

class Window {
private:
	sf::RenderWindow window;
	// std::vector<void*> widgets;
	Nan::Context ctx;
	sf::Vector2f mouse_pos;
	sf::Clock clock;
	bool has_antialiasing = true;
public:
	Window() {
		window.create(sf::VideoMode(200, 200), "...", sf::Style::Default, config());
		ctx.create(&window);
	}

	Window(size_t width, size_t height) {
		window.create(sf::VideoMode(width, height), "...", sf::Style::Default, config());
		updateFrameRate(NAN_WINDOW_FRAME_RATE);
		ctx.create(&window);
	}

	sf::ContextSettings config() {
		sf::ContextSettings settings;
		if (has_antialiasing) { settings.antialiasingLevel = 8; }
		return settings;
	}

	void updateFrameRate(uintptr_t frame_rate) {
		window.setFramerateLimit(frame_rate);
	}	

	void setTitle(const char* title) {
		window.setTitle(title);
	}
	
	void setBounds(size_t width, size_t height) {
		window.setSize(sf::Vector2u(width, height));
	}

	sf::Vector2f mapPixelToCoords(const sf::Vector2i &point) const {
		return window.mapPixelToCoords(point);
	}

	template<typename... Types>
	void event(Types&... widgets) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
				case (sf::Event::Closed): {
					on_close();
				} break;
				case (sf::Event::Resized): {
					ctx.resize(window.getSize());
				} break;
				case (sf::Event::MouseMoved): {
					mouse_pos = window.mapPixelToCoords({ event.mouseMove.x, event.mouseMove.y });
				} break;

				default: break;
			}
			(widgets.event(event, window), ...);
		}
	}

	template<typename... Types>
	void draw(Types&... widgets) {
		window.clear(ctx.config().background().color);
		(widgets.draw(ctx), ...);
		ctx.set("u_resolution", sf::Glsl::Vec2{ window.getSize() });
		ctx.set("u_mouse", sf::Glsl::Vec2{ mouse_pos });
		ctx.set("u_time", clock.getElapsedTime().asSeconds());
		ctx.draw();
		window.display();
	}
	template<typename... Types>
	void update(Types&... widgets) {
		(widgets.update(), ...);
	}
	
	template<class T>
	void updates(T& widget) {
		widget.update();
	}

	template<typename... Types>
	void start(Types&... widgets) {
		ctx.resize(window.getSize());
		(widgets.start(), ...);
	}

	template<typename... Types>
	void loop(Types&... widgets) {
		start<Types...>(widgets...);
		while (window.isOpen()) {
			event<Types...>(widgets...);
			draw<Types...>(widgets...);
			update<Types...>(widgets...);
		}
	}

	void on_close() { window.close(); }

	Context* get_context() { return &this->ctx; }
};

};

#endif