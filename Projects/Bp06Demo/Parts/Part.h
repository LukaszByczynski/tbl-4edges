///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement and may not be copied or disclosed except in
// accordance with the terms of that agreement.
//
// Copyright (c) 2006 Jesper Svennevid, Daniel Collin.
// All Rights Reserved.
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef zenic_ps2_Part_h
#define zenic_ps2_Part_h

#include "../SyncPoints.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace zenic
{
	namespace ps2
	{
		class PadCamera;

	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace zenic
{
	namespace ps2
	{
	
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Part
{
public:
	Part() : m_padCamera(0) {}
	void setPadCamera(PadCamera* padCamera);

	virtual bool create() = 0;
	virtual void reset() = 0;
	virtual void update(float time, float deltaTime, SyncPoints::Part* syncPoints = 0) = 0;

protected:

	PadCamera* m_padCamera;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void Part::setPadCamera(PadCamera* padCamera)
{
	m_padCamera = padCamera;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

