#pragma once
#include "commondata.h"
template <class FilledTrapezoid> class Container {
public:
	Container();
	~Container();
	void Save(std::ofstream &st);
	void Load(std::ifstream &st);
	void FrontPush(FilledTrapezoid &obj);
	void Push(FilledTrapezoid &obj);
	FilledTrapezoid& Pop();
	void Show(bool direction);
	FilledTrapezoid *Search(POINT p);
	FilledTrapezoid *Search(COLORREF c);
private:
	struct data {
		data *prev = nullptr;
		FilledTrapezoid &obj;
		data *next = nullptr;
	};
	size_t count;
	data *first = nullptr;
	data *last;
};

template <class ContourTrapezoid> class Container {
public:
	Container();
	~Container();
	void Save(std::ofstream &st);
	void Load(std::ifstream &st);
	void FrontPush(ContourTrapezoid &obj);
	void Push(ContourTrapezoid obj);
	ContourTrapezoid& Pop();
	void Show(bool direction);
	ContourTrapezoid *Search(POINT p);
	ContourTrapezoid *Search(COLORREF c);
private:
	struct data {
		data *prev = nullptr;
		ContourTrapezoid &obj;
		data *next = nullptr;
	};
	size_t count;
	data *first = nullptr;
	data *last;
};

template <class Drawable> class Container {
public:
	Container();
	~Container();
	void Save(std::ostream &st);
	void Load(std::istream &st);
	void FrontPush(Drawable &obj);
	void Push(Drawable obj);
	Drawable& Pop();
	void Show(bool direction);
	Drawable *Search(POINT p);
	Drawable *Search(COLORREF c);
private:
	struct data {
		data *prev = nullptr;
		Drawable &obj;
		data *next = nullptr;
	};
	size_t count = 0;
	data *first = nullptr;
	data *last;
};