// -*- mode: c++; tab-width: 4; indent-tabs-mode: t; eval: (progn (c-set-style "stroustrup") (c-set-offset 'innamespace 0) (c-set-offset 'inextern-lang 0)); -*-
// vi:set ts=4 sts=4 sw=4 noet :
// Copyright 2014 The pyRASMUS development team
// 
// This file is part of pyRASMUS.
// 
// pyRASMUS is free software: you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License as published by the
// Free Software Foundation, either version 3 of the License, or (at your
// option) any later version.
// 
// pyRASMUS is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
// License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with pyRASMUS.  If not, see <http://www.gnu.org/licenses/>
#ifndef __FUNCTION_HH__
#define __FUNCTION_HH__
#include "lib.h"
#include <stdlib/rm_object.hh>

namespace rasmus {
namespace stdlib {

struct function_object: public rm_object {
	function_object(): rm_object(LType::function), argcnt(0), dtor(nullptr), func(nullptr) {}
	
	uint16_t argcnt;
	void (*dtor)(function_object * object);
	void * func;
};

} //namespace stdlib
} //namespace rasmus
#endif //__FUNCTION_HH__
