#ifndef NAN_CONTAINER_WIDGET_HPP
#define NAN_CONTAINER_WIDGET_HPP

#include <SFML/Graphics.hpp>
#include <NAN/Window.hpp>
#include <NAN/Context.hpp>
#include <NAN/Widget.hpp>
#include <NAN/utils.hpp>
#include <NAN/tools/Bounds.hpp>
#include <NAN/tools/Mouse.hpp>
#include <NAN/basic_widgets/HSLColorPicker.hpp>
#include <NAN/interfaces/Reposable.hpp>
#include <NAN/tools/Keyboard.hpp>
#include <iostream>
#include <concepts>
#include <vector>
#include <glm/glm.hpp>

#include <Windows.h>

namespace Nan {

class Container:
public Reposable {
public:

enum FlexType: 
	unsigned char {
		Column, Row
};

enum StaticType:
	unsigned char {
		NONE 	= 0b00000000,
		X 		= 0b00000001,
		Y 		= 0b00000010,
		XY 		= 0b00000011,
		W 		= 0b00000100,
		XW 		= 0b00000101,
		YW 		= 0b00000110,
		XYW 	= 0b00000111,
		H 		= 0b00001000,
		XH 		= 0b00001001,
		XYH 	= 0b00001011,
		WH 		= 0b00001100,
		HWH 	= 0b00001101,
		YWH 	= 0b00001110,
		HYWH 	= 0b00001111,
};

typedef struct {

typedef std::function<Tools::Boundu&(Tools::Boundu)> setter;
typedef std::function<Tools::Boundu&(void)> getter;

typedef Tools::Boundu&(*c_setter)(Tools::Boundu);
typedef Tools::Boundu&(*c_getter)();

	setter set_bounds;
	getter get_bounds;
	void* object;
} Type;

enum AlignType:
	unsigned char {
		FLOATING, LEFT, RIGHT, CENTER, TOP, BOTTOM
};


// typedef struct {

// typedef Tools::Boundu(*getter)();
// typedef void(*setter)(Tools::Boundu);

// 	getter get_bounds;
// 	setter set_bounds;
// 	void* object;
// } Type;

private:
	Tools::Boundu bounds;
	FlexType flex_type = FlexType::Column;
	std::vector<Type> _list;
	StaticType static_wall = StaticType::NONE;
	AlignType align = AlignType::FLOATING;
	float margin = 5.0f;
public:
	Container() { }
	Container(FlexType flex) { flex_type = flex; }
	Container(Tools::Boundu __bounds) { bounds = __bounds; }
	Container(Tools::Boundu __bounds,	FlexType flex) { bounds = __bounds; flex_type = flex; }

	void reflex(FlexType flex) { flex_type = flex; }

	void wall(StaticType __wall) { static_wall = __wall; }

	void resize(float width, float height) {
		bounds.w = width;
		bounds.h = height;
	}
	
	void rescale(float width, float height) {
		bounds.w *= width;
		bounds.h *= height;
	}

	void repos(float x, float y) {
		bounds.x += x;
		bounds.y += y;
	}

	Tools::Boundu& set_bounds(Tools::Boundu __bounds) {
		bounds = __bounds;
		return bounds; 
	}
	
	Tools::Boundu& get_bounds() {
		return bounds; 
	}

	template<typename T> 
		requires std::derived_from<T, Widget>
	void add(T& object) {

		Type __t;
		typedef Nan::Tools::Boundu &(Widget::*_getter_t)();
		_getter_t __getter = &Widget::bounds;
		typedef Nan::Tools::Boundu &(Widget::*_setter_t)(Nan::Tools::Boundu);
		_setter_t __setter = &Widget::bounds;
		__t.get_bounds = std::bind(__getter, &object);
		__t.set_bounds = std::bind(__setter, &object, std::placeholders::_1);
		__t.object = static_cast<void*>(&object);
		_list.push_back(__t);
	}

	void add_container(Container& object) {
		Type __t = {0};
		__t.get_bounds = std::bind(&Container::get_bounds, &object);
		__t.set_bounds = std::bind(&Container::set_bounds, &object, std::placeholders::_1);
		__t.object = static_cast<void*>(&object);
		_list.push_back(__t);
	}

	void update() {
		float pos = 0.0f;
		for (Type& __t: _list) {
			Tools::Boundu bound = __t.get_bounds();
			// if (flex_type == FlexType::Row) {
			// 	bound.x = margin + bounds.x;
			// 	bound.w = Nan::min(bound.w, margin-bounds.w);
			// 	bound.y = margin + pos;
			// 	bound = __t.set_bounds(bound);
			// 	pos += bound.h;
			// }
			// else if (flex_type == FlexType::Column) {
			// 	bound.y = margin + bounds.y;
			// 	bound.h = Nan::min(bound.h, margin-bounds.h);
			// 	bound.x = margin + pos;
			// 	bound = __t.set_bounds(bound);
			// 	pos += bound.w;
			// }
		}
	}
	
};

}
#endif