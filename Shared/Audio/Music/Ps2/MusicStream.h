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

#ifndef zenic_ps2_MusicStream_h
#define zenic_ps2_MusicStream_h

#include <Shared/Base/Types.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


namespace zenic
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class MusicStream
{
public:

	MusicStream();
	MusicStream(const char* stream);
	~MusicStream();

	void open(const char* stream);
	void play();
	void stop();
	void setPosition(uint pos);
	float setPosition(float time);

private:

	bool m_isPlaying;

	static void loadIrx();
	static bool m_hasLodadedIrx;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif
