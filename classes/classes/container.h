#pragma once
#include "commondata.h"
#include "filledtrapezoid.h"
#include "contourtrapezoid.h"
#include "drawable.h"

template <typename T> class Container {
public:
	Container();
	~Container();
	void Save(std::ofstream &st);
	void Load(std::ifstream &st);
	void FrontPush(T &obj);
	void Push(T &obj);
	T *Search(POINT p);
	T *Search(COLORREF c);
	T& Pop();
	T PopRem();
	void Show(bool direction);
private:
	struct data {
		data *prev = nullptr;
		T &obj;
		data *next = nullptr;
	};
	size_t count;
	data *first = nullptr;
	data *last;
};

template <> class Container<FilledTrapezoid> {
public:
	//void Save(std::ofstream &st);
	//void Load(std::ifstream &st);
	//FilledTrapezoid& Pop();
	FilledTrapezoid *Search(POINT p) {
		std::cout << "Base container doesn't support save/load functions\n";
	};
	FilledTrapezoid *Search(COLORREF c) {};
private:
	struct data {
		data *prev = nullptr;
		FilledTrapezoid &obj;
		data *next = nullptr;
	};
};

template <> class Container<ContourTrapezoid> {
public:
	//void Save(std::ofstream &st);
	//void Load(std::ifstream &st);
	//ContourTrapezoid& Pop();
	ContourTrapezoid *Search(POINT p) {};
	ContourTrapezoid *Search(COLORREF c) {};
private:
	struct data {
		data *prev = nullptr;
		ContourTrapezoid &obj;
		data *next = nullptr;
	};
};

template <> class Container<Drawable> {
public:
	//Drawable& Pop();
	//void Show(bool direction);
	Drawable *Search(POINT p) {};
	Drawable *Search(COLORREF c) {
		std::cout << "Base container doesn't support save/load functions\n";
	};
private:
	struct data {
		data *prev = nullptr;
		Drawable &obj;
		data *next = nullptr;
	};
};