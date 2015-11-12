// -*- C++ -*-
// 

#include <Python.h>

#include "bindings.h"

// the method table
struct PyMethodDef pyhelloworld_methods[] = {

  // hello
  {pyhelloworld_hello__name__, pyhelloworld_hello,
   METH_VARARGS, pyhelloworld_hello__doc__},

  // copyright
  {pyhelloworld_copyright__name__, pyhelloworld_copyright,
   METH_VARARGS, pyhelloworld_copyright__doc__},

  // Sentinel
  {0, 0}
};

// End of file
