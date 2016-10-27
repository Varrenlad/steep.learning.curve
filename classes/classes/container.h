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
	list *Search(POINT p);
	list *Search(COLORREF c);
	T& Pop();
	T& GetElement(int i) const;
	T PopRem();
	void Show(bool direction) const;
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

/*
template <> class Container<FilledTrapezoid> {
public:
	//void Save(std::ofstream &st);
	//void Load(std::ifstream &st);
	//FilledTrapezoid& Pop();
	int Search(POINT p) {
		std::cout << "Base container doesn't support save/load functions\n";
	};
	int Search(COLORREF c) {};
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
	int Search(POINT p) {};
	int Search(COLORREF c) {};
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
	int Search(POINT p) {};
	int Search(COLORREF c) {
		std::cout << "Base container doesn't support save/load functions\n";
	};
private:
	struct data {
		data *prev = nullptr;
		Drawable &obj;
		data *next = nullptr;
	};
};*/