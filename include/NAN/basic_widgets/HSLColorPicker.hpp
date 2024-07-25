#ifndef NAN_HSLCOLORPICKER_WIDGET_HPP
#define NAN_HSLCOLORPICKER_WIDGET_HPP

#include <SFML/Graphics.hpp>
#include <NAN/Window.hpp>
#include <NAN/Context.hpp>
#include <NAN/Widget.hpp>
#include <NAN/utils.hpp>
#include <NAN/tools/Bounds.hpp>
#include <NAN/tools/Mouse.hpp>
#include <NAN/tools/Keyboard.hpp>
#include <iostream>
#include <glm/glm.hpp>
#include <algorithm>

#include <Windows.h>

namespace Nan {

class HSLColorPicker:
	public Widget,
	public Tools::Mouse,
	public Tools::Keyboard {
private:
	Tools::Boundu bounds;
	sf::RenderTexture rt;

	float width;
	float height;
	float circle_radius;
	float pass;
	float cube_margin;
	const int N = 360*4;
	const float max_a = (N) * (2.0 * M_PI / N);
	float angle = 0;
	float x, y;

	bool in_cube = false;
public:
	HSLColorPicker() {
		config();
	}

	HSLColorPicker(Tools::Boundu bounds) {
		this->bounds = bounds;
		config();
	}
	
	sf::Color getCurrentColor() {
		return calcColor(x, y, angle, height-cube_margin-cube_margin, height-cube_margin-cube_margin);
	}
	sf::Color getColor(float __x, float __y) {
		return calcColor(__x, __y, angle, height-cube_margin-cube_margin, height-cube_margin-cube_margin);
	}

	sf::Color calcColor(float x, float y, float angle, float width, float height) {
		float hue = angle/360;
		if (x == 0 && y == 0) { return sf::Color::White; }
		if (x == width && y == height) { return sf::Color::Black; }
		if (y >= height) { return sf::Color::Black; }
		float hsv_value = 1 - (y / height);
		float hsv_saturation = x / width;
		float lightness = (hsv_value / 2) * (2 - hsv_saturation);
		float saturation = (hsv_value * hsv_saturation) / (1 - glm::abs(2 * lightness - 1));
		Nan::ColorRGB color = Nan::hsl_to_rgb(hue, saturation, lightness);
		return sf::Color(color.r, color.g, color.b);
	}

	sf::Color calcColor(float x, float y, float angle) {
		float hue = angle/360;
		float hsv_value = 1 - (y / bounds.h);
		float hsv_saturation = x / bounds.w;
		float lightness = (hsv_value / 1.8f) * (2 - hsv_saturation);
		float saturation = (hsv_value * hsv_saturation) / (1 - glm::abs(2 * lightness - 1));
		Nan::ColorRGB color = Nan::hsl_to_rgb(hue, saturation, lightness);
		return sf::Color(color.r, color.g, color.b);
	}

	sf::Color calcColor(float angle) {
		Nan::ColorRGB color = Nan::hsl_to_rgb(angle, 1.0f, 0.5f);
		return sf::Color(color.r, color.g, color.b);
	}


	void config() {
		sf::ContextSettings settings;
		settings.antialiasingLevel = 8;
		rt.create(bounds.w, bounds.h);
		rt.setSmooth(true);
		width = bounds.w;
		height = bounds.h;
		circle_radius = 0.09*height;
		pass = 5;
		cube_margin = 0.20*height+(circle_radius/3)+pass;
		x = static_cast<float>(bounds.w);
		x = static_cast<float>(bounds.y);
	}

	void start() { }
	void update() { }

	void draw(Nan::Context& ctx) {
		rt.clear(sf::Color::Transparent);
		drawing();
		ctx.draw(rt, bounds.x, bounds.y);
		ctx.draw_circle_empty(x+bounds.x+cube_margin, y+bounds.y+cube_margin, 5, 2);
		ctx.draw_circle(x+bounds.x+cube_margin-5, y+bounds.y+cube_margin-5, 5, getCurrentColor());
	}

  void on_key_down(Tools::KeyboardEvent& ev) {}

  void on_key_up(Tools::KeyboardEvent& ev) { }

	void on_mouse_up(Tools::MouseEvent& ev) {
		in_cube = false;
	}
	void on_mouse_move(Tools::MouseEvent& ev) {	}

	void drawing() {
		float kh2 = height-cube_margin-cube_margin;
		sf::Texture texture;
		texture.create(width, height);
		sf::Image img;
		img.create(width, height, sf::Color::Transparent);
		int margin;
		for (int xx = 0; xx < kh2; xx++) {
			for (int yy = 0; yy < kh2; yy++) {
				sf::Color color = getColor(xx, yy);
				img.setPixel(xx+cube_margin, yy+cube_margin, color);
			}
		}

		texture.update(img);
		rt.draw(sf::Sprite(texture));

		float _height2 = height / 2.0f;

		for (int i = 0; i < N; i++) {
			float a = i * (2.0 * M_PI / N);
			sf::Color color = calcColor(std::fmod((a/max_a) - (180.0f/360.0f), 1.0f));

			float x1 = _height2*cos(a)+_height2;
			float y1 = _height2*sin(a)+_height2;

			float x2 = (_height2-circle_radius)*cos(a)+_height2;
			float y2 = (_height2-circle_radius)*sin(a)+_height2;
			
			Nan::Context::draw_line(rt, x1, y1, x2, y2, color);	
		}
	}

	void on_wheel_scroll(Tools::MouseEvent& ev) {
	}

	void on_mouse_down(Tools::MouseEvent& ev) {
		if (!is_inside(bounds)) return;
		if (updateXY(ev) && !in_cube) updateAngle(ev);
	}

	void on_mouse_hold(Tools::MouseEvent& ev) {
		if (!is_inside(bounds)) return;
		if (updateXY(ev) && !in_cube) updateAngle(ev);
	}

	bool updateXY(Tools::MouseEvent& ev) {
		float xx = bounds.x;
		float yy = bounds.y;
		float margin = cube_margin;
		
		if (!in_cube && !is_inside_mm(
			xx+margin-pass,
			yy+margin-pass,
			height+xx-margin+pass,
			height+yy-margin+pass
		)) {
			return true;
		}

		x = Nan::block(margin, ev.x-xx, height-margin)-margin;
		y = Nan::block(margin, ev.y-yy, height-margin)-margin;

		in_cube = true;
		return false;
	}
	
	void updateAngle(Tools::MouseEvent& ev) {
		float width = bounds.w;
		float height = bounds.h;

		sf::Color color = rt.getTexture().copyToImage().getPixel(ev.x-bounds.x, ev.y-bounds.y);
		if (color.a != 0xFF) { return; }
		Nan::ColorHSL hsl = Nan::rgb_to_hsl(color.r, color.g, color.b);

		this->angle = hsl.h*360;
	}
	
	void event(sf::Event& ev, sf::RenderWindow& ptw) {
		provide_mouse(ev, ptw);
		provide_key(ev, ptw);
	}
};

}
#endif