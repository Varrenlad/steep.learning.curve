#include "container.h"

template <class T> Container <T> ::Container() {
	first = nullptr;
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

template <class T> void Container <T> ::Save(std::ofstream &st) const {
	data *temp = first;
	try {
		while (temp != nullptr) {
			(temp->obj)->Save(st);
			temp = temp->next;
		}
	}
	catch (int e) {
		throw;
	}
	delete temp;
}

template <> void Container <Drawable> ::Save(std::ofstream &st) const {
	data *temp = first;
	size_t i = count;
	if (st.rdstate() & std::ios::failbit)
		throw EXC_WRITE_FAIL;
	st << count << '\n';
	while (i) {
		st << temp->signature;
		temp = temp->next;
		--i;
	}
	st << '\n';
	temp = first;
	i = count;
	try {
		while (i) {
			switch (temp->signature) {
			case 't':
				(dynamic_cast<Trapezoid *> (temp->obj))->Save(st);
				break;
			case 'r':
				(dynamic_cast<_Rectangle *> (temp->obj))->Save(st);
				break;
			default:
				break;
			}
			temp = temp->next;
			--i;
		}
	}
	catch (int e) {
		throw;
	}
	delete temp;
}

template <class T> void Container <T> ::Load(std::ifstream &st, HDC hdc, HWND hwnd) {
	size_t i;
	st >> i;
	try {
		while (i > count) {
			T *obj = new T(hdc, hwnd);
			obj->Load(st);
			this->Push(obj);
		}
	}
	catch (int e) {
		throw;
	}
}

template <> void Container <Drawable> ::Load(std::ifstream &st, HDC hdc, HWND hwnd) {
	size_t i;
	Drawable *obj;
	st >> i;
	st.get();
	char *type = new char[i + 1];
	st.readsome(type, i);
	st.get();
	try{
		while (i > count) {
			switch (type[count]) { //create object by type
			case 't': {
				obj = new Trapezoid(hdc, hwnd);
				break;
			}
			case 'r': {
				obj = new _Rectangle(hdc, hwnd);
				break;
			}
			default:
				obj = nullptr;
				break;
			}
			if (obj) {
				obj->Load(st);
				this->Push(obj);
			}
		}
	}
	catch (int e) {
		throw;
	}
}

template <class T> void Container <T> ::Push(T *obj) {
	char type = obj->GetType();
	if (!count) {
		first = new data;
		first->obj = obj;
		first->signature = type;
		last = first;
	}
	else {
		last->next = new data;
		last->next->obj = obj;
		last->next->signature = type;
		last->next->prev = last;
		last = last->next;
	}
	++count;
}

template <class T> T* Container <T> ::Pop() {
	if (count) {
		T* retval = last->obj;
		last = last->prev;
		delete last->next;
		last->next = nullptr;
		return retval;
	}
	else throw EXC_CANT_CONTAIN;
}

template <class T> void Container <T> ::Show(bool direction) const {
	std::cout << count << " items in container\n";
	data *temp;
	switch (direction) {
	case true:
		temp = first;
		while (temp != nullptr) {
			std::cout << temp->obj->GetType();
			temp->obj->Save(std::cout);
			temp = temp->next;
		}
		break;
	default:
		temp = last;
		while (temp != nullptr) {
			std::cout << temp->obj->GetType();
			temp->obj->Save(std::cout);
			temp = temp->prev;	
		}
		break;
	}
}

template <class T> T& Container<T> ::operator [](size_t i) const {
	size_t iter = 0;
	if (i >= count) {
		throw EXC_CANT_CONTAIN;
	}
	data *temp = first;
	while (iter != i) {
		temp = temp->next;
		++iter;
	}
	return *(temp->obj);
}

template <class T> size_t Container<T> ::Size() const {
	return count;
}

template class Container<Drawable>;