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

#ifndef zenic_ps2_SpeachPart1_h
#define zenic_ps2_SpeachPart1_h

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "SaPart.h"
#include <Shared/Base/Types.h>
#include <Shared/Graphics/Renderer/Ps2/Shaders/PostEffect/FadeToFog.h>
#include <Shared/Graphics/Renderer/Ps2/RenderSettings.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace zenic
{
	class SceneInfo;
	class Model;

	namespace ps2
	{
		class Texture;
		class Dma;
		class Renderer;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace zenic
{
	namespace ps2
	{
	
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class SpeachPart1 : public SaPart
{

public:

	SpeachPart1(Renderer& renderer, Dma& dmaChain) : SaPart(renderer, dmaChain), m_fade(0.0f) {}

	bool create();
	void update(float time, float deltaTime, SyncPoints::Part* syncPoints = 0);
	void reset() {};

private:

	void showImage(const Texture* texture, float strength = 1.0f);
	Texture* loadTexture(const char* filename);

	Texture* m_texts[6];

	float m_fade;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif





