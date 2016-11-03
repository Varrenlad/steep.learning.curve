#include "container.h"

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

template <class T> void Container <T> ::Save(std::ofstream &st) const {
	data *temp = first;
	temp = first;
	while (temp != nullptr) {
		(temp->obj)->Getter(st);
		temp = temp->next;
	}
	delete temp;
}

template <> void Container <Drawable> ::Save(std::ofstream &st) const {
	data *temp = first;
	st << count << '\n';
	while (temp != nullptr) {
		st << temp->signature;
		temp = temp->next;
	}
	st << '\n';
	temp = first;
	while (temp != nullptr) {
		switch (temp->signature) {
		case 'b':
			(dynamic_cast<Background *> (temp->obj))->Getter(st);
			break;
		case 'c':
			(dynamic_cast<ContourTrapezoid *> (temp->obj))->Getter(st);
			break;
		case 'f':
			(dynamic_cast<FilledTrapezoid *> (temp->obj))->Getter(st);
			break;
		case 'p':
			(dynamic_cast<PartialTrapezoid *> (temp->obj))->Getter(st);
			break;
		default:
			break;
		}
		temp = temp->next;
	}
	delete temp;
}

template <class T> void Container <T> ::Load(std::ifstream &st, HDC hdc, HWND hwnd) {
	T *obj = new T(hdc, hwnd);
	obj->Setter(st);
	this->Push(obj);
}

template <> void Container <Drawable> ::Load(std::ifstream &st, HDC hdc, HWND hwnd) {
	size_t i;
	st >> i;
	st.get();
	char *type = new char[i + 1];
	st.readsome(type, i);
	st.get();
	while (i > count) {
		switch (type[count]) {
		case 'b': {
			Background *obj = new Background(hdc, hwnd);
			obj->Setter(st);
			this->Push(obj);
			break;
		}
		case 'c': {
			ContourTrapezoid *obj = new ContourTrapezoid(hdc, hwnd);
			obj->Setter(st);
			this->Push(obj);
			break;
		}
		case 'f': {
			FilledTrapezoid *obj = new FilledTrapezoid(hdc, hwnd);
			obj->Setter(st);
			this->Push(obj);
			break;
		}
		case 'p': {
			PartialTrapezoid *obj = new PartialTrapezoid(hdc, hwnd);
			obj->Setter(st);
			this->Push(obj);
			break;
		}
		default:
			break;
		}
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

template <class T> void Container <T> ::FrontPush(T *obj) {
	char type = obj->GetType();
	if (!count) {
		first = new data;
		first->obj = obj;
		first->signature = type;
		last = first;
	}
	else {
		data *temp = new data;
		temp->obj = obj;
		temp->signature = type;
		temp->next = first;
		first->prev = temp;
		first = temp;
	}
	++count;
}

template <class T> T& Container <T> ::Pop() {
	if (count)
		return *(last->obj);
	else throw EXC_NOT_IN_DC;
}

template <class T> T* Container <T> ::PopRem() {
	T* retval = last->obj;
	last = last->prev;
	delete last->next;
	last->next = nullptr;
	return retval;
}

template <class T> void Container <T> ::Show(bool direction) const {
	std::cout << count << " items in container\n";
	data *temp;
	switch (direction) {
	case true:
		temp = first;
		while (temp != nullptr) {
			std::cout << temp->obj->GetType();
			temp->obj->Getter(std::cout);
			temp = temp->next;
		}
		break;
	default:
		temp = last;
		while (temp != nullptr) {
			std::cout << temp->obj->GetType();
			temp->obj->Getter(std::cout);
			temp = temp->prev;	
		}
		break;
	}
}

template <class T> list *Container <T> ::Search(POINT p) {
	list *retval = new list, *templ = retval;
	int i = 0;
	data *temp = first;
	while (temp != nullptr) {
		if (temp->obj->PointInside(p)) {
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
		if (temp->obj->HasColour(c)) {
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
	return *(temp->obj);
}

template <class T> void Container <T> ::Draw(size_t i) const {
	data *temp;
	if (i > count)
		return;
	temp = first;
	while (temp != nullptr) {
		--i;
		if (!i)
			temp->obj->Draw();
		temp = temp->next;
	}
}

template <class T> int Container<T> ::Size() {
	return count;
}

template class Container<Drawable>;
#ifdef TYPES
template class Container<Background>;
template class Container<ContourTrapezoid>;
template class Container<FilledTrapezoid>;
template class Container<PartialTrapezoid>;
#endif