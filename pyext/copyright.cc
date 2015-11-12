// -*- C++ -*-
// 

#include <Python.h>
#include "copyright.h"


// copyright

char pyhelloworld_copyright__doc__[] = "";
char pyhelloworld_copyright__name__[] = "copyright";

static char pyhelloworld_copyright_note[] = 
    "helloworld module: Copyright (c) 2015 Jiao Lin";


PyObject * pyhelloworld_copyright(PyObject *, PyObject *)
{
    return Py_BuildValue("s", pyhelloworld_copyright_note);
}
    
// End of file
