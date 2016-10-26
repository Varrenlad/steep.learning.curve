#include "container.h"
template <class Type> Container <Type> ::Container() {
}

template <class Type> Container <Type> ::~Container() {
	temp *data;
	while (first != nullptr) {
		data = first->next;
		delete first;
		first = data;
	}
}

template <class Type> void Container <Type> ::Save(std::ofstream &st) {
	data *temp = first;
	while (temp != nullptr) {
		temp->Getter(st);
		temp = temp->next;
	}
}

template <class Type> void Container <Type> ::Load(std::ifstream &st) {
	data *temp = first;
	while (temp != nullptr) {
		temp->Setter(st);
		temp = temp->next;
	}
}

template <class Type> void Container <Type> ::Push(Type &obj) {
	last->next = new data;
	last->obj = obj;
	last = last->next;
	count += 1;
}

template <class Type> void Container <Type> ::FrontPush(Type &obj) {
	temp = new data;
	temp->obj = obj;
	temp->next = first;
	first = temp;
	count += 1;
}

template <class Type> Type& Container <Type> ::Pop() {
	return last->obj;
}

template <class FilledTrapezoid> void Container <FilledTrapezoid> ::Show(bool direction) {
	std::cout << count << " items in container";
	data *test;
	switch (direction) {
	case true:
		temp = first;
		while (temp != nullptr) {
			temp->Getter(std::cout);
			temp = temp->next;
		}
	case false:
		temp = last;
		while (temp != nullptr) {
			temp->Getter(std::cout);
			temp = temp->prev;	
		}
	}
}

template <class FilledTrapezoid> FilledTrapezoid* Container <FilledTrapezoid> ::Search(POINT p) {

}

template <class FilledTrapezoid> FilledTrapezoid* Container <FilledTrapezoid> ::Search(COLORREF c) {

}

template <class ContourTrapezoid> void Container <ContourTrapezoid> ::Show(bool direction) {

}

template <class ContourTrapezoid> ContourTrapezoid* Container <ContourTrapezoid> ::Search(POINT p) {

}

template <class ContourTrapezoid> ContourTrapezoid* Container <ContourTrapezoid> ::Search(COLORREF c) {

}

template <class Drawable> void Container <Drawable> ::Show(bool direction) {

}

template <class Drawable> Drawable* Container <Drawable> ::Search(POINT p) {

}

template <class Drawable> Drawable* Container <Drawable> ::Search(COLORREF c) {

}