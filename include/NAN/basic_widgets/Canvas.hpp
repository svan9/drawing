#ifndef NAN_CANVAS_WIDGET_HPP
#define NAN_CANVAS_WIDGET_HPP

#include <SFML/Graphics.hpp>
#include <NAN/Window.hpp>
#include <NAN/Context.hpp>
#include <NAN/Widget.hpp>
#include <NAN/utils.hpp>
#include <NAN/tools/Bounds.hpp>
#include <NAN/tools/Mouse.hpp>
#include <NAN/basic_widgets/HSLColorPicker.hpp>
#include <NAN/basic_widgets/Slider.hpp>
#include <NAN/tools/Keyboard.hpp>
#include <iostream>
#include <glm/glm.hpp>

#include <Windows.h>

namespace Nan {

class Canvas:
	public Widget,
	public Tools::Mouse,
	public Tools::Keyboard {
private:
	// Tools::Boundu canvas_size;
	sf::RenderTexture rt;
	sf::RenderTexture buffer;
	sf::Clock clock;
	float radius = 5.0f;
	sf::Color color = sf::Color::Black;
	sf::Color bgc = sf::Color(0x22223bff);
	sf::Color alt_color = sf::Color::White;
	sf::Vector2f circle;
	glm::vec2 last;
	Nan::HSLColorPicker* picker;
	Nan::Slider* opacity_slider = nullptr;
	Nan::Slider* size_slider = nullptr;
	const float max_size = 100.0f;
public:
	Canvas() {
		config();
	}

	Canvas(Tools::Boundu __bounds) {
		bounds(__bounds);
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
		rt.create(bounds().w, bounds().h);
		rt.setSmooth(true);
		rt.clear(bgc);
		buffer.create(bounds().w, bounds().h);
		buffer.setSmooth(true);
		picker = nullptr;
		ratio_by_height();
		clear();
	}

	void add_picker(Nan::HSLColorPicker* picker) {
		this->picker = picker;
	}

	void set_sliders(Nan::Slider* opacity, Nan::Slider* size) {
		opacity_slider = opacity;
		size_slider = size;
	}

	void add_slider_opacity(Nan::Slider* slider) {
		opacity_slider = slider;
	}

	void add_slider_size(Nan::Slider* slider) {
		size_slider = slider;
		size_slider->set(radius/bounds().w);
	}

	void clear() {
		rt.clear(alt_color);
	}

	void start() { }

	void update() {
		if (picker != nullptr) {
			color = picker->getCurrentColor();
		}
		if (opacity_slider != nullptr) {
			color.a = opacity_slider->get()*255;
		}
		if (size_slider != nullptr) {
			radius = size_slider->get()*max_size;
		}
	}

	void draw(Nan::Context& ctx) {
		ctx.draw(rt, bounds().x, bounds().y);
		if (is_inside(&bounds())) {
			ctx.draw_circle_empty(circle.x, circle.y, radius, 2);
			ctx.hide_cursor();
		} else {
			ctx.show_cursor();
		}
	}

  void on_key_down(Tools::KeyboardEvent& ev) { }

  void on_key_up(Tools::KeyboardEvent& ev) {
		if (is_inside(&bounds()) && ev.kw.control && ev.kw.code == sf::Keyboard::Key::S) {
			save();
		}
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

	void save() {
		sf::Image img = rt.getTexture().copyToImage();
		OPENFILENAMEW ofn;
		WCHAR szFile[260] = { 0 };
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFile;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = L"PNG Files\0*.png\0All Files\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT;

		if (GetSaveFileNameW(&ofn) == TRUE) {
			sf::String filePath(ofn.lpstrFile);
			if (filePath.find(".png") == std::string::npos) {
				filePath += ".png";
			}
			if (!img.saveToFile(filePath)) {
				std::cout << "Failed to save drawing as PNG." << std::endl;
			}
		}
	}

	void drawing(glm::vec2 current) {
		sf::CircleShape crc;
		crc.setFillColor(color);
		crc.setPosition(current.x, current.y);
		crc.setRadius(radius-1);
		crc.setOutlineColor(color);
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

		// sf::Image img = rt.getTexture().copyToImage();
		// sf::Texture texture;
		// texture.create(canvas_size.w, bounds().h);
		// for (int x = 0; x < bounds().w; x++) {
		// 	for (int y = 0; y < bounds().h; y++) {
		// 		sf::Color color = img.getPixel(x, y);
		// 		if (color.a != 0.0f) {
		// 			img.setPixel(x, y, color);
		// 		}
		// 	}
		// }
		// texture.update(img);
		// rt.clear(sf::Color::Transparent);
		// rt.draw(sf::Sprite(texture));
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
		if (!is_inside(&bounds())) return;
		glm::vec2 current(ev.x-bounds().x, ev.y-bounds().y);
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