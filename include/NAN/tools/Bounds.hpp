#ifndef NAN_TOOLS_BOUNDS_HPP 
#define NAN_TOOLS_BOUNDS_HPP 

namespace Nan {
namespace Tools {
	template<typename T>
	class Bound {
	public:
		T x, y, w, h;

		Bound() { x = 0; y = 0; w = 0; h = 0; }

		Bound(T _x, T _y, T _w, T _h) {
			x = _x; y = _y; w = _w; h = _h;
		}
	};
	
	typedef Bound<unsigned> Boundu;
};
};

#endif