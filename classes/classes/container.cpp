#include "container.h"

template <typename T> Container <T> ::Container() {
	T* check = new T;
}

template <typename T> Container <T> ::~Container() {
	temp *data;
	while (first != nullptr) {
		data = first->next;
		delete first;
		first = data;
	}
}

template <typename T> void Container <T> ::Save(std::ofstream &st) {
	data *temp = first;
	while (temp != nullptr) {
		temp->Getter(st);
		temp = temp->next;
	}
}

template <typename T> void Container <T> ::Load(std::ifstream &st) {
	data *temp = first;
	while (st.peek() != EOF) {
		try {
			temp->Setter(st);
			temp = temp->next;
		}
		catch (int e);
	}
}

template <typename T> void Container <T> ::Push(T &obj) {
	last->next = new data;
	last->next->prev = last;
	last->obj = obj;
	last = last->next;
	count += 1;
}

template <typename T> void Container <T> ::FrontPush(T &obj) {
	temp = new data;
	temp->obj = obj;
	temp->next = first;
	first->prev = temp;
	first = temp;
	count += 1;
}

template <typename T> T& Container <T> ::Pop() {
	return last->obj;
}

template <typename T> T Container <T> ::PopRem() {
	temp = last->obj;
	delete last;
	return temp;
}

template <typename T> void Container <T> ::Show(bool direction) {
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

template <class T> list *Container <T> ::Search(POINT p) {
	list *retval = new list, *templ = retval;
	int i = 0;
	data *temp = first;
	while (temp != nullptr) {
		if (temp->obj.PointInside(p)) {
			templ->i = i;
			templ->next = new list;
			templ = templ->next;
		}
		++i;
	}
	return retval;
}

template <class T> list *Container <T> ::Search(COLORREF c) {
	list *retval = new list, *templ = retval;
	int i = 0;
	data *temp = first;
	while (temp != nullptr) {
		if (temp->obj.HasColour(c)) {
			templ->i = i;
			templ->next = new list;
			templ = templ->next;
		}
		++i;
	}
	return retval;
}

template <class T> const T& Container <T> ::GetElement(int i) {
	int iter;
	data *temp = first;
	while (iter != i || temp != nullptr) {
		temp = temp->next;
		++i;
	}
	return temp->obj;
}
/*
template <class ContourTrapezoid> ContourTrapezoid* Container <ContourTrapezoid> ::Search(POINT p) {

}

template <class ContourTrapezoid> ContourTrapezoid* Container <ContourTrapezoid> ::Search(COLORREF c) {

}

template <class Drawable> Drawable* Container <Drawable> ::Search(POINT p) {

}

template <class Drawable> Drawable* Container <Drawable> ::Search(COLORREF c) {

}
	*/