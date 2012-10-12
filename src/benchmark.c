/*
	http://stackoverflow.com/a/1739265
	Oct 12, 2012
*/
#include <inttypes.h>

#ifdef WIN32
#include <windows.h>

static double PCFreq = 0.0;
static uint64_t CounterStart = 0;

int startCounter()
{
	LARGE_INTEGER li;
	if(!QueryPerformanceFrequency(&li))
		return -1;
	PCFreq = li.QuadPart;
	QueryPerformanceCounter(&li);
	CounterStart = li.QuadPart;
	return 0;
}

double getCounter()
{
	LARGE_INTEGER li;
	if(!QueryPerformanceFrequency(&li))
		return -1;
	PCFreq = li.QuadPart;
	QueryPerformanceCounter(&li);
	return (double)(li.QuadPart - CounterStart) / PCFreq;
}
#endif
//TODO: Unix support