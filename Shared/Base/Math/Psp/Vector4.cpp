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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Vector4.h"
#include "../../Serialize/Serializer.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Class
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace zenic
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Vector4::serialize(Serializer& s, const char* name)
{
	s.beginGroup(SERIALIZER_NAME(name), SERIALIZER_NAME("zenic::Vector4"));

	s.descriptor(SERIALIZER_NAME("x")) << x;
	s.descriptor(SERIALIZER_NAME("y")) << y;
	s.descriptor(SERIALIZER_NAME("z")) << z;
	s.descriptor(SERIALIZER_NAME("w")) << w;

	s.endGroup();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
