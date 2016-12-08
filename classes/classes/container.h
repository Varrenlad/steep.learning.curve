#ifndef CNTR
#define CNTR
#include "trapezoid.h"
#include "rectangle.h"

template <class T> class Container {
	struct data {
		data *prev = nullptr;
		T *obj;
		data *next = nullptr;
		char signature = '0';
	};
protected:
	size_t count;
	data *first;
	data *last = nullptr;
public:
	Container();
	T& operator [](size_t i) const;
	void Save(std::ofstream &st) const;
	void Load(std::ifstream &st, HDC hdc, HWND hwnd);
	void Push(T *obj);
	size_t Size() const;
	T* Pop();
	void Show(bool direction) const;
	~Container();
};
#include "container.cpp"
#endif

