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
#include "ChessTreeNode.hpp"

static void ChessNPC_dealloc(PyChessNPC *self)
{
    self->chesstree.~ChessTree();
    self->ob_type->tp_free(self);
}

static int ChessNPC_init(PyChessNPC * self, PyObject * args, PyObject * kwds)
{
    int ts = PyTuple_Size(args);
    if (ts != 0) { 
    	PyErr_SetString(PyExc_TypeError, "ChessNPC does not take arguments");
        return -1;
    }

    self->chesstree = utilai::tree::chess::ChessTree();

    return 0;
}
	
static int ChessNPC_start_game(PyChessNPC * self, PyObject * args, PyObject * kwds)
{
    int ts = PyTuple_Size(args);
    if (ts != 0) { 
    	PyErr_SetString(PyExc_TypeError, "ChessNPC does not take arguments");
        return -1;
    }

    self->chesstree.startGame();
    return 1;
}

//build a new tree based on the current board stored in self->chesstree
static int ChessNPC_build_tree(PyChessNPC * self, PyObject * args, PyObject * kwds)
{
    	self->chesstree.buildTree();
	
	return 1;
}

//build a tree based on a Board parameter
static int ChessNPC_build_tree_with_board(PyChessNPC * self, PyObject * args, PyObject * kwds)
{
	/*FIXME python args board parameter*/
    	self->chesstree.buildTreeWithBoard(self->chesstree.get());
	
	return 1;
}

static PyObject * ChessNPC_new(PyTypeObject * type, PyObject *, PyObject *)
{
    // This looks allot like the default implementation, except we call the
    // in-place constructor.
    PyChessNPC * self = (PyChessNPC *)type->tp_alloc(type, 0);
    if (self != NULL) {
        //if (PyInt_Check(i) && PyInt_Check(h) && PyInt_Check(o)) {
    	new (&(self->chesstree)) utilai::tree::chess::ChessTree();
    }
    return (PyObject *)self;
}

static PyMethodDef ChessNPC_methods[] = {
    {"startgame",             (PyCFunction)ChessNPC_start_game,      METH_O},
    {"buildtree",             (PyCFunction)ChessNPC_build_tree,      METH_O},
    {"buildtreewithboard",             (PyCFunction)ChessNPC_build_tree_with_board,      METH_O},
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
