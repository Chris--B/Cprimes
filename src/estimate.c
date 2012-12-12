#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif

double estimatelo(double num)
{
	return num;
}
double estimatehi(double num)
{
	return (num / log(num) * (1 + 1.2762 / log(num)) + 1);
}

#ifdef __cplusplus
}
#endif