#include <Python.h>
#include "primes.h"
#include "limits.h"

PyObject* py_below(uint64_t num)
{
	PyObject* list = NULL;
	uint8_t* sieve = NULL;
	Py_ssize_t sieve_len = sieve_index_of(num) + 1;

	if(num < 2)
	{
		list = PyList_New(0);
		return list;
	}

	errno = 0;
	int not_ok = eratos_sieve(num, &sieve);
	if(not_ok)
	{
		//TODO: Throw an exception based on errno
		goto error;
	}

	Py_ssize_t esti = estimatehi(num);
	if(esti > SSIZE_MAX)
	{
		//Overflow
		PyErr_SetString(PyExc_Exception, "Oops?");
		goto error;
	}
	list = PyList_New(esti);
	if(!list)
		goto error;

	Py_ssize_t i = 0, k = 0;
	for(; i < sieve_len; ++i)
	{
		if(sieve[i] == MaybePrime)
		{
			PyObject* item = PyLong_FromUnsignedLongLong(sieve_value_at(i));
			PyList_SET_ITEM(list, k, item);
			++k;
		}
	}
	free(sieve);

	/*We over-estimated the size, so let's cut that flab out.*/
	PyList_SetSlice(list, k, PyList_Size(list), NULL);

	/*
		One is not prime, it's a unit. Two IS prime, but excluded from our sieve.
		This is rather convient: let's just replace 1 with 2, but only if there's a 1 to replace.
	*/
	if(PyList_Size(list) > 0)
	{
		PyObject* two = PyLong_FromUnsignedLongLong(2);
		int res = PyList_SetItem(list, 0, two);
		if(res)
		{
			//do something meaningful
		}
	}

	return list;

error:
	Py_XDECREF(list);
	if(PyErr_Occurred())
		return NULL;
	else
	{
		Py_RETURN_NONE;
	}
}
