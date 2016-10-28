#ifndef CNTR
#define CNTR
#include "background.h"
#include "filledtrapezoid.h"
#include "contourtrapezoid.h"
#include "drawable.h"

template <class T> class Container {
	struct data {
		data *prev = nullptr;
		T &obj;
		data *next = nullptr;
		data(T &inner) : obj(inner) {};
	};
protected:
	size_t count;
	data *first;
	data *second;
	data *last = nullptr;
public:
	Container();
	~Container();
	void Save(std::ofstream &st);
	void Load(std::ifstream &st);
	void FrontPush(T &obj);
	void Push(T &obj);
	list *Search(POINT p);
	list *Search(COLORREF c);
	T& Pop();
	T& GetElement(size_t i) const;
	T& PopRem();
	void Show(bool direction) const;
}
#include "container.cpp"
#endif

