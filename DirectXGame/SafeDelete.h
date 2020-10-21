#pragma once

template <class T>
inline void safe_delete(T*& p) {
	delete p;
	p = nullptr;
}
