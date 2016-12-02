#pragma once
#include "commondata.h"
#include "filledtrapezoid.h"

///Proxy allowes us to keep sanity and disallow use of private 
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
	void Resize(float new_size_x, float new_size_y) {
		proxified.Resize(new_size_x, new_size_y);
	}
	void Rotate(float angle) {
		proxified.Rotate(angle);
	}
	FilledTrapezoid& proxified;
};