/*
	http://stackoverflow.com/a/1739265
	Oct 12, 2012
*/
#ifdef WIN32
#include <windows.h>

static LARGE_INTEGER PCFreq;
static LARGE_INTEGER CounterStart;

//TODO: Better error handling
int startTimer()
{
	return (QueryPerformanceFrequency(&PCFreq)
	 && QueryPerformanceCounter(&CounterStart));
}

double getTimer()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return (double)(li.QuadPart - CounterStart.QuadPart) / PCFreq.QuadPart;
}

#else
//TODO: Linux / Unix support
#error "No support for nonWindows. Try winelib."
#endif