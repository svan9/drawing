#ifndef NAN_UTILS_HPP
#define NAN_UTILS_HPP

#include <algorithm>
#include <glm/glm.hpp>
#include <Windows.h>

namespace Nan {

	struct ColorRGB {
		int r, g, b;
	};

	struct ColorHSL {
		float h, s, l;
	};

	union Color {
		ColorRGB rgb;
		ColorHSL hsl;
	};
	
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

	template<typename T>
	T rounded_block(T min, T val, T max) {
		if (val < min) {return max;}
		if (val > max) {return min;}
		return val;
	}

	float hueToRgb(float p, float q, float t) {
		if (t < 0.0f) t += 1.0f;
		if (t > 1.0f) t -= 1.0f;
		if (t < 1.0f/6.0f) return p + (q - p) * 6.0f * t;
		if (t < 1.0f/2.0f) return q;
		if (t < 2.0f/3.0f) return p + (q - p) * (2.0f/3.0f - t) * 6.0f;
		return p;
	}

	ColorRGB hsl_to_rgb(float h, float s, float l) {
		float r, g, b;
		if (s == 0) {
			r = g = b = l; // achromatic
		} else {
			const float q = l < 0.5 ? l * (1 + s) : l + s - l * s;
			const float p = 2 * l - q;
			r = Nan::hueToRgb(p, q, h + 1.0f/3.0f);
			g = Nan::hueToRgb(p, q, h);
			b = Nan::hueToRgb(p, q, h - 1.0f/3.0f);
		}
		return ColorRGB{static_cast<int>(r*255),static_cast<int>(g*255),static_cast<int>(b*255)};
	}

	ColorHSL rgb_to_hsl(float r, float g, float b) {
		r /= 255;g /= 255; b /= 255;
		float vmax = std::max({r, g, b});
		float vmin = std::min({r, g, b});
		float h, s, l;
		h = s = l = (vmax + vmin) / 2;
		if (vmax == vmin) { return {0, 0, l}; }
		float d = vmax - vmin;
		s = l > 0.5 ? d / (2 - vmax - vmin) : d / (vmax + vmin);
		if (vmax == r) h = (g - b) / d + (g < b ? 6 : 0);
		if (vmax == g) h = (b - r) / d + 2;
		if (vmax == b) h = (r - g) / d + 4;
		h /= 6;
		return {h, s, l};
	}


	void HideConsole()
	{
			::ShowWindow(::GetConsoleWindow(), SW_HIDE);
	}
	void ShowConsole()
	{
			::ShowWindow(::GetConsoleWindow(), SW_SHOW);
	}
	bool IsConsoleVisible()
	{
			return ::IsWindowVisible(::GetConsoleWindow()) != FALSE;
	}
}
#endif