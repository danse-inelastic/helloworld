// -*- C++ -*-
// 

#include <Python.h>

#include "hello.h"
#include "helloworld/hello.h"

// hello

char pyhelloworld_hello__doc__[] = "";
char pyhelloworld_hello__name__[] = "hello";


PyObject * pyhelloworld_hello(PyObject *, PyObject * args)
{
    char * t;
    int ok = PyArg_ParseTuple(args, "s:initialize", &t);
    if (!ok) {
        return 0;
    }

    hello(t);
    
    Py_RETURN_NONE;
}
    
// End of file
