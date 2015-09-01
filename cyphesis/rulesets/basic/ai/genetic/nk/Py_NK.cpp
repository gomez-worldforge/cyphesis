// Cyphesis Online RPG Server and AI Engine
// Copyright (C) 2000-2011 Alistair Riddoch
// Copyright (C) 2015 Johan Ceuppens 
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software Foundation,
// Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA


#include "Py_NK.h"

static void NK_dealloc(PyNK *self)
{
    self->nk.~NK();
    self->ob_type->tp_free(self);
}

static int NK_init(PyNK * self, PyObject * args, PyObject * kwds)
{
    if (!PyInt_Check(args)) {
       PyErr_SetString(PyExc_TypeError, "NK() arguments should a integer");
       return -1;
    }
    int n = (int)args;
    self->nk.reinit(n);

    return 0;
}
	
static int NK_runfor(PyNK * self, PyObject * args, PyObject * kwds)
{
    if (!PyInt_Check(args)) {
       PyErr_SetString(PyExc_TypeError, "NK.runfor() arguments should a integer");
       return -1;
    }
    
    int n = (int)args;
    self->nk.runfor(n);
 
    return 0;
}

static PyObject * NK_new(PyTypeObject * type, PyObject *, PyObject *)
{
    // This looks allot like the default implementation, except we call the
    // in-place constructor.
    PyNK * self = (PyNK *)type->tp_alloc(type, 0);
    if (self != NULL) {
        //if (PyInt_Check(i) && PyInt_Check(h) && PyInt_Check(o)) {
        new (&(self->nk)) utilai::nk::NK(10);
    }
    return (PyObject *)self;
}

static PyMethodDef NK_methods[] = {
    {"runfor",             (PyCFunction)NK_runfor,      METH_O},
    {NULL,              NULL}           /* sentinel */
};

PyTypeObject PyNK_Type = {
        PyObject_HEAD_INIT(0)
        0,                              // ob_size
        //////"nn.NK",             // tp_name
        "NK",             // tp_name
        sizeof(PyNK),             // tp_basicsize
        0,                              // tp_itemsize
        // methods 
        (destructor)NK_dealloc,   // tp_dealloc
        0,                              // tp_print
        0,                              // tp_getattr
        0,                              // tp_setattr
        0,      // tp_compare
        0,        // tp_repr
        0,                  // tp_as_number
        0,                  // tp_as_sequence
        0,                              // tp_as_mapping
        0,                              // tp_hash
        0,                              // tp_call
        0,                              // tp_str
        0,// tp_getattro
        0,// tp_setattro
        0,                              // tp_as_buffer
        Py_TPFLAGS_DEFAULT,             // tp_flags
        "NK objects",             // tp_doc
        0,                              // tp_travers
        0,                              // tp_clear
        0,                              // tp_richcompare
        0,                              // tp_weaklistoffset
        0,                              // tp_iter
        0,                              // tp_iternext
        NK_methods,               // tp_methods
        0,                              // tp_members
        0,                              // tp_getset
        0,                              // tp_base
        0,                              // tp_dict
        0,                              // tp_descr_get
        0,                              // tp_descr_set
        0,                              // tp_dictoffset
	(initproc)NK_init,        // tp_init
        0,                              // tp_alloc
        NK_new,                   // tp_new
};

PyNK * newPyNK()
{
    return (PyNK *)PyNK_Type.tp_new(&PyNK_Type, 0, 0);
}
