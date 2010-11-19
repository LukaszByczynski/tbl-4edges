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

#ifndef zenic_Quaternion_h
#define zenic_Quaternion_h

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if defined(ZENIC_WIN32)
	#include "Win32/Quaternion.h"
#elif defined(ZENIC_PS2)
	#include "Ps2/Quaternion.h"
#elif defined(ZENIC_PSP)
	#include "Psp/Quaternion.h"
#else
	#error "Unsupported platform"
#endif

#endif // zenic_Quaternion_h

