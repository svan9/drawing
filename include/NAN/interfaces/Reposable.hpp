#ifndef NAN_REPOSABLE_HPP
#define NAN_REPOSABLE_HPP

namespace Nan {

class Window;

class Reposable {
public:
	virtual ~Reposable() {}
protected:
	friend class Window;

	virtual void repos(float x, float y) = 0; 
};

};

#endif