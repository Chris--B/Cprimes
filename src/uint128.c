#include "uint128.h"

/*
	This was a fun exercise, but I'm not sure I want to use it. Leaving it here for a bit.	
*/

const char* uint128_to_str(uint128_t n)
{
	// 2^128 - 1 has 39 digits, plus one for NUL
	static char out_buffer [40];
	uint128_t ten_power = 1;
	int zero_offset = 0;

	//10^39
	for(int i = 0; i < 38; i++)
	{
		ten_power *= 10;
	}

	for(int i = 0; i < 39; i++)
	{
		out_buffer[i] = '0';
		while(n >= ten_power)
		{
			n -= ten_power;
			out_buffer[i]++;
		}
		ten_power /= 10;
	}
	//don't return leading zeroes
	while(out_buffer[zero_offset] == '0' && zero_offset < 38)
	{
		zero_offset++;
	}
	out_buffer[39] = '\0';
	return out_buffer + zero_offset;
}