#ifndef CNTR
#define CNTR
#include "background.h"
#include "filledtrapezoid.h"
#include "contourtrapezoid.h"
#include "partialtrapezoid.h"

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
	void Save(std::ofstream &st) const;
	void Load(std::ifstream &st, HDC hdc, HWND hwnd);
	void FrontPush(T *obj);
	void Push(T *obj);
	list *Search(POINT p);
	list *Search(COLORREF c);
	T& Pop();
	T& GetElement(size_t i) const;
	T* PopRem();
	void Show(bool direction) const;
	~Container();
};
#include "container.cpp"
#endif

