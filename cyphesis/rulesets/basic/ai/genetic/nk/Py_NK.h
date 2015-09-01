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

#ifndef AI_PY_NK_H
#define AI_PY_NK_H

#include <Python.h>

#include "NK.hpp"

/// \brief Wrapper for BNP in Pyton
///
/// Uses in-place construction to embed full C++ object into what is
/// basically a C structure.
/// \ingroup PythonWrappers
typedef struct {
    PyObject_HEAD
    /// \brief Vector3D object handled by this wrapper
    utilai::nk::NK nk;
} PyNK;

extern PyTypeObject PyNK_Type;

#define PyNK_Check(_o) ((_o)->ob_type == &PyNK_Type)

PyNK * newPyNK();

#endif // AI_PY_NK_H
