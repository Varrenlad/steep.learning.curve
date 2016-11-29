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
			(temp->obj)->Getter(st);
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
		throw EXC_WR_FAIL;
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
			obj->Setter(st);
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
			case 'b': {
				obj = new Background(hdc, hwnd);
				break;
			}
			case 'c': {
				obj = new ContourTrapezoid(hdc, hwnd);
				break;
			}
			case 'f': {
				obj = new FilledTrapezoid(hdc, hwnd);
				break;
			}
			case 'p': {
				obj = new PartialTrapezoid(hdc, hwnd);
				break;
			}
			default:
				obj = nullptr;
				break;
			}
			if (obj) {
				obj->Setter(st);
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
	else throw EXC_CANT_CONTAIN;
}

template <class T> T* Container <T> ::PopRem() {
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

template <class T> void Container <T> ::Draw(size_t i) const {
	data *temp;
	if (i >= count)
		return;
	temp = first;
	while (i) {
		temp = temp->next;
		--i;
	}
	temp->obj->Draw();
}

template <class T> size_t Container<T> ::Size() const {
	return count;
}

template class Container<Drawable>;
#ifdef TYPES
template class Container<Background>;
template class Container<ContourTrapezoid>;
template class Container<FilledTrapezoid>;
template class Container<PartialTrapezoid>;
#endif