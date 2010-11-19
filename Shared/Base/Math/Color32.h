///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement and may not be copied or disclosed except in
// accordance with the terms of that agreement.
//
// Copyright (c) 2003-2004 Jesper Svennevid, Daniel Collin.
// All Rights Reserved.
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef zenic_Color32_h
#define zenic_Color32_h

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Shared/Base/Types.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace zenic
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Color32
{
public:

	inline Color32() {}
	inline Color32(u8 r, u8 g, u8 b, u8 a) : r(r), g(g), b(b), a(a) {}

	u8	r;
	u8	g;
	u8 	b;
	u8	a;
};


}


#endif
