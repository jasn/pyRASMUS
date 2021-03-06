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
#ifndef __GIL_HH__
#define __GIL_HH__
#include <mutex>

namespace rasmus {
namespace stdlib {

typedef std::recursive_mutex gil_t;
typedef std::lock_guard<gil_t> gil_lock_t;

// Global interperter lock
extern gil_t gil;

template<typename T, typename F> 
inline T gil_execute(F f) {
	gil_lock_t lock(gil);
	return f();
}

} //rasmus
} //stdlib

#endif //__GIL_HH__
