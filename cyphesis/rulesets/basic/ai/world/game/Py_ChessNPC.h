// Cyphesis Online RPG Server and AI Engine
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

//BackPropagation Neural Network Python Bindings

#ifndef AI_PY_CHESSNPC_H
#define AI_PY_CHESSNPC_H

#include <Python.h>

#include "ChessTree.hpp"

/// \brief Wrapper for BNP in Python
///
typedef struct {
    PyObject_HEAD
    utilai::tree::chess::ChessTree chesstree;
} PyChessNPC;

extern PyTypeObject PyChessNPC_Type;

#define PyChessNPC_Check(_o) ((_o)->ob_type == &PyChessNPC_Type)

PyChessNPC * newPyChessNPC();

#endif // AI_PY_CHESSNPC_H
