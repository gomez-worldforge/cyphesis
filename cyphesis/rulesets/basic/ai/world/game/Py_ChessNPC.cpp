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


#include "Py_ChessNPC.h"

static void ChessNPC_dealloc(PyChessNPC *self)
{
    self->chesstree.~ChessTree();
    self->ob_type->tp_free(self);
}

static int ChessNPC_init(PyChessNPC * self, PyObject * args, PyObject * kwds)
{
    if (!PyList_Check(args)) {
       PyErr_SetString(PyExc_TypeError, "ChessNPC() arguments should a list");
       return -1;
    }
    int ts = PyTuple_Size(args);
    if (ts >= 4 || ts != 3) { 
    	PyErr_SetString(PyExc_TypeError, "ChessNPC must take list of 3 ints");
        return -1;
    }

    int i = 0,h = 0,o = 0;

    PyObject *item;
    item = PyTuple_GetItem(args, 0);
    if (PyInt_Check(item)) {
	i = (int)item;
    }

    item = PyTuple_GetItem(args, 0);
    if (PyInt_Check(item)) {
	h = (int)item;
    }

    item = PyTuple_GetItem(args, 0);
    if (PyInt_Check(item)) {
	o = (int)item;
    }

    self->net = utilai::nn::NN(i,h,o);

    return 0;
}
	
static int ChessNPC_run(PyChessNPC * self, PyObject * args, PyObject * kwds)
{
    if (!PyList_Check(args)) {
       PyErr_SetString(PyExc_TypeError, "ChessNPC() arguments should a list");
       return -1;
    }
    int ts = PyTuple_Size(args);
    if (ts > 65536) { 
    	PyErr_SetString(PyExc_TypeError, "ChessNPC must take list of less than 65536 items");
        return -1;
    }

    PyObject * clist;
  
    for (int i = 0; i < ts; i++) { 
    	clist = PyTuple_GetItem(args, i);
    	if (!PyList_Check(clist)) {
       		PyErr_SetString(PyExc_TypeError, "ChessNPC() arguments should a list of lists");
       		return -1;
    	}
    	int ts2 = PyTuple_Size(clist);
    	if (ts2 > 65536) { 
    		PyErr_SetString(PyExc_TypeError, "ChessNPC must take list of lists of less than 65536 items");
        	return -1;
    	}

	PyObject *item;
	utilai::math::Vector<float> iv(self->net.getinputsize());	
        for(int j = 0; j < self->net.getinputsize(); j++) {
    		item = PyTuple_GetItem(clist, j);
        	if (PyFloat_Check(item)) {
                    iv.set(j, PyFloat_AsDouble(item));
    		}
   	}
	
	utilai::math::Vector<float> ov(self->net.getinputsize());	
        for(int j = 0; j < self->net.getoutputsize(); j++) {
    		item = PyTuple_GetItem(clist, j);
        	if (PyFloat_Check(item)) {
                    ov.set(j, PyFloat_AsDouble(item));
    		}
 	}  	
	self->patterns.push_back(utilai::nn::Pair<utilai::math::Vector<float>,
						utilai::math::Vector<float> >
						(iv,ov));
    }
 
    for (;;) { 
    	int i = 0; 
    	for (utilai::nn::PatternVectorIter vi = self->patterns.begin(); 
			vi != self->patterns.end(); vi++, i++) { 
    		if (self->net.propagate((*vi).first(), (*vi).second()))
			i++;		
    	}

    	if (i == (int)(self->patterns.size()))
    		return 0;
    	else
		return -1;
    }
    return -1; // never reached
}

static PyObject* ChessNPC_test(PyChessNPC * self, PyObject * args, PyObject * kwds)
{
    if (!PyList_Check(args)) {
       PyErr_SetString(PyExc_TypeError, "ChessNPC() arguments should a list");
       return NULL;
    }
    int ts = PyTuple_Size(args);
    if (ts > 65536) { 
    	PyErr_SetString(PyExc_TypeError, "ChessNPC must take list of less than 65536 items");
        return NULL;
    }

    utilai::math::Vector<float> pattern(self->net.getinputsize());	
    for (int i = 0; i < ts; i++) { 
    	PyObject *item = PyTuple_GetItem(args, i);
        for(int j = 0; j < self->net.getinputsize(); j++) {
        	if (PyFloat_Check(item)) {
                    pattern.set(j, PyFloat_AsDouble(item));
    		} else {
    			PyErr_SetString(PyExc_TypeError, "ChessNPC test must take list of floats");
        		return NULL;
    		}
   	}
    }
	
    utilai::math::Vector<float> output = self->net.test(pattern);
    if (output.getcols() != self->net.getoutputsize()) {
    	PyErr_SetString(PyExc_TypeError, "ChessNPC internal error : outputpattern is different from output layer size");
       return NULL;

    }	
    PyObject *list = PyList_New(0);
    for (int i = 0; i < self->net.getoutputsize(); i++) { 
    	PyObject *f = PyFloat_FromDouble(output[i]);
	PyList_Append(list, f);
    }

    return list; 
}

static PyObject * ChessNPC_new(PyTypeObject * type, PyObject *, PyObject *)
{
    // This looks allot like the default implementation, except we call the
    // in-place constructor.
    PyChessNPC * self = (PyChessNPC *)type->tp_alloc(type, 0);
    if (self != NULL) {
        //if (PyInt_Check(i) && PyInt_Check(h) && PyInt_Check(o)) {
        new (&(self->net)) utilai::nn::NN((int)(10),
				(int)(10),
				(int)(10));
    }
    return (PyObject *)self;
}

static PyMethodDef ChessNPC_methods[] = {
    {"run",             (PyCFunction)ChessNPC_run,      METH_O},
    {"test",             (PyCFunction)ChessNPC_test,      METH_O},
    {NULL,              NULL}           /* sentinel */
};

PyTypeObject PyChessNPC_Type = {
        PyObject_HEAD_INIT(0)
        0,                              // ob_size
        //////"nn.ChessNPC",             // tp_name
        "ChessNPC",             // tp_name
        sizeof(PyChessNPC),             // tp_basicsize
        0,                              // tp_itemsize
        // methods 
        (destructor)ChessNPC_dealloc,   // tp_dealloc
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
        "ChessNPC objects",             // tp_doc
        0,                              // tp_travers
        0,                              // tp_clear
        0,                              // tp_richcompare
        0,                              // tp_weaklistoffset
        0,                              // tp_iter
        0,                              // tp_iternext
        ChessNPC_methods,               // tp_methods
        0,                              // tp_members
        0,                              // tp_getset
        0,                              // tp_base
        0,                              // tp_dict
        0,                              // tp_descr_get
        0,                              // tp_descr_set
        0,                              // tp_dictoffset
	(initproc)ChessNPC_init,        // tp_init
        0,                              // tp_alloc
        ChessNPC_new,                   // tp_new
};

PyChessNPC * newPyChessNPC()
{
    return (PyChessNPC *)PyChessNPC_Type.tp_new(&PyChessNPC_Type, 0, 0);
}
