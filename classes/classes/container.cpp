#include "container.h"
; //WHAT?!
template <class T> Container <T> ::Container() {
	count = 0;
}

template <class T> Container <T> ::~Container() {
	data *temp = nullptr;
	while (first != nullptr) {
		temp = first->next;
		delete first;
		first = temp;
	}
}

template <class T> void Container <T> ::Save(std::ofstream &st) {
	data *temp = first;
	while (temp != nullptr) {
		temp->obj.Getter(st);
		temp = temp->next;
	}
}

template <class T> void Container <T> ::Load(std::ifstream &st) {
	data *temp = first;
/*	if()
	while (st.peek() != EOF) {
		try {
			temp->obj = new T;
			temp->obj.Setter(st);
			temp = temp->next;
		}
		catch (int e) {
			throw;
		}
	}*/
}

template <class T> void Container <T> ::Push(T &obj) {
	if (!count) {
		first = new data(obj);
		last = first;
	}
	else {
		last->next = new data(obj);
		last->next->prev = last;
		last = last->next;
	}
	++count;
}

template <class T> void Container <T> ::FrontPush(T &obj) {
	if (!count) {
		first = new data(obj);
		last = first;
	}
	else {
		data *temp = new data(obj);
		temp->next = first;
		first->prev = temp;
		first = temp;
	}
	++count;
}

template <class T> T& Container <T> ::Pop() {
	return last->obj;
}

template <class T> T& Container <T> ::PopRem() {
	T& temp = last->obj;
	--count;
	delete last;
	return temp;
}

template <class T> void Container <T> ::Show(bool direction) const {
	std::cout << count << " items in container\n";
	data *temp;
	switch (direction) {
	case true:
		temp = first;
		while (temp != nullptr) {
			temp->obj.Getter(std::cout);
			temp = temp->next;
		}
	case false:
		temp = last;
		while (temp != nullptr) {
			temp->obj.Getter(std::cout);
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

template <class T> T& Container <T> ::GetElement(size_t i) const {
	size_t iter = 0;
	if (i >= count)
		throw EXC_CANT_CONTAIN;
	data *temp = first;
	while (iter != i) {
		temp = temp->next;
		++iter;
	}
	return temp->obj;
}

template class Container<Drawable>;
template class Container<Background>;
template class Container<ContourTrapezoid>;
template class Container<FilledTrapezoid>;