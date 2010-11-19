///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement and may not be copied or disclosed except in
// accordance with the terms of that agreement.
//
// Copyright (c) 2003-2005 Jesper Svennevid, Daniel Collin.
// All Rights Reserved.
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef zenic_win32_RenderTarget_h
#define zenic_win32_RenderTarget_h

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Texture.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// forwards
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// class
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace zenic
{

namespace win32
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RenderTarget : public Texture
{
	ZENIC_SERIALIZABLE_FACTORY;

public:

	RenderTarget();
	virtual ~RenderTarget();

private:
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "RenderTarget.inl"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

}

#endif
