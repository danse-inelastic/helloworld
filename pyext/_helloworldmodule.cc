// -*- C++ -*-

#include <Python.h>
#include "bindings.h"

char pyhelloworld_module__doc__[] = "";

// Initialization function for the module (*must* be called init_helloworld)
extern "C"
void
init_helloworld()
{
  // create the module and add the functions
  PyObject * m = Py_InitModule4
    ("_helloworld", pyhelloworld_methods,
     pyhelloworld_module__doc__, 0, PYTHON_API_VERSION);

  // get its dictionary
  PyObject * d = PyModule_GetDict(m);

  // check for errors
  if (PyErr_Occurred()) {
    Py_FatalError("can't initialize module helloworld");
  }

  // install the module exceptions
  pyhelloworld_runtimeError = PyErr_NewException("helloworld.runtime", 0, 0);
  PyDict_SetItemString(d, "RuntimeException", pyhelloworld_runtimeError);
  
  return;
}

// End of file
