#pragma once
#include "commondata.h"
#include "filledtrapezoid.h"

class FilledTrapezoid_Proxy {
	friend class PartialTrapezoid;
	explicit FilledTrapezoid_Proxy(FilledTrapezoid &to_proxify) :
		proxified(to_proxify) {};
	void UpdateColour(COLORREF newc) {
		proxified.UpdateColour(newc);
	}
	POINT& GetPoint(size_t i) {
		return proxified.GetPoint(i);
	}
	bool LoadP(std::istream &st) const {
		return proxified.LoadP(st);
	}
	void SaveP(std::ostream &st) const {
		return proxified.SaveP(st);
	}
	FilledTrapezoid& proxified;
};