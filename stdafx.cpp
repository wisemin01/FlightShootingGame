#include "DXUT.h"

int randomNumber(int min, int max)
{
	random_device rn;
	mt19937_64 rnd(rn());

	uniform_int_distribution<int> range(min, max);

	return range(rnd);
}

TCHAR* StringToTCHAR(string& s)
{
	const char* all = s.c_str();
	int len = 1 + strlen(all);
	wchar_t* t = new wchar_t[len];
	if (NULL == t) throw std::bad_alloc();
	mbstowcs(t, all, len);
	return (TCHAR*)t;
}

float FloatSquare(float f) {
	return f * f;
}