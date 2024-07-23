#ifndef NAN_UTILS_HPP
#define NAN_UTILS_HPP

namespace Nan {
	
	int abs_inn(int i) {
		return i < 0 ? 0: i;
	}

	int block(int min, int val) {
		return val < min ? min: val;
	}

	template<typename T>
	T block(T min, T val, T max) {
		if (val < min) {return min;}
		if (val > max) {return max;}
		return val;
	}

}
#endif