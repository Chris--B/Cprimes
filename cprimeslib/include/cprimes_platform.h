#pragma once

#ifndef CPRIMES_EXPORT
	#if _WIN32
		#if CPRIMES_BUILDING_DLL
				#define CPRIMES_EXPORT __declspec(dllexport)
		#else
				#define CPRIMES_EXPORT __declspec(dllimport)
		#endif
	#else
		#define CPRIMES_EXPORT
	#endif
#endif

#if WIN32
	#define _CRT_SECURE_NO_WARNINGS 1
#endif
