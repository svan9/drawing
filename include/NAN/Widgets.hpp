// #ifndef NAN_WIDGETS_HPP
// #define NAN_WIDGETS_HPP

// #include <SFML/Graphics.hpp>
// #include <NAN/Context.hpp>
// #include <NAN/tools/Mouse.hpp>

// namespace Nan {

// template<typename T, bool>
// struct WidgetsWrapper;

// template<typename T, bool>
// struct WidgetsWrapper<T, std::is_empty_v<T>> {

// };

// template<typename T>
// struct WidgetsWrapper<T, !std::is_empty_v<T>> {
// 	[[no_unique_address]] T* data = nullptr;
	
// 	T* getData() { return data; }
// 	void setData(T* _data) { data = _data; }
// };

// template<typename Head, typename ...Tail>
// struct Widgets:
// 	: WidgetsWrapper<Head>
// 	, Widgets<Tail...>
// {
	
// 	void push(T* _data) {
// 		if (getData() == nullptr) { setData(_data); } 
// 		else { _next->push(_data); }
// 	}
	
// 	void push(void* data) {
// 		push(static_cast<T*>(data));
// 	}


// 	Widgets<NT...>* next() { return _next; }

// 	// void start() {
// 	// 	T* data = getData();
// 	// 	data->start();
// 	// 	Widgets<NT...>* __next = next();
// 	// 	__next->start();
// 	// }

// 	// void update() {
// 	// 	T* data = getData();
// 	// 	data->update();
// 	// 	Widgets<NT...>* __next = next();
// 	// 	__next->update();
// 	// }

// 	// void draw(Nan::Context& ctx) {
// 	// 	T* data = getData();
// 	// 	data->draw(ctx);
// 	// 	Widgets<NT...>* __next = next();
// 	// 	__next->draw(ctx);
// 	// }

// 	// void event(sf::Event &ev, sf::RenderWindow &ptw) {
// 	// 	T* data = getData();
// 	// 	data->draw(ev, ptw);
// 	// 	Widgets<NT...>* __next = next();
// 	// 	__next->event(ev, ptw);
// 	// }
// };


// }
// #endif